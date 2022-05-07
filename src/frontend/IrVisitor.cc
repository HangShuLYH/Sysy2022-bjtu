//
// Created by hangshu on 22-4-26.
//
#include "IrVisitor.hh"
#include <iostream>

void IrVisitor::visit(CompUnit *compUnit) {
    for (size_t i = 0; i < compUnit->declDefList.size(); ++i) {
        compUnit->declDefList[i]->accept(*this);
    }
    for (size_t i = 0; i < functions.size(); ++i) {
        functions[i]->clear();
    }
}

void IrVisitor::visit(DeclDef *declDef) {
    if (declDef->varDecl) {
        declDef->varDecl->accept(*this);
    } else if (declDef->funcDef) {
        declDef->funcDef->accept(*this);
    } else if (declDef->constDecl) {
        declDef->constDecl->accept(*this);
    } else {
        std::cerr << "This should never be seen in IrVisitor(DeclDef)!" << std::endl;
    }
}

void IrVisitor::visit(ConstDecl *constDecl) {
    if (constDecl->defType->type == type_specifier::TYPE_INT) {
        curDefType = TYPE::INT;
    } else if (constDecl->defType->type == type_specifier::TYPE_FLOAT) {
        curDefType = TYPE::FLOAT;
    } else {
        std::cerr << "Void should not be type of Value!" << std::endl;
    }
    for (size_t i = 0; i < constDecl->constDefList.size(); ++i) {
        constDecl->constDefList[i]->accept(*this);
    }
}

void IrVisitor::visit(ConstDef *constDef) {
    if (constDef->constExpList.empty()) {
        constDef->constInitVal->accept(*this);
        if (!useConst) {
            std::cerr << "Const Value should be defined when compiling!" << std::endl;
        }
        ConstValue *var = nullptr;
        if (curDefType == TYPE::INT) {
            if (curValType == TYPE::INT) {
                var = new ConstValue(0, constDef->identifier, TYPE::INT);
                var->setInt(tempInt);
            } else if (curValType == TYPE::FLOAT) {
                var = new ConstValue(0, constDef->identifier, TYPE::INT);
                var->setInt(tempFloat);
            }
        } else if (curDefType == TYPE::FLOAT) {
            if (curValType == TYPE::INT) {
                var = new ConstValue(0, constDef->identifier, TYPE::FLOAT);
                var->setFloat(tempInt);
            } else if (curValType == TYPE::FLOAT) {
                var = new ConstValue(0, constDef->identifier, TYPE::FLOAT);
                var->setFloat(tempFloat);
            }
        }
        if (isGlobal()) {
            globalVars.push_back(var);
        } else {
            cur_bb->pushVar(var);
        }
    } else {

    }
}

void IrVisitor::visit(ConstDefList *constDefList) {}

void IrVisitor::visit(ConstExpList *constExpList) {}

void IrVisitor::visit(ConstInitVal *constInitVal) {
    if (constInitVal->constExp) {
        constInitVal->constExp->accept(*this);
    } else {
        for (size_t i = 0; i < constInitVal->constInitValList.size(); ++i) {
            constInitVal->constInitValList[i]->accept(*this);
        }
    }
}

void IrVisitor::visit(ConstInitValList *constInitValList) {}

void IrVisitor::visit(VarDecl *varDecl) {
    if (varDecl->defType->type == type_specifier::TYPE_INT) {
        curDefType = TYPE::INT;
    } else if (varDecl->defType->type == type_specifier::TYPE_FLOAT) {
        curDefType = TYPE::FLOAT;
    } else {
        std::cerr << "Void should not be type of Value!" << std::endl;
    }
    for (size_t i = 0; i < varDecl->varDefList.size(); ++i) {
        varDecl->varDefList[i]->accept(*this);
    }
}

void IrVisitor::visit(VarDefList *varDefList) {}

