//
// Created by hangshu on 22-7-4.
//
#define DEBUG

#include "codegen.hh"
#include <set>
#include <algorithm>
#include "allocRegs.hh"

int GR::reg_num = 16;
int FR::reg_num = 32;
int bbNameCnt = 0;
std::map<std::string, std::string> bbNameMapping;
std::map<std::string, std::string> stringConstMapping;
int stringConstCnt = 0;
bool is_legal_load_store_offset(int32_t offset) {
    return offset >= -4095 && offset <= 4095;
}
bool is_legal_immediate(int32_t value) {
    uint32_t u = static_cast<uint32_t>(value);
    if (u <= 0xffu) return true;
    for (int i = 1; i < 16; ++i) {
        uint32_t cur = (u << (2 * i)) | (u >> (32 - 2 * i));
        if (cur <= 0xffu) return true;
    }
    return false;
}

std::string getBBName(std::string name) {
    if (bbNameMapping.count(name) == 0) {
        bbNameMapping[name] = ".L" + std::to_string(bbNameCnt++);
    }
    return bbNameMapping[name];
}

std::vector<Instr *> setIntValue(GR target, int value) {
    if (0 <= value && value <= 65535) {
        return {new MovImm(target, value)};
    } else if (-255 <= value && value <= 0) {
        return {new MvnImm(target, -value - 1)};
    } else {
        int imm_low = value & ((1 << 16) - 1);
        int imm_high = value >> 16;
        return {new MoveW(target, imm_low),
                new MoveT(target, imm_high)};
    }
}

std::vector<Instr *> setFloatValue(GR target, float value) {
    union {
        float floatVal;
        int intVal;
    } data;
    data.floatVal = value;
    int imm_low = data.intVal & ((1 << 16) - 1);
    int imm_high = data.intVal >> 16;
    return {new MoveW(target, imm_low),
            new MoveT(target, imm_high)};
}

