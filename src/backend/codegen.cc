//
// Created by hangshu on 22-7-4.
//
#define DEBUG

#include "codegen.hh"
#include <set>
#include <algorithm>
#include "allocRegs.hh"

int GR::reg_num = 16;
int FR::reg_num = 33;

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

void Codegen::generateProgramCode() {
    out << ".arch armv7ve\n";
    out << ".arm\n";
    generateGlobalCode();
    for (Function *function: irVisitor.functions) {
        out << ".global " << function->name << "\n";
    }
    out << ".section .text\n";
    for (Function *function: irVisitor.functions) {
        translateFunction(function);
        ColoringAlloc coloringAlloc(function);
        coloringAlloc.run();
        for (BasicBlock *block: function->basicBlocks) {
            out << block->name << ":\n";
            for (Instr *instr: block->getInstrs()) {
                out << "\t";
                instr->replace(coloringAlloc.getColorGR(),coloringAlloc.getColorFR());
                instr->print(out);
            }
        }
    }
}
void Codegen::translateFunction(Function *function) {
    stackMapping.clear();
    stackSize = 0;
    GR::reg_num = 16;
    FR::reg_num = 32;
    for (BasicBlock *bb: function->basicBlocks) {
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
                    stackMapping[function->params[i]] = stackSize + cnt * 4;
                    cnt++;
                }
                gr_cnt++;
            } else {
                if (fr_cnt < 32) {
                    fRegMapping[function->params[i]] = FR(fr_cnt);
                } else {
                    stackMapping[function->params[i]] = stackSize + cnt * 4;
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
                vec.push_back(new GRegImmInstr(GRegImmInstr::Add, dst, dst, 4 * gepIr->arrayLen));
            } else {
                Value *val = new VarValue();
                GR mul1 = getGR(val);
                vec.push_back(new MovImm(mul1, 4));
                vec.push_back(new MLA(dst, mul1, getGR(gepIr->v3), dst));
            }
        } else {
            if (!gepIr->v3) {
                stackMapping[gepIr->v1] = gepIr->arrayLen * 4 + stackMapping[gepIr->v2];
            } else {
                //v3 * 4 + v2
                GR dst = getGR(gepIr->v1);
                Value *val2 = new VarValue();
                GR mul1 = getGR(val2);
                vec.push_back(new MovImm(mul1, 4));
                vec.push_back(new MLA(dst, mul1, getGR(gepIr->v3), getGR(gepIr->v2)));
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
                vec.push_back(new Load(dst, GR(13), stackMapping[loadIr->v2]));
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
                vec.push_back(new VLoad(dst, GR(13), stackMapping[loadIr->v2]));
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
            src = getGR(storeIr->src.getVal());
        }
        if (storeIr->dst->is_Global()) {
            Value *v = new VarValue();
            GR base = getGR(v);
            vec.push_back(new MoveWFromSymbol(base, storeIr->dst->getName()));
            vec.push_back(new MoveTFromSymbol(base, storeIr->dst->getName()));
            vec.push_back(new Store(src, base, 0));
        } else {
            if (stackMapping.count(storeIr->dst) != 0) {
                vec.push_back(new Store(src, GR(13), stackMapping[storeIr->dst]));
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
            vec.push_back(new MoveT(src, storeIr->src.getFloat()));
            if (storeIr->dst->is_Global()) {
                Value *v = new VarValue();
                GR base = getGR(v);
                vec.push_back(new MoveWFromSymbol(base, storeIr->dst->getName()));
                vec.push_back(new MoveTFromSymbol(base, storeIr->dst->getName()));
                vec.push_back(new Store(src, base, 0));
            } else {
                if (stackMapping.count(storeIr->dst) != 0) {
                    vec.push_back(new Store(src, GR(13), stackMapping[storeIr->dst]));
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
                    vec.push_back(new VStore(src, GR(13), stackMapping[storeIr->dst]));
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
        return {new CmpImm(getGR(branchIr->cond), 1),
                new B(branchIr->trueTarget->name, EQU),
                new B(branchIr->falseTarget->name, NE)};
    }
    if (typeid(*ir) == typeid(CallIR)) {
        CallIR *callIr = dynamic_cast<CallIR *>(ir);
        int gr_cnt = 0;
        int fr_cnt = 0;
        int cnt = 0;
        std::vector<Instr *> vec;
        for (TempVal v: callIr->args) {
            if (!v.isFloat()) {
                if (gr_cnt >= 4) {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
                        vec.push_back(new MovImm(getGR(v.getVal()), v.getInt()));
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
                        vec.push_back(new MoveReg(GR(gr_cnt), getGR(v.getVal())));
                        gRegMapping[v.getVal()] = gr_cnt;
                    }
                }
                gr_cnt++;
            } else {
                if (fr_cnt >= 32) {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
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
                        vec.push_back(new VMoveReg(FR(gr_cnt), getFR(v.getVal())));
                        fRegMapping[v.getVal()] = fr_cnt;
                    }
                }
                fr_cnt++;
            }
        }
        vec.push_back(new Bl(callIr->func->name));
        if (callIr->returnVal) {
            if (callIr->returnVal->getType()->isInt()) {
                gRegMapping[callIr->returnVal] = 0;
            } else {
                fRegMapping[callIr->returnVal] = 0;
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
        vec.push_back(new Bx());
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
            bssList.push_back(v);
        }
    }
    if (!dataList.empty()) {
        out << ".section .data\n";
        for (Value *v: dataList) {
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