void IrVisitor::visit(VarDef *varDef) {
    if (varDef->constExpList.empty()) {
        VarValue *var = nullptr;
        if (curDefType == TYPE::INT) {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, TYPE::INTPOINTER);
            } else {
                var = new VarValue(0, varDef->identifier, TYPE::INTPOINTER);
            }
            AllocIIR *ir = new AllocIIR(var);
            cur_bb->pushIr(ir);
        } else {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, TYPE::FLOATPOINTER);
            } else {
                var = new VarValue(0, varDef->identifier, TYPE::FLOATPOINTER);
            }
            AllocFIR *ir = new AllocFIR(var);
            cur_bb->pushIr(ir);
        }
        if (isGlobal()) {
            var->isGlobal = true;
            globalVars.push_back(var);
        } else {
            cur_bb->pushVar(var);
        }
        if (varDef->initVal) {
            varDef->initVal->accept(*this);
            if (useConst) {
                if (var->type == TYPE::INTPOINTER) {
                    if (curValType == TYPE::INT) {
                        StoreIIR *ir = new StoreIIR(var, tempInt);
                        cur_bb->pushIr(ir);
                    } else {
                        StoreIIR *ir = new StoreIIR(var, tempFloat);
                        cur_bb->pushIr(ir);
                    }
                } else {
                    if (curValType == TYPE::INT) {
                        StoreFIR *ir = new StoreFIR(var, tempInt);
                        cur_bb->pushIr(ir);
                    } else {
                        StoreFIR *ir = new StoreFIR(var, tempFloat);
                        cur_bb->pushIr(ir);
                    }
                }
            } else {
                if (var->type == TYPE::INTPOINTER && tempVal->type == TYPE::FLOAT) {
                    VarValue *t = nullptr;
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                    } else {
                        t = new VarValue(0, "", TYPE::INT);
                    }
                    CastFloat2IntIR *ir = new CastFloat2IntIR(t, var);
                    cur_bb->pushIr(ir);
                    var = t;
                } else if (var->type == TYPE::FLOATPOINTER && tempVal->type == TYPE::INT) {
                    VarValue *t = nullptr;
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                    } else {
                        t = new VarValue(0, "", TYPE::FLOAT);
                    }
                    CastInt2FloatIR *ir = new CastInt2FloatIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                }
                if (var->type == TYPE::INT) {
                    StoreIIR *ir = new StoreIIR(var, tempVal);
                    cur_bb->pushIr(ir);
                } else {
                    StoreFIR *ir = new StoreFIR(var, tempVal);
                    cur_bb->pushIr(ir);
                }
            }
        }

    } else {
//        auto t = new Value(varCnt++, varDef->identifier, curDefType, true);
//        for (size_t i = 0; i < varDef->constExpList.size(); ++i) {
//            varDef->constExpList[i]->accept(*this);
//            assert(curValType == TYPE::INT);
//            t->dims.push_back(tempInt);
//        }

    }
}

void IrVisitor::visit(InitVal *initVal) {
    if (initVal->exp) {
        initVal->exp->accept(*this);
    } else {
        for (size_t i = 0; i < initVal->initValList.size(); ++i) {
            initVal->initValList[i]->accept(*this);
        }
    }
}

void IrVisitor::visit(InitValList *initValList) {}

void IrVisitor::visit(FuncDef *funcDef) {
    if (findFunc(funcDef->identifier)) {
        std::cerr << "Duplicate Function Definition of " << funcDef->identifier << std::endl;
    }
    cur_bb = entry;
    Function *function;
    if (funcDef->defType->type == type_specifier::TYPE_INT) {
        function = new Function(funcDef->identifier, TYPE::INT);
    } else if (funcDef->defType->type == type_specifier::TYPE_FLOAT) {
        function = new Function(funcDef->identifier, TYPE::FLOAT);
    } else {
        function = new Function(funcDef->identifier, TYPE::VOID);
    }
    cur_func = function;
    functions.push_back(cur_func);
    if (funcDef->funcFParams) {
        funcDef->funcFParams->accept(*this);
        cur_bb = new NormalBlock(cur_bb, cur_func->bbCnt++);
        cur_func->pushBB(cur_bb);
        for (size_t i = 0; i < cur_func->params.size(); ++i) {
            if (cur_func->params[i]->type == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, cur_func->params[i]->name, TYPE::INTPOINTER);
                cur_bb->pushVar(v);
                AllocIIR *ir1 = new AllocIIR(v);
                cur_bb->pushIr(ir1);
                StoreIIR *ir2 = new StoreIIR(v, cur_func->params[i]);
                cur_bb->pushIr(ir2);
            } else {
                VarValue *v = new VarValue(cur_func->varCnt++, cur_func->params[i]->name, TYPE::FLOATPOINTER);
                cur_bb->pushVar(v);
                AllocFIR *ir1 = new AllocFIR(v);
                cur_bb->pushIr(ir1);
                StoreFIR *ir2 = new StoreFIR(v, cur_func->params[i]);
                cur_bb->pushIr(ir2);
            }
        }
    }
    funcDef->block->accept(*this);
}

void IrVisitor::visit(DefType *defType) {}

void IrVisitor::visit(FuncFParams *funcFParams) {
    for (size_t i = 0; i < funcFParams->funcFParamList.size(); ++i) {
        funcFParams->funcFParamList[i]->accept(*this);
    }
}

void IrVisitor::visit(FuncFParam *funcFParam) {
    if (!funcFParam->isArray) {
        if (funcFParam->defType->type == type_specifier::TYPE_FLOAT) {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, TYPE::FLOAT);
        } else if (funcFParam->defType->type == type_specifier::TYPE_INT) {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, TYPE::INT);
        }
        cur_func->params.push_back(tempVal);
    } else {

    }
}

void IrVisitor::visit(ParamArrayExpList *paramArrayExpList) {}

void IrVisitor::visit(Block *block) {
    cur_bb = new NormalBlock(cur_bb, cur_func->bbCnt++);
    pushBB(cur_bb);
    for (size_t i = 0; i < block->blockItemList.size(); ++i) {
        block->blockItemList[i]->accept(*this);
        if (block->blockItemList[i]->stmt && (block->blockItemList[i]->stmt->block ||
                                              block->blockItemList[i]->stmt->selectStmt ||
                                              block->blockItemList[i]->stmt->iterationStmt)) {
            cur_bb = new NormalBlock(cur_bb, cur_func->bbCnt++);
            pushBB(cur_bb);
        }
    }
    cur_bb = cur_bb->parent;
}