void Codegen::generateProgramCode() {
    out << ".arch armv7ve\n";
    out << ".arm\n";
    generateGlobalCode();
    out << ".global main\n";
    out << ".section .text\n";
    int removeCnt = 0;
    Function *entry_func = new Function(".init", new Type(TypeID::VOID));
    entry_func->pushBB(irVisitor.entry);
    irVisitor.functions.push_back(entry_func);
    std::map<Function *, std::set<GR>> usedGRMapping;
    std::map<Function *, std::set<FR>> usedFRMapping;
    std::map<Function *, int> stackSizeMapping;
    std::map<Function*, int> spillCountMapping;
    for (auto itt = irVisitor.functions.rbegin(); itt != irVisitor.functions.rend(); itt++) {
        Function *function = *itt;
        if (function->basicBlocks.empty()) continue;
        function->stackSize = translateFunction(function);
        stackSizeMapping[function] = function->stackSize;
        ColoringAlloc coloringAlloc(function);
        int spill_size = coloringAlloc.run() * 4;
        spillCountMapping[function] = spill_size;
        std::set<GR> allUsedRegsGR{GR(14)};
        std::set<FR> allUsedRegsFR;
        std::set<GR> callerSave;
        for (BasicBlock *block: function->basicBlocks) {
            for (auto it = block->getInstrs().rbegin(); it != block->getInstrs().rend();) {
                Instr *instr = *it;
                instr->replace(coloringAlloc.getColorGR(), coloringAlloc.getColorFR());
                instr->replaceBBName(bbNameMapping);
                if (typeid(*instr) == typeid(MoveReg) && instr->getUseG()[0] == instr->getDefG()[0] ||
                    typeid(*instr) == typeid(VMoveReg) && instr->getUseF()[0] == instr->getUseF()[0]) {
                    block->getInstrs().erase((++it).base());
                    removeCnt++;
                } else {
                    for (GR gr: instr->getDefG()) {
                        if (callee_save_regs.count(gr) != 0) {
                            allUsedRegsGR.insert(gr);
                        }
                        if (caller_save_regs.count(gr) != 0) {
                            callerSave.erase(gr);
                        }
                    }
                    for (GR gr: instr->getUseG()) {
                        if (caller_save_regs.count(gr) != 0) {
                            callerSave.insert(gr);
                        }
                    }
                    for (FR fr: instr->getDefF()) {
                        allUsedRegsFR.insert(fr);
                    }
                    if (typeid(*instr) == typeid(Bl)) {
//                        Push* pushInstr = dynamic_cast<Push*>(*(it+1));
//                        Pop* popInstr = dynamic_cast<Pop*>(*(it-1));
//                        if (pushInstr && popInstr) {
//                            pushInstr->addRegs(callerSave);
//                            popInstr->addRegs(callerSave);
//                        }
                    }
                    it++;
                }
            }
        }
        usedGRMapping[function] = allUsedRegsGR;
        usedFRMapping[function] = allUsedRegsFR;
    }
    for (auto itt = irVisitor.functions.rbegin(); itt != irVisitor.functions.rend(); itt++) {
        Function *function = *itt;
        if (function->basicBlocks.empty()) continue;
        if (function->name != ".init") {
            function->basicBlocks.insert(function->basicBlocks.begin(),new NormalBlock(function->name));
            bbNameMapping[function->name] = function->name;
            if (function->name == "main") {
                function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                             new Bl(".init"));
            }
            //sub r11,sp, #size;
            if (spillCountMapping[function] != 0) {
                if (is_legal_load_store_offset(spillCountMapping[function]) &&
                    is_legal_immediate(spillCountMapping[function])) {
                    function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                                 new GRegImmInstr(GRegImmInstr::Sub,GR(11),GR(13),spillCountMapping[function]));
                } else {
                    function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                                 new GRegRegInstr(GRegRegInstr::Sub,GR(11),GR(13),GR(12)));
                    std::vector<Instr *> vec = setIntValue(GR(12), spillCountMapping[function]);
                    for (int i = vec.size() - 1; i >= 0; --i) {
                        function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(), vec[i]);
                    }
                }
            }
            if (is_legal_immediate(function->stackSize) && is_legal_load_store_offset(function->stackSize)) {
                function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                             new GRegImmInstr(GRegImmInstr::Sub, GR(13), GR(13),
                                                                              function->stackSize));
            } else {
                function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                             new GRegRegInstr(GRegRegInstr::Sub, GR(13), GR(13),
                                                                              GR(12)));
                std::vector<Instr *> vec = setIntValue(GR(12), function->stackSize);
                for (int i = vec.size() - 1; i >= 0; --i) {
                    function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(), vec[i]);
                }
                usedGRMapping[function].insert(GR(12));
            }
            function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                         new Vpush(usedFRMapping[function]));
            function->basicBlocks[0]->getInstrs().insert(function->basicBlocks[0]->getInstrs().begin(),
                                                         new Push(usedGRMapping[function]));
            //simple way
        } else {
            function->basicBlocks[0]->getInstrs().push_back(new Bx());
        }
        for (BasicBlock *block: function->basicBlocks) {
            for (auto it = block->getInstrs().begin(); it != block->getInstrs().end();) {
                Instr *instr = *it;
                if (typeid(*instr) == typeid(Load)) {
                    Load *load = dynamic_cast<Load *>(instr);
                    if (load->offset < 0) {
                        load->offset = -load->offset + usedGRMapping[function].size() * 4 + usedFRMapping[function].size() * 4;
                    }
                    if (!is_legal_immediate(load->offset) || !is_legal_load_store_offset(load->offset)) {
                        block->getInstrs().erase(it);
                        block->getInstrs().insert(it, new Load(load->dst,GR(12),0));
                        block->getInstrs().insert(it, new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),load->base));
                        std::vector<Instr*> vv = setIntValue(GR(12), load->offset);
                        for (auto item = vv.rbegin();item != vv.rend();it++) {
                            block->getInstrs().insert(it,*item);
                        }
                        it = it + 1 + vv.size();
                    }
                }
                if (typeid(*instr) == typeid(Store)) {
                    Store *store = dynamic_cast<Store *>(instr);
                    if (store->offset < 0) {
                        store->offset = -store->offset + usedGRMapping[function].size() * 4 +
                                        usedFRMapping[function].size() * 4;
                    }
                    if (!is_legal_immediate(store->offset) || !is_legal_load_store_offset(store->offset)) {
                        block->getInstrs().erase(it);
                        block->getInstrs().insert(it, new Store(store->src,GR(12),0));
                        block->getInstrs().insert(it, new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),store->base));
                        std::vector<Instr*> vv = setIntValue(GR(12), store->offset);
                        for (auto item = vv.rbegin();item != vv.rend();it++) {
                            block->getInstrs().insert(it,*item);
                        }
                        it = it + 1 + vv.size();
                    }
                }
                if (typeid(*instr) == typeid(VLoad)) {
                    VLoad *vload = dynamic_cast<VLoad *>(instr);
                    if (vload->offset < 0) {
                        vload->offset = -vload->offset + usedGRMapping[function].size() * 4 +
                                        usedFRMapping[function].size() * 4;
                    }
                    if (!is_legal_immediate(vload->offset) || !is_legal_load_store_offset(vload->offset)) {
                        block->getInstrs().erase(it);
                        block->getInstrs().insert(it, new VLoad(vload->dst,GR(12),0));
                        block->getInstrs().insert(it, new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),vload->base));
                        std::vector<Instr*> vv = setIntValue(GR(12), vload->offset);
                        for (auto item = vv.rbegin();item != vv.rend();it++) {
                            block->getInstrs().insert(it,*item);
                        }
                        it = it + 1 + vv.size();
                    }
                }
                if (typeid(*instr) == typeid(MoveReg)) {
                    MoveReg* moveReg = dynamic_cast<MoveReg*>(instr);
                    //mov sp,r11;
                    if (moveReg->getUseG()[0] == GR(11)) {
                        block->getInstrs().erase(it);
                        int cnt = 0;
                        if (spillCountMapping[function] != 0) {
                            if (is_legal_immediate(spillCountMapping[function]) && is_legal_load_store_offset(spillCountMapping[function])) {
                                block->getInstrs().insert(it,new GRegImmInstr(GRegImmInstr::Sub, GR(13),GR(13),spillCountMapping[function]));
                                cnt++;
                            } else {
                                block->getInstrs().insert(it,new GRegRegInstr(GRegRegInstr::Sub,GR(13),GR(13),GR(12)));
                                std::vector<Instr*> vv = setIntValue(GR(12), spillCountMapping[function]);
                                for (auto item = vv.rbegin();item != vv.rend();it++) {
                                    block->getInstrs().insert(it,*item);
                                }
                                cnt = cnt + 1 + vv.size();
                            }
                        }
                        it = it + cnt - 1;
                    }
                    if (moveReg->getDefG()[0] == GR(11)) {
                        block->getInstrs().erase(it);
                        int cnt = 0;
                        if (spillCountMapping[function] != 0) {
                            if (is_legal_immediate(spillCountMapping[function]) && is_legal_load_store_offset(spillCountMapping[function])) {
                                block->getInstrs().insert(it,new GRegImmInstr(GRegImmInstr::Add, GR(13),GR(13),spillCountMapping[function]));
                                cnt++;
                            } else {
                                block->getInstrs().insert(it,new GRegRegInstr(GRegRegInstr::Add,GR(13),GR(13),GR(12)));
                                std::vector<Instr*> vv = setIntValue(GR(12), spillCountMapping[function]);
                                for (auto item = vv.rbegin();item != vv.rend();it++) {
                                    block->getInstrs().insert(it,*item);
                                }
                                cnt = cnt + 1 + vv.size();
                            }
                        }
                        it = it + cnt - 1;
                    }
                }
                if (typeid(*instr) == typeid(VStore)) {
                    VStore *vstore = dynamic_cast<VStore *>(instr);
                    if (vstore->offset < 0) {
                        vstore->offset = -vstore->offset + usedGRMapping[function].size() * 4 +
                                         usedFRMapping[function].size() * 4;
                    }
                    if (!is_legal_immediate(vstore->offset) || !is_legal_load_store_offset(vstore->offset)) {
                        block->getInstrs().erase(it);
                        block->getInstrs().insert(it, new VStore(vstore->src,GR(12),0));
                        block->getInstrs().insert(it, new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),vstore->base));
                        std::vector<Instr*> vv = setIntValue(GR(12), vstore->offset);
                        for (auto item = vv.rbegin();item != vv.rend();it++) {
                            block->getInstrs().insert(it,*item);
                        }
                        it = it + 1 + vv.size();
                    }
                }
                if (typeid(*instr) == typeid(Ret)) {
                    block->getInstrs().erase(it);
                    if (is_legal_immediate(function->stackSize) && is_legal_load_store_offset(function->stackSize)) {
                        if (function->stackSize != 0)
                        block->getInstrs().push_back(
                                new GRegImmInstr(GRegImmInstr::Add, GR(13), GR(13), function->stackSize));
                    } else {
                        std::vector<Instr *> vec = setIntValue(GR(12), function->stackSize);
                        for (int i = 0; i < vec.size(); i++) {
                            block->getInstrs().push_back(vec[i]);
                        }
                        block->getInstrs().push_back(new GRegRegInstr(GRegRegInstr::Add, GR(13), GR(13), GR(12)));
                    }
                    std::set<GR> setGR = usedGRMapping[function];
                    setGR.erase(GR(14));
                    setGR.insert(GR(15));
                    if (!usedFRMapping[function].empty()) {
                        block->getInstrs().push_back(new Vpop(usedFRMapping[function]));
                    }
                    if (!setGR.empty()) {
                        block->getInstrs().push_back(new Pop(setGR));
                    }
                    break;
                } else if (typeid(*instr) == typeid(Push)) {
                    Push *pushInstr = dynamic_cast<Push *>(instr);
                    if (pushInstr->regs.empty()) {
                        block->getInstrs().erase(it);
                    } else {
                        it++;
                    }
                } else if (typeid(*instr) == typeid(Pop)) {
                    Pop *pushInstr = dynamic_cast<Pop *>(instr);
                    if (pushInstr->regs.empty()) {
                        block->getInstrs().erase(it);
                    } else {
                        it++;
                    }
                } else if (typeid(*instr) == typeid(Vpop)) {
                    Vpop *pushInstr = dynamic_cast<Vpop *>(instr);
                    if (pushInstr->regs.empty()) {
                        block->getInstrs().erase(it);
                    } else {
                        it++;
                    }
                } else if (typeid(*instr) == typeid(Vpush)) {
                    Vpush *pushInstr = dynamic_cast<Vpush *>(instr);
                    if (pushInstr->regs.empty()) {
                        block->getInstrs().erase(it);
                    } else {
                        it++;
                    }
                } else if (typeid(*instr) == typeid(GRegImmInstr)) {
                    GRegImmInstr *g = dynamic_cast<GRegImmInstr *>(instr);
                    if ((g->op == GRegRegInstr::Add && g->src2 == 0 ||
                        g->op == GRegRegInstr::Sub && g->src2 == 0) && (g->dst == g->src1)) {
                        block->getInstrs().erase(it);
                    } else {
                        it++;
                    }
                } else {
                    it++;
                }
            }
        }
    }
    for (auto itt = irVisitor.functions.rbegin(); itt != irVisitor.functions.rend(); itt++) {
        Function *function = *itt;
        if (function->basicBlocks.empty()) continue;
        if (function->name == ".init") {
            out << function->name << ":\n";
        }
        for (BasicBlock *block: function->basicBlocks) {
            out << getBBName(block->name) << ":\n";
            for (auto it = block->getInstrs().begin(); it != block->getInstrs().end();) {
                Instr *instr = *it;
                it++;
                out << "\t";
                instr->print(out);
            }
        }
    }
}

