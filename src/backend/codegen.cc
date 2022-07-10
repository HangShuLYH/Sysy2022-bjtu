//
// Created by hangshu on 22-7-4.
//
#define DEBUG

#include "codegen.hh"
#include <set>
#include <algorithm>

int GR::reg_num = 16;
int FR::reg_num = 33;

void Codegen::generateProgramCode() {
    out << ".arch armv7ve\n";
    out << ".arm\n";
    generateGlobalCode();
    for (Function *function: irVisitor.functions) {
        translateFunction(function);
    }
}

void Codegen::translateFunction(Function *function) {
    stackMapping.clear();
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
            if (dynamic_cast<AllocIR*>(ir)) {
                AllocIR *allocIr = dynamic_cast<AllocIR *>(ir);
                stackMapping[allocIr->v] = stackSize;
                stackSize += allocIr->arrayLen;
            }else {
                std::vector<Instr *> vec = translateInstr(ir);
                for (int i = 0; i < vec.size(); ++i) {
                    bb->pushInstr(vec[i]);
                }
            }
        }
        out << bb->name << ":\n";
        for (Instr *instr: bb->getInstrs()) {
            instr->print(out);
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
                stackMapping[gepIr->v1] = gepIr->arrayLen + stackMapping[gepIr->v2];
            } else {
                GR dst = getGR(gepIr->v1);
                Value *val = new VarValue();
                GR sp = getGR(val);
                vec.push_back(new GRegImmInstr(GRegImmInstr::Add, sp, GR(13), 0));
                Value *val2 = new VarValue();
                GR mul1 = getGR(val2);
                vec.push_back(new MovImm(mul1, 4));
                vec.push_back(new MLA(dst, mul1, getGR(gepIr->v3), sp));
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
            vec.push_back(new MovImm(src, storeIr->src.getInt()));
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
    if (typeid(*ir) == typeid(CastInt2FloatIR)) {
        CastInt2FloatIR *ir = dynamic_cast<CastInt2FloatIR *>(ir);
        GR src = getGR(ir->v2);
        FR dst = getFR(ir->v1);
        return {new VMovFG(dst, src), new VcvtFS(dst, dst)};
    }
    if (typeid(*ir) == typeid(CastFloat2IntIR)) {
        CastFloat2IntIR *ir = dynamic_cast<CastFloat2IntIR *>(ir);
        FR src = getFR(ir->v2);
        GR dst = getGR(ir->v1);
        return {new VcvtSF(src, src), new VMovGF(dst, src)};
    }

    if (dynamic_cast<ArithmeticIR*>(ir)) {
        std::cout << "ok..";
        ArithmeticIR *ir = dynamic_cast<ArithmeticIR *>(ir);
        std::vector<Instr *> vec;
        if (!ir->left.getVal()) {
            Value *v = new VarValue();
            ir->left.setVal(v);
            if (ir->left.isInt()) {
                GR dst = getGR(ir->left.getVal());
                vec.push_back(new MovImm(dst, ir->left.getInt()));
            } else {
                FR dst = getFR(ir->left.getVal());
                vec.push_back(new VMovImm(dst, ir->left.getFloat()));
            }
        }
        if (!ir->right.getVal()) {
            Value *v = new VarValue();
            ir->right.setVal(v);
            if (ir->right.isInt()) {
                GR dst = getGR(ir->right.getVal());
                vec.push_back(new MovImm(dst, ir->right.getInt()));
            } else {
                FR dst = getFR(ir->right.getVal());
                vec.push_back(new VMovImm(dst, ir->right.getFloat()));
            }
        }
        if (ir->left.getVal() || ir->right.getVal()) {
            if (ir->left.isInt()) {
                if (dynamic_cast<AddIIR*>(ir)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Add,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->left.getVal()),
                                                   getGR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(SubIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Sub,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->left.getVal()),
                                                   getGR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(MulIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Mul,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->left.getVal()),
                                                   getGR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(DivIIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Div,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->left.getVal()),
                                                   getGR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(ModIR)) {
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Div,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->left.getVal()),
                                                   getGR(ir->right.getVal())));
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Mul,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->right.getVal())));
                    vec.push_back(new GRegRegInstr(GRegRegInstr::Sub,
                                                   getGR(ir->res.getVal()),
                                                   getGR(ir->left.getVal()),
                                                   getGR(ir->res.getVal())));

                }
                if (typeid(*ir) == typeid(LTIIR)) {
                    vec.push_back(new Cmp(getGR(ir->left.getVal()), getGR(ir->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, LT));
                }
                if (typeid(*ir) == typeid(LEIIR)) {
                    vec.push_back(new Cmp(getGR(ir->left.getVal()), getGR(ir->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, LE));
                }
                if (typeid(*ir) == typeid(GTIIR)) {
                    vec.push_back(new Cmp(getGR(ir->left.getVal()), getGR(ir->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, GT));
                }
                if (typeid(*ir) == typeid(GEIIR)) {
                    vec.push_back(new Cmp(getGR(ir->left.getVal()), getGR(ir->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, GE));
                }
                if (typeid(*ir) == typeid(EQUIIR)) {
                    vec.push_back(new Cmp(getGR(ir->left.getVal()), getGR(ir->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, EQU));
                }
                if (typeid(*ir) == typeid(NEIIR)) {
                    vec.push_back(new Cmp(getGR(ir->left.getVal()), getGR(ir->right.getVal())));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, NE));
                }
            } else {
                if (typeid(*ir) == typeid(AddFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VAdd,
                                                   getFR(ir->res.getVal()),
                                                   getFR(ir->left.getVal()),
                                                   getFR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(SubFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VSub,
                                                   getFR(ir->res.getVal()),
                                                   getFR(ir->left.getVal()),
                                                   getFR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(MulFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VMul,
                                                   getFR(ir->res.getVal()),
                                                   getFR(ir->left.getVal()),
                                                   getFR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(DivFIR)) {
                    vec.push_back(new VRegRegInstr(VRegRegInstr::VDiv,
                                                   getFR(ir->res.getVal()),
                                                   getFR(ir->left.getVal()),
                                                   getFR(ir->right.getVal())));
                }
                if (typeid(*ir) == typeid(LTFIR)) {
                    vec.push_back(new VCmpe(getFR(ir->left.getVal()), getFR(ir->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, LT));
                }
                if (typeid(*ir) == typeid(GTFIR)) {
                    vec.push_back(new VCmpe(getFR(ir->left.getVal()), getFR(ir->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, GT));
                }
                if (typeid(*ir) == typeid(LEFIR)) {
                    vec.push_back(new VCmpe(getFR(ir->left.getVal()), getFR(ir->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, LE));
                }
                if (typeid(*ir) == typeid(GEFIR)) {
                    vec.push_back(new VCmpe(getFR(ir->left.getVal()), getFR(ir->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, GE));
                }
                if (typeid(*ir) == typeid(EQUFIR)) {
                    vec.push_back(new VCmpe(getFR(ir->left.getVal()), getFR(ir->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, EQU));
                }
                if (typeid(*ir) == typeid(NEFIR)) {
                    vec.push_back(new VCmpe(getFR(ir->left.getVal()), getFR(ir->right.getVal())));
                    vec.push_back(new VMrs());
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 0));
                    vec.push_back(new MovImm(getGR(ir->res.getVal()), 1, NE));
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
                new B(branchIr->trueTarget->name, EQU),
                new B(branchIr->falseTarget->name, NE)};
    }
    if (typeid(*ir) == typeid(CallIR)) {
        CallIR *callIr = dynamic_cast<CallIR *>(ir);
        int gr_cnt = 0;
        int fr_cnt = 0;
        std::vector<Instr *> vec;
        for (TempVal v: callIr->args) {
            if (!v.isFloat()) {
                if (gr_cnt >= 4) {
                    if (!v.getVal()) {
                        v.setVal(new VarValue());
                        vec.push_back(new MovImm(getGR(v.getVal()), v.getInt()));
                    }
                    stackMapping[v.getVal()] = (gr_cnt - 4) * 4;
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
                    stackMapping[v.getVal()] = (gr_cnt - 4) * 4;
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
    if (gRegMapping.count(src) != 0) {
        GR reg = GR::allocateReg();
        gRegMapping[src] = reg;
        return reg;
    }
    return gRegMapping[src];
}

FR Codegen::getFR(Value *src) {
    if (fRegMapping.count(src) != 0) {
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

void Codegen::regAlloc() {
    /*for (Function* function: irVisitor.functions) {
        std::map<BasicBlock*, std::set<Value*>> liveIn_i,liveOut_i,def_i,use_i;
        std::map<BasicBlock*, std::set<Value*>> liveIn_f,liveOut_f,def_f,use_f;
        for (BasicBlock* bb: function->basicBlocks) {
            //init in,out,def,use
            std::set<Value*> in_i,out_i,in_f,out_f;
            liveIn_i[bb] = in_i;
            liveOut_i[bb] = out_i;
            liveIn_f[bb] = in_f;
            liveOut_f[bb] = out_f;
            std::set<Value*> defSet_i, defSet_f;
            std::set<Value*> useSet_i, useSet_f;
            for (Instruction* ir: bb->ir) {
                if (ir->getDef()) {
                    if (ir->getDef()->getType()->isInt()) {
                        defSet_i.insert(ir->getDef());
                    }else {
                        defSet_f.insert(ir->getDef());
                    }
                }
                for (int i = 0; i < ir->getUseList().size(); ++i) {
                    if (ir->getUseList()[i]->getType()->isInt()) {
                        useSet_i.insert(ir->getUseList()[i]);
                    }else {
                        useSet_f.insert(ir->getUseList()[i]);
                    }
                }
            }
            def_i[bb] = defSet_i;
            use_i[bb] = useSet_i;
            def_f[bb] = defSet_f;
            use_f[bb] = useSet_f;
        }
        //function arguments
        for (int i = 0; i < function->params.size(); ++i) {
            if (function->params[i]->getType()->isInt()) {
                liveIn_i[function->basicBlocks[0]].insert(function->params[i]);
            } else {
                liveIn_f[function->basicBlocks[0]].insert(function->params[i]);
            }
        }
        //cal GR livein and liveout
        while(true) {
            bool flag = true;
            for (BasicBlock* bb: function->basicBlocks) {
                std::set<Value*> temp,in_prime,out_prime;
                std::set_difference(liveOut_i[bb].begin(),liveOut_i[bb].end(),
                                    def_i[bb].begin(),def_i[bb].end(),
                                    std::inserter(temp,temp.begin()));
                std::set_union(use_i[bb].begin(),use_i[bb].end(),
                               temp.begin(),temp.end(),
                               std::inserter(in_prime,in_prime.begin()));
                if (in_prime != liveIn_i[bb]) {
                    liveIn_i[bb] = in_prime;
                    flag = false;
                }
                std::set<Value*> t1,t2;
                for (BasicBlock* succ:bb->getSucc()) {
                    std::set_union(liveIn_i[succ].begin(),liveIn_i[succ].end(),
                                   t1.begin(),t1.end(),
                                   std::inserter(t2,t2.begin()));
                    t1 = t2;
                    out_prime = t2;
                    t2.clear();
                }
                if (out_prime != liveOut_i[bb]) {
                    liveOut_i[bb] = out_prime;
                    flag = false;
                }
            }
            if (flag) {
                break;
            }
        }

        //cal GR livein and liveout
        calLiveInfo(function,liveIn_i,liveOut_i,def_i,use_i);
        //cal FR livein and liveout
        calLiveInfo(function,liveIn_f,liveOut_f,def_f,use_f);
#ifdef DEBUG
        std::cout << "GR Info:\n";
        printLiveInfo(function,liveIn_i,liveOut_i);
        std::cout << "FR Info:\n";
        printLiveInfo(function,liveIn_f,liveOut_f);
#endif
        //create Inference graph: both GR and FR graph
        std::map<Value*, std::set<Value*>> IG_i, IG_f;
        createIG(IG_i,liveIn_i,liveOut_i);
        createIG(IG_f,liveIn_f,liveOut_f);
        std::cout << "IG create finish\n";
    }
}
void Codegen::calLiveInfo(Function* function,
                 std::map<BasicBlock*,std::set<Value*>>& liveIn,
                 std::map<BasicBlock*,std::set<Value*>>& liveOut,
                 std::map<BasicBlock*,std::set<Value*>>& def,
                 std::map<BasicBlock*,std::set<Value*>>& use) {
    while(true) {
        bool flag = true;
        for (BasicBlock* bb: function->basicBlocks) {
            std::set<Value*> temp,in_prime,out_prime;
            std::set_difference(liveOut[bb].begin(),liveOut[bb].end(),
                                def[bb].begin(),def[bb].end(),
                                std::inserter(temp,temp.begin()));
            std::set_union(use[bb].begin(),use[bb].end(),
                           temp.begin(),temp.end(),
                           std::inserter(in_prime,in_prime.begin()));
            if (in_prime != liveIn[bb]) {
                liveIn[bb] = in_prime;
                flag = false;
            }
            std::set<Value*> t1,t2;
            for (BasicBlock* succ:bb->getSucc()) {
                std::set_union(liveIn[succ].begin(),liveIn[succ].end(),
                               t1.begin(),t1.end(),
                               std::inserter(t2,t2.begin()));
                t1 = t2;
                out_prime = t2;
                t2.clear();
            }
            if (out_prime != liveOut[bb]) {
                liveOut[bb] = out_prime;
                flag = false;
            }
        }
        if (flag) {
            break;
        }
    }*/
}

void Codegen::printLiveInfo(Function *function,
                            std::map<BasicBlock *, std::set<Value *>> &liveIn,
                            std::map<BasicBlock *, std::set<Value *>> &liveOut) {
    std::cout << function->name << ":\n";
    std::cout << "liveIn():\n";
    auto iter = liveIn.begin();
    while (iter != liveIn.end()) {
        std::cout << "\t" << iter->first->name << ":";
        for (Value *v: iter->second) {
            std::cout << "%" << v->getNum() << " ";
        }
        std::cout << std::endl;
        iter++;
    }
    std::cout << "liveOut:\n";
    iter = liveOut.begin();
    while (iter != liveOut.end()) {
        std::cout << "\t" << iter->first->name << ":";
        for (Value *v: iter->second) {
            std::cout << "%" << v->getNum() << " ";
        }
        std::cout << std::endl;
        iter++;
    }
}

void Codegen::createIG(std::map<Value *, std::set<Value *>> &IG,
                       std::map<BasicBlock *, std::set<Value *>> &liveIn,
                       std::map<BasicBlock *, std::set<Value *>> &liveOut) {
    auto iter = liveIn.begin();
    while (iter != liveIn.end()) {
        for (Value *v1: iter->second) {
            for (Value *v2: iter->second) {
                if (v1 != v2) {
                    IG[v1].insert(v2);
                    IG[v2].insert(v1);
                }
            }
        }
        iter++;
    }
    iter = liveOut.begin();
    while (iter != liveOut.end()) {
        for (Value *v1: iter->second) {
            for (Value *v2: iter->second) {
                if (v1 != v2) {
                    IG[v1].insert(v2);
                    IG[v2].insert(v1);
                }
            }
        }
        iter++;
    }
}

void Codegen::comment(std::string s) {
    out << "@ " << s << "\n";
}