void IrVisitor::visit(BlockItemList *blockItemList) {}

void IrVisitor::visit(BlockItem *blockItem) {
    if (blockItem->varDecl || blockItem->constDecl || (blockItem->stmt &&
                                                       blockItem->stmt->assignStmt || blockItem->stmt->returnStmt ||
                                                       blockItem->stmt->breakStmt)) {
        if (cur_bb == entry) {
            cur_bb = new NormalBlock(cur_bb, cur_func->bbCnt++);
            if (!ifBB.empty()) {
                if (isIF) {
                    ifBB.top()->ifStmt.push_back(cur_bb);
                } else {
                    ifBB.top()->elseStmt.push_back(cur_bb);
                }
            } else {
                cur_func->pushBB(cur_bb);
            }
        }
    }
    if (blockItem->varDecl) {
        blockItem->varDecl->accept(*this);
    } else if (blockItem->constDecl) {
        blockItem->constDecl->accept(*this);
    } else if (blockItem->stmt) {
        blockItem->stmt->accept(*this);
    }
}

void IrVisitor::visit(Stmt *stmt) {
    if (stmt->assignStmt) {
        stmt->assignStmt->accept(*this);
    } else if (stmt->block) {
        stmt->block->accept(*this);
    } else if (stmt->selectStmt) {
        stmt->selectStmt->accept(*this);
    } else if (stmt->iterationStmt) {
        stmt->iterationStmt->accept(*this);
    } else if (stmt->breakStmt) {
        stmt->breakStmt->accept(*this);
    } else if (stmt->returnStmt) {
        stmt->returnStmt->accept(*this);
    }
}

void IrVisitor::visit(AssignStmt *assignStmt) {
    assignStmt->lVal->accept(*this);
    auto left = tempVal;
    assignStmt->exp->accept(*this);
    if (useConst) {
        if (left->type == TYPE::INTPOINTER) {
            if (curValType == TYPE::INT) {
                StoreIIR *ir = new StoreIIR(left, tempInt);
                cur_bb->pushIr(ir);
            } else {
                StoreIIR *ir = new StoreIIR(left, tempFloat);
                cur_bb->pushIr(ir);
            }
        } else {
            if (curValType == TYPE::INT) {
                StoreFIR *ir = new StoreFIR(left, tempInt);
                cur_bb->pushIr(ir);
            } else {
                StoreFIR *ir = new StoreFIR(left, tempFloat);
                cur_bb->pushIr(ir);
            }
        }
    } else {
        //CAST
        if (left->type == TYPE::INTPOINTER && tempVal->type == TYPE::FLOAT) {
            VarValue *t = nullptr;
            if (!isGlobal()) {
                t = new VarValue(cur_func->varCnt++, "", TYPE::INT);
            } else {
                t = new VarValue(cnt++, "", TYPE::INT);
            }
            CastFloat2IntIR *ir = new CastFloat2IntIR(t, tempVal);
            cur_bb->pushIr(ir);
            tempVal = t;
        } else if (left->type == TYPE::FLOATPOINTER && tempVal->type == TYPE::INT) {
            VarValue *t = nullptr;
            if (!isGlobal()) {
                t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
            } else {
                t = new VarValue(cnt++, "", TYPE::FLOAT);
            }
            CastInt2FloatIR *ir = new CastInt2FloatIR(t, tempVal);
            cur_bb->pushIr(ir);
            tempVal = t;
        }
        //STORE
        if (left->type == TYPE::INT) {
            StoreIIR *ir = new StoreIIR(left, tempVal);
            cur_bb->pushIr(ir);
        } else {
            StoreFIR *ir = new StoreFIR(left, tempVal);
            cur_bb->pushIr(ir);
        }
    }
}

void IrVisitor::visit(SelectStmt *selectStmt) {
    auto tempBB = cur_bb;
    cur_bb = new SelectBlock(cur_bb, cur_func->bbCnt++);
    pushBB(cur_bb);
    ifBB.push(dynamic_cast<SelectBlock *>(cur_bb));
    selectStmt->cond->accept(*this);
    isIF = true;
    selectStmt->ifStmt->accept(*this);
    if (selectStmt->elseStmt) {
        isIF = false;
        selectStmt->elseStmt->accept(*this);
    }
    cur_bb = tempBB;
    ifBB.pop();
}

void IrVisitor::visit(IterationStmt *iterationStmt) {
    auto tempBB = cur_bb;
    cur_bb = new IterationBlock(cur_bb, cur_func->bbCnt++);
    pushBB(cur_bb);
    whileBB.push(dynamic_cast<IterationBlock *>(cur_bb));
    iterationStmt->cond->accept(*this);
    iterationStmt->stmt->accept(*this);
    cur_bb = tempBB;
    whileBB.pop();
}