int Codegen::translateFunction(Function *function) {
    stackMapping.clear();
    int stackSize = 0;
    GR::reg_num = 16;
    FR::reg_num = 32;
    for (BasicBlock *bb: function->basicBlocks) {
        getBBName(bb->name);
        for (Instruction *ir: bb->ir) {
            if (typeid(*ir) == typeid(CallIR)) {
                int size = 0;
                CallIR *callIr = dynamic_cast<CallIR *>(ir);
                int gr_cnt = 0;
                int fr_cnt = 0;
                for (TempVal v: callIr->args) {
                    if (!v.isFloat()) {
                        if (gr_cnt >= 4) {
                            size += 4;
                        }
                        gr_cnt++;
                    } else {
                        if (fr_cnt >= 32) {
                            size += 4;
                        }
                        fr_cnt++;
                    }
                }
                stackSize = stackSize > size ? stackSize : size;
            }
        }
    }
    for (BasicBlock *bb: function->basicBlocks) {
        for (Instruction *ir: bb->ir) {
            if (dynamic_cast<AllocIR *>(ir)) {
                AllocIR *allocIr = dynamic_cast<AllocIR *>(ir);
                stackMapping[allocIr->v] = stackSize;
                stackSize += allocIr->arrayLen * 4;
            }
        }
    }
    {
        int gr_cnt = 0;
        int fr_cnt = 0;
        int cnt = 0;
        for (int i = 0; i < function->params.size(); i++) {
            if (!function->params[i]->getType()->isFloat()) {
                if (gr_cnt < 4) {
                    gRegMapping[function->params[i]] = GR(gr_cnt);
                } else {
                    //push {}  -> stackSize + cnt * 4 + pushSize
                    // eg :push {r4,r5} int f(int a,int b,int c,int d,int e)
                    // e -> [sp, # (16 + 8)]
                    stackMapping[function->params[i]] = -(stackSize + cnt * 4);
                    cnt++;
                }
                gr_cnt++;
            } else {
                if (fr_cnt < 32) {
                    fRegMapping[function->params[i]] = FR(fr_cnt);
                } else {
                    stackMapping[function->params[i]] = -(stackSize + cnt * 4);
                    cnt++;
                }
                fr_cnt++;
            }
        }
    }
    for (BasicBlock *bb: function->basicBlocks) {
        for (Instruction *ir: bb->ir) {
            if (!dynamic_cast<AllocIR *>(ir)) {
                std::vector<Instr *> vec = translateInstr(ir);
                for (int i = 0; i < vec.size(); ++i) {
                    bb->pushInstr(vec[i]);
                }
            }
        }
    }
    return stackSize;
}