void IrVisitor::visit(BreakStmt *breakStmt) {}

void IrVisitor::visit(ContinueStmt *continueStmt) {}

void IrVisitor::visit(ReturnStmt *returnStmt) {}

void IrVisitor::visit(Exp *exp) {
    exp->addExp->accept(*this);
}

void IrVisitor::visit(Cond *cond) {
    cond->lOrExp->accept(*this);
//    if (useConst) {
//        useConst = false;
//        if ((curDefType == TYPE::INT && tempInt != 0) ||
//            (curDefType == TYPE::FLOAT && tempFloat != 0)) {
//            tempVal = new Value(varCnt++, "", TYPE::INT, true, false, 1, 1);
//        } else {
//            tempVal = new Value(varCnt++, "", TYPE::INT, true, false, 0, 1);
//        }
//    }
}

void IrVisitor::visit(LVal *lVal) {
    if (lVal->expList.empty()) {
        tempVal = findAllVal(lVal->identifier);
        if (!tempVal) {
            std::cerr << "Undefined Identifier of " << lVal->identifier << std::endl;
        }
        if (typeid(*tempVal) == typeid(ConstValue)) {
            useConst = true;
            if (tempVal->type == TYPE::INT) {
                curValType = TYPE::INT;
                tempInt = dynamic_cast<ConstValue *>(tempVal)->intVal;
            } else {
                curValType = TYPE::FLOAT;
                tempFloat = dynamic_cast<ConstValue *>(tempVal)->floatVal;
            }
        } else {
            useConst = false;
        }
    } else {

    }
}

void IrVisitor::visit(PrimaryExp *primaryExp) {
    if (primaryExp->exp) {
        primaryExp->exp->accept(*this);
    } else if (primaryExp->lVal) {
        primaryExp->lVal->accept(*this);
        useConst = false;
        if (tempVal->type == TYPE::INTPOINTER) {
            VarValue *v = nullptr;
            if (!isGlobal()) {
                v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
            } else {
                v = new VarValue(cnt++, "", TYPE::INT);
            }
            LoadIIR *ir = new LoadIIR(v, tempVal);
            tempVal = v;
            cur_bb->pushIr(ir);
        } else if (tempVal->type == TYPE::FLOATPOINTER) {
            VarValue *v = nullptr;
            if (!isGlobal()) {
                v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
            } else {
                v = new VarValue(cnt++, "", TYPE::FLOAT);
            }
            LoadFIR *ir = new LoadFIR(v, tempVal);
            tempVal = v;
            cur_bb->pushIr(ir);
        }
    } else if (primaryExp->number) {
        primaryExp->number->accept(*this);
    }
}

void IrVisitor::visit(Number *number) {
    if (number->type == type_specifier::TYPE_FLOAT) {
        tempFloat = number->floatNum;
        curValType = TYPE::FLOAT;
    } else if (number->type == type_specifier::TYPE_INT) {
        tempInt = number->intNum;
        curValType = TYPE::INT;
    }
    useConst = true;
}

void IrVisitor::visit(UnaryExp *unaryExp) {
    if (unaryExp->primaryExp) {
        unaryExp->primaryExp->accept(*this);
    } else if (unaryExp->unaryExp) {
        unaryExp->unaryExp->accept(*this);
        if (useConst) {
            useConst = true;
            if (unaryExp->unaryOp->op == unaryop::OP_POS) {

            } else if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                tempInt = -tempInt;
                tempFloat = -tempFloat;
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                tempInt = !tempInt;
                tempFloat = !tempFloat;
            }
        } else {
            useConst = false;
            VarValue *v = nullptr;
            if (tempVal->type == TYPE::INT) {
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }
            } else {
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
            }
            if (unaryExp->unaryOp->op == unaryop::OP_POS) {
                UnaryIR *ir = new UnaryIR(v, tempVal, OP::POS);
                cur_bb->pushIr(ir);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                UnaryIR *ir = new UnaryIR(v, tempVal, OP::NEG);
                cur_bb->pushIr(ir);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                UnaryIR *ir = new UnaryIR(v, tempVal, OP::NOT);
                cur_bb->pushIr(ir);
            }
            tempVal = v;
        }
    } else {

    }
}

void IrVisitor::visit(FuncRParams *funcRParams) {}

void IrVisitor::visit(MulExp *mulExp) {
    if (!mulExp->mulExp) {
        mulExp->unaryExp->accept(*this);
    } else {
        mulExp->mulExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        TYPE lt = curValType;
        bool lUseConst = useConst;
        mulExp->unaryExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            assert(!(mulExp->op == mulop::OP_MOD &&
                     (lt == TYPE::FLOAT || rt == TYPE::FLOAT)));
            if (lt == TYPE::FLOAT && rt == TYPE::FLOAT) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = lf * rf;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempFloat = lf / rf;
                }
            } else if (lt == TYPE::INT & rt == TYPE::INT) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempInt = li * ri;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempInt = li / ri;
                } else if (mulExp->op == mulop::OP_MOD) {
                    tempInt = li % ri;
                }
            } else if (lt == TYPE::FLOAT) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = lf * ri;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempFloat = lf / ri;
                }
                curValType = TYPE::FLOAT;
            } else if (lt == TYPE::INT) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = li * rf;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempFloat = li / rf;
                }
                curValType = TYPE::FLOAT;
            }
        } else if (lUseConst && !rUseConst) {
            if (lt == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir = new MulFIR(v, li, right);
                        break;
                    case mulop::OP_DIV:
                        ir = new DivFIR(v, li, right);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::INT && right->type == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }
                Instruction *ir = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir = new MulIIR(v, li, right);
                        break;
                    case mulop::OP_DIV:
                        ir = new DivIIR(v, li, right);
                        break;
                    case mulop::OP_MOD:
                        ir = new ModIIR(v, li, right);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }
                Instruction *ir = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir = new MulFIR(v, lf, right);
                        break;
                    case mulop::OP_DIV:
                        ir = new DivFIR(v, lf, right);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    t = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, right);
                cur_bb->pushIr(ir1);
                right = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir2 = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir2 = new MulFIR(v, lf, right);
                        break;
                    case mulop::OP_DIV:
                        ir2 = new DivFIR(v, lf, right);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir2);
            }
        } else if (!lUseConst && rUseConst) {
            if (left->type == TYPE::INT && rt == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }
                Instruction *ir = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir = new MulIIR(v, left, ri);
                        break;
                    case mulop::OP_DIV:
                        ir = new DivIIR(v, left, ri);
                        break;
                    case mulop::OP_MOD:
                        ir = new ModIIR(v, left, ri);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::INT && rt == TYPE::FLOAT) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    t = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, left);
                cur_bb->pushIr(ir1);
                left = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir2 = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir2 = new MulFIR(v, left, rf);
                        break;
                    case mulop::OP_DIV:
                        ir2 = new DivFIR(v, left, rf);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir2);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir = new MulFIR(v, left, ri);
                        break;
                    case mulop::OP_DIV:
                        ir = new DivFIR(v, left, ri);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (mulExp->op) {
                    case mulop::OP_MUL:
                        ir = new MulFIR(v, left, rf);
                        break;
                    case mulop::OP_DIV:
                        ir = new DivFIR(v, left, rf);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        } else if (!lUseConst && !rUseConst) {
            if (left->type == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, left);
                cur_bb->pushIr(ir);
                left = v;
            } else if (left->type == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, right);
                cur_bb->pushIr(ir);
                right = v;
            }
            VarValue *v = nullptr;
            if (!isGlobal()) {
                if (left->type == TYPE::INT) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                }
            } else {
                if (left->type == TYPE::INT) {
                    v = new VarValue(cnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
            }
            Instruction *ir = nullptr;
            switch (mulExp->op) {
                case mulop::OP_MUL:
                    ir = new MulIR(v, left, right);
                    break;
                case mulop::OP_DIV:
                    ir = new DivIR(v, left, right);
                    break;
                case mulop::OP_MOD:
                    ir = new ModIR(v, left, right);
                    break;
            }
            tempVal = v;
            cur_bb->pushIr(ir);
        }
    }
}