std::vector<Instr *> Codegen::translateInstr(Instruction *ir) {
    if (typeid(*ir) == typeid(GEPIR)) {
        GEPIR *gepIr = dynamic_cast<GEPIR *>(ir);
        std::vector<Instr *> vec;
        if (gepIr->v2->is_Global()) {
            GR dst = getGR(gepIr->v1);
            vec.push_back(new MoveWFromSymbol(dst, gepIr->v2->getName()));
            vec.push_back(new MoveTFromSymbol(dst, gepIr->v2->getName()));
            if (!gepIr->v3) {
                if (is_legal_load_store_offset(4*gepIr->arrayLen) && is_legal_immediate(4*gepIr->arrayLen)) {
                    vec.push_back(new GRegImmInstr(GRegImmInstr::Add, dst, dst, 4 * gepIr->arrayLen));
                } else {
                    std::vector<Instr*> v = setIntValue(GR(12), 4*gepIr->arrayLen);
                    for (Instr* instr:v) {
                        vec.push_back(instr);
                    }
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Add, dst, dst,GR(12)));
                }
            } else {
                Value *val = new VarValue();
                GR mul1 = getGR(val);
                vec.push_back(new MovImm(mul1, 4));
                vec.push_back(new MLA(dst, mul1, getGR(gepIr->v3), dst));
            }
        } else {
            if (!gepIr->v3) {
                if (stackMapping.count(gepIr->v2) == 0) {
                    GR dst = getGR(gepIr->v1);
                    if (is_legal_load_store_offset(gepIr->arrayLen * 4)&& is_legal_immediate(4*gepIr->arrayLen)) {
                        vec.push_back(new GRegImmInstr(GRegImmInstr::Add, dst, getGR(gepIr->v2), gepIr->arrayLen * 4));
                    } else {
                        std::vector<Instr*> v = setIntValue(GR(12), 4*gepIr->arrayLen);
                        for (Instr* instr:v) {
                            vec.push_back(instr);
                        }
                        vec.push_back(new GRegRegInstr(GRegRegInstr::Add, dst, getGR(gepIr->v2),GR(12)));
                    }
                } else {
                    stackMapping[gepIr->v1] = stackMapping[gepIr->v2] + 4 * gepIr->arrayLen;
                }
            } else {
                //v3 * 4 + v2
                GR dst = getGR(gepIr->v1);
                Value *val2 = new VarValue();
                GR mul1 = getGR(val2);
                vec.push_back(new MovImm(mul1, 4));
                if (stackMapping.count(gepIr->v2) != 0) {
                    if (is_legal_load_store_offset(stackMapping[gepIr->v2]) && is_legal_immediate(stackMapping[gepIr->v2])) {
                        vec.push_back(
                                new GRegImmInstr(GRegImmInstr::Add, getGR(gepIr->v2), GR(13), stackMapping[gepIr->v2]));
                    } else {
                        std::vector<Instr*> v = setIntValue(GR(12), stackMapping[gepIr->v2]);
                        for (Instr* instr:v) {
                            vec.push_back(instr);
                        }
                        vec.push_back(new GRegRegInstr(GRegRegInstr::Add, getGR(gepIr->v2), GR(13),GR(12)));
                    }
                    vec.push_back(new MLA(dst, mul1, getGR(gepIr->v3), getGR(gepIr->v2)));

                } else {
                    vec.push_back(new MLA(dst, mul1, getGR(gepIr->v3), getGR(gepIr->v2)));
                }
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(LoadIIR)) {
        LoadIIR *loadIr = dynamic_cast<LoadIIR *>(ir);
        std::vector<Instr *> vec;
        GR dst = getGR(loadIr->v1);
        if (loadIr->v2->is_Global()) {
            Value *v = new VarValue();
            GR base = getGR(v);
            vec.push_back(new MoveWFromSymbol(base, loadIr->v2->getName()));
            vec.push_back(new MoveTFromSymbol(base, loadIr->v2->getName()));
            vec.push_back(new Load(dst, base, 0));
        } else {
            if (stackMapping.count(loadIr->v2) != 0) {
                if (is_legal_load_store_offset(stackMapping[loadIr->v2]) &&
                is_legal_immediate(stackMapping[loadIr->v2])
                || stackMapping[loadIr->v2] < 0) {
                    vec.push_back(new Load(dst, GR(13), stackMapping[loadIr->v2]));
                } else {
                    std::vector<Instr*> v = setIntValue(GR(12), stackMapping[loadIr->v2]);
                    for (Instr* instr:v) {
                        vec.push_back(instr);
                    }
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),GR(13)));
                    vec.push_back(new Load(dst, GR(12), 0));
                }
            } else {
                vec.push_back(new Load(dst, getGR(loadIr->v2), 0));
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(LoadFIR)) {
        LoadFIR *loadIr = dynamic_cast<LoadFIR *>(ir);
        std::vector<Instr *> vec;
        FR dst = getFR(loadIr->v1);
        if (loadIr->v2->is_Global()) {
            Value *v = new VarValue();
            GR base = getGR(v);
            vec.push_back(new MoveWFromSymbol(base, loadIr->v2->getName()));
            vec.push_back(new MoveTFromSymbol(base, loadIr->v2->getName()));
            vec.push_back(new VLoad(dst, base, 0));
        } else {
            if (stackMapping.count(loadIr->v2) != 0) {
                if (is_legal_load_store_offset(stackMapping[loadIr->v2]) &&
                is_legal_immediate(stackMapping[loadIr->v2])
                || stackMapping[loadIr->v2] < 0) {
                    vec.push_back(new VLoad(dst, GR(13), stackMapping[loadIr->v2]));
                } else {
                    std::vector<Instr*> v = setIntValue(GR(12), stackMapping[loadIr->v2]);
                    for (Instr* instr:v) {
                        vec.push_back(instr);
                    }
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),GR(13)));
                    vec.push_back(new VLoad(dst, GR(12), 0));
                }
            } else {
                vec.push_back(new VLoad(dst, getGR(loadIr->v2), 0));
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(StoreIIR)) {
        StoreIIR *storeIr = dynamic_cast<StoreIIR *>(ir);
        std::vector<Instr *> vec;
        GR src;
        if (!storeIr->src.getVal()) {
            Value *val = new VarValue();
            storeIr->src.setVal(val);
            src = getGR(val);
            std::vector<Instr *> v = setIntValue(src, storeIr->src.getInt());
            for (Instr *instr: v) {
                vec.push_back(instr);
            }
        } else {
            if (gRegMapping.count(storeIr->src.getVal()) != 0) {
                src = getGR(storeIr->src.getVal());
            } else {
                stackMapping[storeIr->dst] = stackMapping[storeIr->src.getVal()];
                return vec;
            }
        }
        if (storeIr->dst->is_Global()) {
            Value *v = new VarValue();
            GR base = getGR(v);
            vec.push_back(new MoveWFromSymbol(base, storeIr->dst->getName()));
            vec.push_back(new MoveTFromSymbol(base, storeIr->dst->getName()));
            vec.push_back(new Store(src, base, 0));
        } else {
            if (stackMapping.count(storeIr->dst) != 0) {
                if (is_legal_load_store_offset(stackMapping[storeIr->dst]) &&
                is_legal_immediate(stackMapping[storeIr->dst])
                || stackMapping[storeIr->dst] < 0) {
                    vec.push_back(new Store(src, GR(13), stackMapping[storeIr->dst]));
                }else {
                    std::vector<Instr*> v = setIntValue(GR(12), stackMapping[storeIr->dst]);
                    for (Instr* instr:v) {
                        vec.push_back(instr);
                    }
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),GR(13)));
                    vec.push_back(new Store(src, GR(12), 0));
                }
            } else {
                vec.push_back(new Store(src, getGR(storeIr->dst), 0));
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(StoreFIR)) {
        StoreFIR *storeIr = dynamic_cast<StoreFIR *>(ir);
        std::vector<Instr *> vec;
        if (!storeIr->src.getVal()) {
            GR src;
            Value *val = new VarValue();
            storeIr->src.setVal(val);
            src = getGR(val);
            std::vector<Instr *> vv = setFloatValue(src, storeIr->src.getFloat());
            for (Instr *instr: vv) {
                vec.push_back(instr);
            }
            if (storeIr->dst->is_Global()) {
                Value *v = new VarValue();
                GR base = getGR(v);
                vec.push_back(new MoveWFromSymbol(base, storeIr->dst->getName()));
                vec.push_back(new MoveTFromSymbol(base, storeIr->dst->getName()));
                vec.push_back(new Store(src, base, 0));
            } else {
                if (stackMapping.count(storeIr->dst) != 0) {
                    if (is_legal_load_store_offset(stackMapping[storeIr->dst]) &&
                    is_legal_immediate(stackMapping[storeIr->dst])
                    || stackMapping[storeIr->dst] < 0) {
                        vec.push_back(new Store(src, GR(13), stackMapping[storeIr->dst]));
                    }else {
                        std::vector<Instr*> v = setIntValue(GR(12), stackMapping[storeIr->dst]);
                        for (Instr* instr:v) {
                            vec.push_back(instr);
                        }
                        vec.push_back(new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),GR(13)));
                        vec.push_back(new Store(src, GR(12), 0));
                    }
                } else {
                    vec.push_back(new Store(src, getGR(storeIr->dst), 0));
                }
            }
        } else {
            FR src = getFR(storeIr->src.getVal());
            if (storeIr->dst->is_Global()) {
                Value *v = new VarValue();
                GR base = getGR(v);
                vec.push_back(new MoveWFromSymbol(base, storeIr->dst->getName()));
                vec.push_back(new MoveTFromSymbol(base, storeIr->dst->getName()));
                vec.push_back(new VStore(src, base, 0));
            } else {
                if (stackMapping.count(storeIr->dst) != 0) {
                    if (is_legal_load_store_offset(stackMapping[storeIr->dst])
                    && is_legal_immediate(stackMapping[storeIr->dst])
                    || stackMapping[storeIr->dst] < 0) {
                        vec.push_back(new VStore(src, GR(13), stackMapping[storeIr->dst]));
                    }else {
                        std::vector<Instr*> v = setIntValue(GR(12), stackMapping[storeIr->dst]);
                        for (Instr* instr:v) {
                            vec.push_back(instr);
                        }
                        vec.push_back(new GRegRegInstr(GRegRegInstr::Add,GR(12),GR(12),GR(13)));
                        vec.push_back(new VStore(src, GR(12), 0));
                    }
                } else {
                    vec.push_back(new VStore(src, getGR(storeIr->dst), 0));
                }
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(UnaryIR)) {
        std::vector<Instr *> vec;
        UnaryIR *unaryIr = dynamic_cast<UnaryIR *>(ir);
        if (unaryIr->res.isInt()) {
            GR src = gRegMapping[unaryIr->v.getVal()];
            gRegMapping[unaryIr->res.getVal()] = src;
            if (unaryIr->op == OP::NEG) {
                vec.push_back(new RsubImm(gRegMapping[unaryIr->res.getVal()], gRegMapping[unaryIr->res.getVal()], 0));
            } else {
                vec.push_back(new CmpImm(src, 0));
                vec.push_back(new MovImm(src, 0));
                vec.push_back(new MovImm(src, 1, EQU));
            }
        } else {
            FR src = fRegMapping[unaryIr->v.getVal()];
            if (unaryIr->op == OP::NEG) {
                fRegMapping[unaryIr->res.getVal()] = src;
                vec.push_back(new VNeg(src, src));
            } else {
                vec.push_back(new VCmpe(src, 0));
                vec.push_back(new VMrs());
                GR dst = getGR(unaryIr->res.getVal());
                vec.push_back(new MovImm(dst, 0));
                vec.push_back(new MovImm(dst, 1, EQU));
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(CastInt2FloatIR)) {
        CastInt2FloatIR *ir2 = dynamic_cast<CastInt2FloatIR *>(ir);
        GR src = getGR(ir2->v2);
        FR dst = getFR(ir2->v1);
        return {new VMovFG(dst, src), new VcvtFS(dst, dst)};
    }
    if (typeid(*ir) == typeid(CastFloat2IntIR)) {
        CastFloat2IntIR *ir2 = dynamic_cast<CastFloat2IntIR *>(ir);
        FR src = getFR(ir2->v2);
        GR dst = getGR(ir2->v1);
        return {new VcvtSF(src, src), new VMovGF(dst, src)};
    }
    if (typeid(*ir) == typeid(AddIIR) ||
        typeid(*ir) == typeid(AddFIR) ||
        typeid(*ir) == typeid(DivIIR) ||
        typeid(*ir) == typeid(SubIIR) ||
        typeid(*ir) == typeid(SubFIR) ||
        typeid(*ir) == typeid(DivFIR) ||
        typeid(*ir) == typeid(MulIIR) ||
        typeid(*ir) == typeid(MulFIR) ||
        typeid(*ir) == typeid(ModIR) ||
        typeid(*ir) == typeid(LTIIR) ||
        typeid(*ir) == typeid(LTFIR) ||
        typeid(*ir) == typeid(GTIIR) ||
        typeid(*ir) == typeid(GTFIR) ||
        typeid(*ir) == typeid(LEIIR) ||
        typeid(*ir) == typeid(LEFIR) ||
        typeid(*ir) == typeid(GEIIR) ||
        typeid(*ir) == typeid(GEFIR) ||
        typeid(*ir) == typeid(EQUIIR) ||
        typeid(*ir) == typeid(EQUFIR) ||
        typeid(*ir) == typeid(NEIIR) ||
        typeid(*ir) == typeid(NEFIR)) {

        ArithmeticIR *ir2 = dynamic_cast<ArithmeticIR *>(ir);
        std::vector<Instr *> vec;
        if (!ir2->left.getVal()) {
            Value *v = new VarValue();
            ir2->left.setVal(v);
            if (ir2->left.isInt()) {
                GR dst = getGR(ir2->left.getVal());
                std::vector<Instr *> v = setIntValue(dst, ir2->left.getInt());
                for (Instr *instr: v) {
                    vec.push_back(instr);
                }
            } else {
                FR dst = getFR(ir2->left.getVal());
                vec.push_back(new VMovImm(dst, ir2->left.getFloat()));
            }
        }
        if (!ir2->right.getVal()) {
            Value *v = new VarValue();
            ir2->right.setVal(v);
            if (ir2->right.isInt()) {
                GR dst = getGR(ir2->right.getVal());
                std::vector<Instr *> v = setIntValue(dst, ir2->right.getInt());
                for (Instr *instr: v) {
                    vec.push_back(instr);
                }
            } else {
                FR dst = getFR(ir2->right.getVal());
                vec.push_back(new VMovImm(dst, ir2->right.getFloat()));
            }
        }
        if (ir2->left.getVal() || ir2->right.getVal()) {
            if (ir2->left.isInt()) {
                if (typeid(*ir) == typeid(AddIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Add,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->left.getVal()),
                                                   getGR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(SubIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Sub,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->left.getVal()),
                                                   getGR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(MulIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Mul,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->left.getVal()),
                                                   getGR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(DivIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Div,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->left.getVal()),
                                                   getGR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(ModIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Div,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->left.getVal()),
                                                   getGR(ir2->right.getVal())));
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Mul,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->right.getVal())));
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Sub,
                                                   getGR(ir2->res.getVal()),
                                                   getGR(ir2->left.getVal()),
                                                   getGR(ir2->res.getVal())));

                }
                if (typeid(*ir) == typeid(LTIIR)) {
                    vec.push_back(new Cmp(getGR(ir2->left.getVal()), getGR(ir2->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, LT));
                }
                if (typeid(*ir) == typeid(LEIIR)) {
                    vec.push_back(new Cmp(getGR(ir2->left.getVal()), getGR(ir2->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, LE));
                }
                if (typeid(*ir) == typeid(GTIIR)) {
                    vec.push_back(new Cmp(getGR(ir2->left.getVal()), getGR(ir2->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, GT));
                }
                if (typeid(*ir) == typeid(GEIIR)) {
                    vec.push_back(new Cmp(getGR(ir2->left.getVal()), getGR(ir2->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, GE));
                }
                if (typeid(*ir) == typeid(EQUIIR)) {
                    vec.push_back(new Cmp(getGR(ir2->left.getVal()), getGR(ir2->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, EQU));
                }
                if (typeid(*ir) == typeid(NEIIR)) {
                    vec.push_back(new Cmp(getGR(ir2->left.getVal()), getGR(ir2->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, NE));
                }
            } else {
                if (typeid(*ir) == typeid(AddFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VAdd,
                                                   getFR(ir2->res.getVal()),
                                                   getFR(ir2->left.getVal()),
                                                   getFR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(SubFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VSub,
                                                   getFR(ir2->res.getVal()),
                                                   getFR(ir2->left.getVal()),
                                                   getFR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(MulFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VMul,
                                                   getFR(ir2->res.getVal()),
                                                   getFR(ir2->left.getVal()),
                                                   getFR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(DivFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VDiv,
                                                   getFR(ir2->res.getVal()),
                                                   getFR(ir2->left.getVal()),
                                                   getFR(ir2->right.getVal())));
                }
                if (typeid(*ir) == typeid(LTFIR)) {
                    vec.push_back(new VCmpe(getFR(ir2->left.getVal()), getFR(ir2->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, LT));
                }
                if (typeid(*ir) == typeid(GTFIR)) {
                    vec.push_back(new VCmpe(getFR(ir2->left.getVal()), getFR(ir2->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, GT));
                }
                if (typeid(*ir) == typeid(LEFIR)) {
                    vec.push_back(new VCmpe(getFR(ir2->left.getVal()), getFR(ir2->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, LE));
                }
                if (typeid(*ir) == typeid(GEFIR)) {
                    vec.push_back(new VCmpe(getFR(ir2->left.getVal()), getFR(ir2->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, GE));
                }
                if (typeid(*ir) == typeid(EQUFIR)) {
                    vec.push_back(new VCmpe(getFR(ir2->left.getVal()), getFR(ir2->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, EQU));
                }
                if (typeid(*ir) == typeid(NEFIR)) {
                    vec.push_back(new VCmpe(getFR(ir2->left.getVal()), getFR(ir2->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir2->res.getVal()), 1, NE));
                }
            }
        }
        return vec;
    }

    if (typeid(*ir) == typeid(JumpIR)) {
        return {new B(dynamic_cast<JumpIR *>(ir)->target->name)};
    }
    if (typeid(*ir) == typeid(BranchIR)) {
        BranchIR *branchIr = dynamic_cast<BranchIR *>(ir);
        return {new CmpImm(getGR(branchIr->cond), 0),
                new B(branchIr->trueTarget->name, NE),
                new B(branchIr->falseTarget->name, EQU)};
    }
    if (typeid(*ir) == typeid(CallIR)) {
        CallIR *callIr = dynamic_cast<CallIR *>(ir);
        int gr_cnt = 0;
        int fr_cnt = 0;
        int cnt = 0;
        std::vector<Instr *> vec;
        for (TempVal v: callIr->args) {
            if (v.getType()->isString()) {
                vec.push_back(new MoveWFromSymbol(GR(0), stringConstMapping[v.getString()]));
                vec.push_back(new MoveTFromSymbol(GR(0), stringConstMapping[v.getString()]));
                gr_cnt++;
                continue;
            }
            if (!v.isFloat()) {
                if (gr_cnt >= 4) {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
                        gRegMapping[v.getVal()] = gr_cnt;
                        vec.push_back(new MovImm(getGR(v.getVal()), v.getInt()));
                    } else if (gRegMapping.count(v.getVal()) == 0) {
                        if (is_legal_load_store_offset(stackMapping[v.getVal()]) && is_legal_immediate(stackMapping[v.getVal()])) {
                            vec.push_back(new GRegImmInstr(GRegImmInstr::Add, getGR(v.getVal()), GR(13),
                                                           stackMapping[v.getVal()]));
                        } else {
                            std::vector<Instr*> vv = setIntValue(GR(12), stackMapping[v.getVal()]);
                            for (Instr* instr:vv) {
                                vec.push_back(instr);
                            }
                            vec.push_back(new GRegRegInstr(GRegRegInstr::Add, getGR(v.getVal()), GR(13),GR(12)));
                        }
                    }
                    stackMapping[v.getVal()] = cnt * 4;
                    cnt++;
                    vec.push_back(new Store(getGR(v.getVal()), GR(13), stackMapping[v.getVal()]));
                } else {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
                        gRegMapping[v.getVal()] = gr_cnt;
                        vec.push_back(new MovImm(getGR(v.getVal()), v.getInt()));
                    } else {
                        if (gRegMapping.count(v.getVal()) != 0) {
                            vec.push_back(new MoveReg(GR(gr_cnt), getGR(v.getVal())));
                            gRegMapping[v.getVal()] = gr_cnt;
                        } else {
                            if (is_legal_load_store_offset(stackMapping[v.getVal()]) && is_legal_immediate(stackMapping[v.getVal()])) {
                                vec.push_back(new GRegImmInstr(GRegImmInstr::Add, GR(gr_cnt), GR(13),
                                                         stackMapping[v.getVal()]));
                            } else {
                                std::vector<Instr*> vv = setIntValue(GR(12), stackMapping[v.getVal()]);
                                for (Instr* instr:vv) {
                                    vec.push_back(instr);
                                }
                                vec.push_back(new GRegRegInstr(GRegRegInstr::Add, GR(gr_cnt),GR(13),GR(12)));
                            }
                        }
                    }
                }
                gr_cnt++;
            } else {
                if (fr_cnt >= 32) {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
                        fRegMapping[v.getVal()] = fr_cnt;
                        vec.push_back(new VMovImm(getFR(v.getVal()), v.getFloat()));
                    }
                    stackMapping[v.getVal()] = cnt * 4;
                    cnt++;
                    vec.push_back(new VStore(getFR(v.getVal()), GR(13), stackMapping[v.getVal()]));
                } else {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
                        fRegMapping[v.getVal()] = fr_cnt;
                        vec.push_back(new VMovImm(getFR(v.getVal()), v.getFloat()));
                    } else {
                        vec.push_back(new VMoveReg(FR(fr_cnt), getFR(v.getVal())));
                        fRegMapping[v.getVal()] = fr_cnt;
                    }
                }
                fr_cnt++;
            }
        }
//        vec.push_back(new Push({}));
        vec.push_back(new MoveReg(GR(13),GR(11)));
        vec.push_back(new Bl(callIr->func->name));
        vec.push_back(new MoveReg(GR(11),GR(13)));
//        vec.push_back(new Pop({}));
        if (callIr->returnVal) {
            if (callIr->returnVal->getType()->isInt()) {
                vec.push_back(new MoveReg(getGR(callIr->returnVal), GR(0)));
            } else {
                vec.push_back(new VMoveReg(getFR(callIr->returnVal), FR(0)));
            }
        }
        return vec;
    }
    if (typeid(*ir) == typeid(ReturnIR)) {
        ReturnIR *returnIr = dynamic_cast<ReturnIR *>(ir);
        std::vector<Instr *> vec;
        if (returnIr->useInt) {
            vec.push_back(new MovImm(GR(0), returnIr->retInt));
        } else if (returnIr->useFloat) {
            vec.push_back(new VMovImm(FR(0), returnIr->retFloat));
        } else if (returnIr->v) {
            if (returnIr->v->getType()->isInt()) {
                vec.push_back(new MoveReg(GR(0), getGR(returnIr->v)));
            } else {
                vec.push_back(new VMoveReg(FR(0), getFR(returnIr->v)));
            }
        }
        vec.push_back(new Ret());
        return vec;
    }
    return {};
}

GR Codegen::getGR(Value *src) {
    if (gRegMapping.count(src) == 0) {
        GR reg = GR::allocateReg();
        gRegMapping[src] = reg;
        return reg;
    }
    return gRegMapping[src];
}

FR Codegen::getFR(Value *src) {
    if (fRegMapping.count(src) == 0) {
        FR reg = FR::allocateReg();
        fRegMapping[src] = reg;
        return reg;
    }
    return fRegMapping[src];
}

void Codegen::generateGlobalCode() {
    std::vector<Value *> dataList;
    std::vector<Value *> bssList;
    for (Value *v: irVisitor.globalVars) {
        if (typeid(*v) == typeid(ConstValue)) {
            dataList.push_back(v);
        } else {
            if (v->getType()->isString()) {
                dataList.push_back(v);
            } else {
                bssList.push_back(v);
            }
        }
    }
    if (!dataList.empty()) {
        out << ".section .data\n";
        for (Value *v: dataList) {
            if (!v->getType()->isString()) {
                out << ".align\n";
                out << v->getName() << ":\n";
                out << "\t.4byte ";
                ConstValue *vv = dynamic_cast<ConstValue *>(v);
                if (!vv->is_Array()) {
                    if (vv->getType()->isInt()) {
                        out << vv->getIntVal();
                    } else {
                        out << vv->getFloatVal();
                    }
                } else {
                    for (int i = 0; i < vv->getArrayLen(); ++i) {
                        if (i != 0) {
                            out << ",";
                        }
                        if (vv->getType()->isIntPointer()) {
                            out << vv->getIntValList()[i];
                        } else {
                            out << vv->getFloatValList()[i];
                        }
                    }
                }
                out << "\n";
            } else {
                std::string varName = "_m_global_string_const" + std::to_string(stringConstCnt++);
                stringConstMapping[v->getName()] = varName;
                out << varName << ":\n\t.asciz " << v->getName() << "\n";
            }
        }
    }
    if (!bssList.empty()) {
        out << ".section .bss\n";
        for (Value *v: bssList) {
            out << ".align\n";
            out << v->getName() << ":\n";
            out << "\t.space ";
            if (!v->is_Array()) {
                out << "4";
            } else {
                out << v->getArrayLen() * 4;
            }
            out << "\n";
        }
    }
}

void Codegen::comment(std::string s) {
    out << "@ " << s << "\n";
}