void IrVisitor::visit(AddExp *addExp) {
    if (!addExp->addExp) {
        addExp->mulExp->accept(*this);
    } else {
        addExp->addExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        TYPE lt = curValType;
        bool lUseConst = useConst;
        addExp->mulExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            if (lt == TYPE::FLOAT && rt == TYPE::FLOAT) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = lf + rf;
                } else if (addExp->op == addop::OP_SUB) {
                    tempFloat = lf - rf;
                }
            } else if (lt == TYPE::INT & rt == TYPE::INT) {
                if (addExp->op == addop::OP_ADD) {
                    tempInt = li + ri;
                } else if (addExp->op == addop::OP_SUB) {
                    tempInt = li - ri;
                }
            } else if (lt == TYPE::FLOAT) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = lf + ri;
                } else if (addExp->op == addop::OP_SUB) {
                    tempFloat = lf - ri;
                }
                curValType = TYPE::FLOAT;
            } else if (lt == TYPE::INT) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = li + rf;
                } else if (addExp->op == addop::OP_SUB) {
                    tempFloat = li - rf;
                }
                curValType = TYPE::FLOAT;
            }
        } else if (lUseConst && !rUseConst) {
            if (lt == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir = new AddFIR(v, li, right);
                        break;
                    case addop::OP_SUB:
                        ir = new SubFIR(v, li, right);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::INT && right->type == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }
                Instruction *ir = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir = new AddIIR(v, li, right);
                        break;
                    case addop::OP_SUB:
                        ir = new SubIIR(v, li, right);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir = new AddFIR(v, lf, right);
                        break;
                    case addop::OP_SUB:
                        ir = new SubFIR(v, lf, right);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    t = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, right);
                cur_bb->pushIr(ir1);
                right = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir2 = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir2 = new AddFIR(v, lf, right);
                        break;
                    case addop::OP_SUB:
                        ir2 = new SubFIR(v, lf, right);
                        break;
                    default:
                        std::cerr << "float should not be one operator of mod!" << std::endl;
                }
                tempVal = v;
                cur_bb->pushIr(ir2);
            }
        } else if (!lUseConst && rUseConst) {
            if (left->type == TYPE::INT && rt == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }
                Instruction *ir = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir = new AddIIR(v, left, ri);
                        break;
                    case addop::OP_SUB:
                        ir = new SubIIR(v, left, ri);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::INT && rt == TYPE::FLOAT) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    t = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, left);
                cur_bb->pushIr(ir1);
                left = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir2 = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir2 = new AddFIR(v, left, rf);
                        break;
                    case addop::OP_SUB:
                        ir2 = new SubFIR(v, left, rf);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir2);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir = new AddFIR(v, left, ri);
                        break;
                    case addop::OP_SUB:
                        ir = new SubFIR(v, left, ri);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                Instruction *ir = nullptr;
                switch (addExp->op) {
                    case addop::OP_ADD:
                        ir = new AddFIR(v, left, rf);
                        break;
                    case addop::OP_SUB:
                        ir = new SubFIR(v, left, rf);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        } else if (!lUseConst && !rUseConst) {
            if (left->type == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, left);
                cur_bb->pushIr(ir);
                left = v;
            } else if (left->type == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                } else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, right);
                cur_bb->pushIr(ir);
                right = v;
            }
            VarValue *v = nullptr;
            if (!isGlobal()) {
                if (left->type == TYPE::INT) {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                }else {
                    v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                }
            } else {
                if (left->type == TYPE::INT) {
                    v = new VarValue(cnt++, "", TYPE::INT);
                }else {
                    v = new VarValue(cnt++, "", TYPE::FLOAT);
                }
            }
            Instruction *ir = nullptr;
            switch (addExp->op) {
                case addop::OP_ADD:
                    ir = new AddIR(v, left, right);
                    break;
                case addop::OP_SUB:
                    ir = new SubIR(v, left, right);
                    break;
            }
            tempVal = v;
            cur_bb->pushIr(ir);

        }
    }
}

void IrVisitor::visit(RelExp *relExp) {
//    if (!relExp->relExp) {
//        relExp->addExp->accept(*this);
//    }else {
//        relExp->relExp->accept(*this);
//        auto left = tempVal;
//        int li = tempInt;
//        float lf = tempFloat;
//        TYPE lt = curValType;
//        bool lUseConst = useConst;
//        relExp->addExp->accept(*this);
//        auto right = tempVal;
//        int ri = tempInt;
//        float rf = tempFloat;
//        TYPE rt = curValType;
//        bool rUseConst = useConst;
//        if (lUseConst && rUseConst) {
//            useConst = true;
//            float x = 0;
//            float y = 0;
//            if (lt == TYPE::INT && rt == TYPE::INT) {
//                x = li;
//                y = ri;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT) {
//                x = lf;
//                y = lf;
//            }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
//                x = li;
//                y = rf;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::INT) {
//                x = lf;
//                y = ri;
//            }
//            if (relExp->op == relop::OP_LT) {
//                tempInt = (x < y);
//            }else if (relExp->op == relop::OP_GT){
//                tempInt = (x > y);
//            }else if (relExp->op == relop::OP_LE) {
//                tempInt = (x <= y);
//            }else if (relExp->op == relop::OP_GE){
//                tempInt = (x >= y);
//            }
//            curDefType = TYPE::INT;
//        }else {
//            useConst = false;
//            auto ir = new Instruction;
//            if (lUseConst) {
//                if (lt == TYPE::INT) {
//                    left = new Value("",TYPE::INT,true,false,li,0);
//                    new AllocIIR(left,cur_bb);
//                }else if (lt == TYPE::FLOAT) {
//                    left = new Value("",TYPE::FLOAT,true,false,0,lf);
//                    new AllocFIR(left,cur_bb);
//                }
//            }
//            if (rUseConst) {
//                if (rt == TYPE::INT) {
//                    right = new Value("",TYPE::INT,true,false,li,0);
//                    new AllocIIR(right,cur_bb);
//                }else if (rt == TYPE::FLOAT) {
//                    right = new Value("",TYPE::FLOAT,true,false,0,lf);
//                    new AllocFIR(right,cur_bb);
//                }
//            }
//            if (left->type != right->type) {
//                if (left->type == TYPE::FLOAT) {
//                    auto v = new Value(right);
//                    v->type = TYPE::FLOAT;
//                    new CastInt2FloatIR(v,right,cur_bb);
//                    right = v;
//                } else {
//                    auto v = new Value(left);
//                    v->type = TYPE::FLOAT;
//                    new CastInt2FloatIR(v,left,cur_bb);
//                    left = v;
//                }
//                if (relExp->op == relop::OP_LT) {
//                    tempVal = Instruction::CreateCmpLtFIR(left,right,ir);
//                } else if (relExp->op == relop::OP_GT){
//                    tempVal = Instruction::CreateCmpGtFIR(left,right,ir);
//                }else if (relExp->op == relop::OP_LE){
//                    tempVal = Instruction::CreateCmpLeFIR(left,right,ir);
//                }else if (relExp->op == relop::OP_GE){
//                    tempVal = Instruction::CreateCmpGeFIR(left,right,ir);
//                }
//                cur_bb->pushIr(ir);
//            } else {
//                if (left->type == TYPE::INT) {
//                    if (relExp->op == relop::OP_LT) {
//                        tempVal = Instruction::CreateCmpLtIIR(left,right,ir);
//                    } else if (relExp->op == relop::OP_GT){
//                        tempVal = Instruction::CreateCmpGtIIR(left,right,ir);
//                    }else if (relExp->op == relop::OP_LE){
//                        tempVal = Instruction::CreateCmpLeIIR(left,right,ir);
//                    }else if (relExp->op == relop::OP_GE){
//                        tempVal = Instruction::CreateCmpGeIIR(left,right,ir);
//                    }
//                } else {
//                    if (relExp->op == relop::OP_LT) {
//                        tempVal = Instruction::CreateCmpLtFIR(left,right,ir);
//                    } else if (relExp->op == relop::OP_GT){
//                        tempVal = Instruction::CreateCmpGtFIR(left,right,ir);
//                    }else if (relExp->op == relop::OP_LE){
//                        tempVal = Instruction::CreateCmpLeFIR(left,right,ir);
//                    }else if (relExp->op == relop::OP_GE){
//                        tempVal = Instruction::CreateCmpGeFIR(left,right,ir);
//                    }
//                }
//                cur_bb->pushIr(ir);
//            }
//        }
//    }
}

void IrVisitor::visit(EqExp *eqExp) {
//    if (!eqExp->eqExp) {
//        eqExp->relExp->accept(*this);
//    }else {
//        eqExp->eqExp->accept(*this);
//        auto left = tempVal;
//        int li = tempInt;
//        float lf = tempFloat;
//        TYPE lt = curValType;
//        bool lUseConst = useConst;
//        eqExp->relExp->accept(*this);
//        auto right = tempVal;
//        int ri = tempInt;
//        float rf = tempFloat;
//        TYPE rt = curValType;
//        bool rUseConst = useConst;
//        if (lUseConst && rUseConst) {
//            useConst = true;
//            float x = 0;
//            float y = 0;
//            if (lt == TYPE::INT && rt == TYPE::INT) {
//                x = li;
//                y = ri;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT) {
//                x = lf;
//                y = lf;
//            }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
//                x = li;
//                y = rf;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::INT) {
//                x = lf;
//                y = ri;
//            }
//            if (eqExp->op == relop::OP_EQU) {
//                tempInt = (x == y);
//            }else if (eqExp->op == relop::OP_NE){
//                tempInt = (x != y);
//            }
//            curDefType = TYPE::INT;
//        }else {
//            useConst = false;
//            auto ir = new Instruction;
//            if (lUseConst) {
//                if (lt == TYPE::INT) {
//                    left = Instruction::CreateAllocIIR("",true,false,li,ir);
//                }else if (lt == TYPE::FLOAT) {
//                    left = Instruction::CreateAllocFIR("",true,false,lf,ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//            }
//            if (rUseConst) {
//                if (rt == TYPE::INT) {
//                    right = Instruction::CreateAllocIIR("",true,false,ri,ir);
//                }else if (rt == TYPE::FLOAT) {
//                    right = Instruction::CreateAllocFIR("",true,false,rf,ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//            }
//            if (left->type != right->type) {
//                if (left->type == TYPE::FLOAT) {
//                    right = Instruction::CreateCastInt2FloatIR(right, ir);
//                } else {
//                    left = Instruction::CreateCastInt2FloatIR(left, ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//                if (eqExp->op == relop::OP_EQU) {
//                    tempVal = Instruction::CreateCmpEqFIR(left,right,ir);
//                } else if (eqExp->op == relop::OP_NE) {
//                    tempVal = Instruction::CreateCmpNeFIR(left,right,ir);
//                }
//                cur_bb->pushIr(ir);
//            } else {
//                if (left->type == TYPE::INT) {
//                    if (eqExp->op == relop::OP_EQU) {
//                        tempVal = Instruction::CreateCmpEqIIR(left,right,ir);
//                    }else if (eqExp->op == relop::OP_NE){
//                        tempVal = Instruction::CreateCmpNeIIR(left,right,ir);
//                    }
//                } else {
//                    if (eqExp->op == relop::OP_EQU) {
//                        tempVal = Instruction::CreateCmpEqFIR(left,right,ir);
//                    }else if (eqExp->op == relop::OP_NE){
//                        tempVal = Instruction::CreateCmpNeFIR(left,right,ir);
//                    }
//                }
//                cur_bb->pushIr(ir);
//            }
//        }
//    }
}

void IrVisitor::visit(LAndExp *lAndEXp) {
//    if (!lAndEXp->lAndExp) {
//        lAndEXp->eqExp->accept(*this);
//    }else {
//        lAndEXp->lAndExp->accept(*this);
//        auto left = tempVal;
//        int li = tempInt;
//        float lf = tempFloat;
//        TYPE lt = curValType;
//        bool lUseConst = useConst;
//        lAndEXp->eqExp->accept(*this);
//        auto right = tempVal;
//        int ri = tempInt;
//        float rf = tempFloat;
//        TYPE rt = curValType;
//        bool rUseConst = useConst;
//        if (lUseConst && rUseConst) {
//            useConst = true;
//            float x = 0;
//            float y = 0;
//            if (lt == TYPE::INT && rt == TYPE::INT) {
//                x = li;
//                y = ri;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT) {
//                x = lf;
//                y = lf;
//            }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
//                x = li;
//                y = rf;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::INT) {
//                x = lf;
//                y = ri;
//            }
//            tempInt = (x && y);
//            curDefType = TYPE::INT;
//        }else {
//            useConst = false;
//            auto ir = new Instruction;
//            if (lUseConst) {
//                if (lt == TYPE::INT) {
//                    left = Instruction::CreateAllocIIR("",true,false,li,ir);
//                }else if (lt == TYPE::FLOAT) {
//                    left = Instruction::CreateAllocFIR("",true,false,lf,ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//            }
//            if (rUseConst) {
//                if (rt == TYPE::INT) {
//                    right = Instruction::CreateAllocIIR("",true,false,ri,ir);
//                }else if (rt == TYPE::FLOAT) {
//                    right = Instruction::CreateAllocFIR("",true,false,rf,ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//            }
//            if (left->type != right->type) {
//                if (left->type == TYPE::FLOAT) {
//                    right = Instruction::CreateCastInt2FloatIR(right, ir);
//                } else {
//                    left = Instruction::CreateCastInt2FloatIR(left, ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//                tempVal = Instruction::CreateAndFIR(left,right,ir);
//                cur_bb->pushIr(ir);
//            } else {
//                if (left->type == TYPE::INT) {
//                    tempVal = Instruction::CreateAndIIR(left,right,ir);
//                } else {
//                    tempVal = Instruction::CreateAndFIR(left,right,ir);
//                }
//                cur_bb->pushIr(ir);
//            }
//        }
//    }
}

void IrVisitor::visit(LOrExp *lOrExp) {
//    if (!lOrExp->lOrExp) {
//        lOrExp->lAndExp->accept(*this);
//    }else {
//        lOrExp->lOrExp->accept(*this);
//        auto left = tempVal;
//        int li = tempInt;
//        float lf = tempFloat;
//        TYPE lt = curValType;
//        bool lUseConst = useConst;
//        lOrExp->lAndExp->accept(*this);
//        auto right = tempVal;
//        int ri = tempInt;
//        float rf = tempFloat;
//        TYPE rt = curValType;
//        bool rUseConst = useConst;
//        if (lUseConst && rUseConst) {
//            useConst = true;
//            float x = 0;
//            float y = 0;
//            if (lt == TYPE::INT && rt == TYPE::INT) {
//                x = li;
//                y = ri;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT) {
//                x = lf;
//                y = lf;
//            }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
//                x = li;
//                y = rf;
//            }else if (lt == TYPE::FLOAT && rt == TYPE::INT) {
//                x = lf;
//                y = ri;
//            }
//            tempInt = (x || y);
//            curDefType = TYPE::INT;
//        }else {
//            useConst = false;
//            auto ir = new Instruction;
//            if (lUseConst) {
//                if (lt == TYPE::INT) {
//                    left = Instruction::CreateAllocIIR("",true,false,li,ir);
//                }else if (lt == TYPE::FLOAT) {
//                    left = Instruction::CreateAllocFIR("",true,false,lf,ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//            }
//            if (rUseConst) {
//                if (rt == TYPE::INT) {
//                    right = Instruction::CreateAllocIIR("",true,false,ri,ir);
//                }else if (rt == TYPE::FLOAT) {
//                    right = Instruction::CreateAllocFIR("",true,false,rf,ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//            }
//            if (left->type != right->type) {
//                if (left->type == TYPE::FLOAT) {
//                    right = Instruction::CreateCastInt2FloatIR(right, ir);
//                } else {
//                    left = Instruction::CreateCastInt2FloatIR(left, ir);
//                }
//                cur_bb->pushIr(ir);
//                ir = new Instruction;
//                tempVal = Instruction::CreateOrFIR(left,right,ir);
//                cur_bb->pushIr(ir);
//            } else {
//                if (left->type == TYPE::INT) {
//                    tempVal = Instruction::CreateOrIIR(left,right,ir);
//                } else {
//                    tempVal = Instruction::CreateOrFIR(left,right,ir);
//                }
//                cur_bb->pushIr(ir);
//            }
//        }
//    }
}

void IrVisitor::visit(ConstExp *constExp) {
    constExp->addExp->accept(*this);
}

void IrVisitor::visit(UnaryOp *unaryOp) {}