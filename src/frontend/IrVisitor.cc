//
// Created by hangshu on 22-4-26.
//
#include "IrVisitor.hh"
#include <iostream>
#include "errors/errors.hh"
void IrVisitor::visit(CompUnit *compUnit) {
    for (size_t i = 0; i < compUnit->declDefList.size(); ++i) {
        compUnit->declDefList[i]->accept(*this);
    }
    bool foundMain = false;
    for (size_t i = 0; i < functions.size(); ++i) {
        functions[i]->clear();
        if (functions[i]->name == "main") {
            foundMain = true;
            if (functions[i]->return_type != TYPE::INT) {
                throw MainReturnError();
            }
            if (functions[i]->params.size() > 0){
                throw MainWithArgsError();
            }
        }
    }
    if (!foundMain) {
        throw MainNotFoundError();
    }
}

void IrVisitor::visit(DeclDef *declDef) {
    if (declDef->varDecl) {
        declDef->varDecl->accept(*this);
    } else if (declDef->funcDef) {
        declDef->funcDef->accept(*this);
    } else if (declDef->constDecl) {
        declDef->constDecl->accept(*this);
    }
}

void IrVisitor::visit(ConstDecl *constDecl) {
    if (constDecl->defType->type == type_specifier::TYPE_INT) {
        curDefType = TYPE::INT;
    } else if (constDecl->defType->type == type_specifier::TYPE_FLOAT) {
        curDefType = TYPE::FLOAT;
    } else {
        throw ValueTypeError();
    }
    for (size_t i = 0; i < constDecl->constDefList.size(); ++i) {
        constDecl->constDefList[i]->accept(*this);
    }
}

void IrVisitor::visit(ConstDef *constDef) {
    if (constDef->constExpList.empty()) {
        constDef->constInitVal->accept(*this);
        if (!useConst) {
            throw ConstNotInitError();
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
        pushVars(var);
    } else {
        ConstValue *var(nullptr);
        std::vector<int> arrayDims;
        int arrayLen(1);
        for (size_t i(0); i < constDef->constExpList.size(); i++) {
            constDef->constExpList[i]->accept(*this);
            arrayDims.push_back(tempInt);
            arrayLen *= tempInt;
        }

        if (curDefType == TYPE::INT) {
            if (!isGlobal()) {
                var = new ConstValue(cur_func->varCnt++, constDef->identifier, TYPE::INT);
            } else {
                var = new ConstValue(0, constDef->identifier, TYPE::INT);
            }
            AllocIIR *ir = new AllocIIR(var, arrayLen);
            cur_bb->pushIr(ir);
        } else {
            if (!isGlobal()) {
                var = new ConstValue(cur_func->varCnt++, constDef->identifier, TYPE::FLOAT);
            } else {
                var = new ConstValue(0, constDef->identifier, TYPE::FLOAT);
            }
            AllocFIR *ir = new AllocFIR(var, arrayLen);
            cur_bb->pushIr(ir);
        }
        var->isArray = true;
        var->arrayDims = arrayDims;

        pushVars(var);

        if (constDef->constInitVal) {
            tempDims = constDef->constExpList.size();
            tempVal = var;
            constDef->constInitVal->accept(*this);
        }
    }
}

void IrVisitor::visit(ConstDefList *constDefList) {}

void IrVisitor::visit(ConstExpList *constExpList) {}

void IrVisitor::visit(ConstInitVal *constInitVal) {
    if (constInitVal->constExp) {
        constInitVal->constExp->accept(*this);
    } else {
        static int dims(0), index(0);
        dims++;
        static ConstValue *var = nullptr;
        static bool flag = true;
        if (flag && dims == tempDims) {
            var = dynamic_cast<ConstValue *>(tempVal);
            var->isArray = true;
            flag = false;
        }
        for (size_t i = 0; i < constInitVal->constInitValList.size(); ++i) {
            constInitVal->constInitValList[i]->accept(*this);
            if (useConst && dims == tempDims) {
                if (var->type == TYPE::INT) {
                    if (curValType == TYPE::INT) {
                        var->push(tempInt);
                        StoreIIR *ir = new StoreIIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push(tempFloat);
                        StoreIIR *ir = new StoreIIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                } else {
                    if (curValType == TYPE::INT) {
                        var->push(tempInt);
                        StoreFIR *ir = new StoreFIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push(tempFloat);
                        StoreFIR *ir = new StoreFIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                }
            } else if (!useConst && dims == tempDims) {
                VarValue *t = nullptr;
                if (var->type == TYPE::INT && tempVal->type == TYPE::FLOAT) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                    } else {
                        t = new VarValue(0, "", TYPE::INT);
                    }
                    CastFloat2IntIR *ir = new CastFloat2IntIR(t, tempVal);
                    cur_bb->pushIr(ir);
                } else if (var->type == TYPE::FLOAT && tempVal->type == TYPE::INT) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                    } else {
                        t = new VarValue(0, "", TYPE::FLOAT);
                    }
                    CastInt2FloatIR *ir = new CastInt2FloatIR(t, tempVal);
                    cur_bb->pushIr(ir);
                }
                if (var->type == TYPE::INT) {
                    var->push(0);
                    StoreIIR *ir = new StoreIIR(var, t, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push(0);
                    StoreFIR *ir = new StoreFIR(var, t, index++);
                    cur_bb->pushIr(ir);
                }
            }
        }

        if(!flag && var->arrayDims[dims - 1] - constInitVal->constInitValList.size())
        {
            int cnt(var->arrayDims[dims - 1] - constInitVal->constInitValList.size());
            for(int i(dims); i < tempDims; i++)
            {
                cnt *= var->arrayDims[i];
            }
            
            index += cnt;
        }

        dims--;

        if (dims == 0) {
            tempVal = var;
            var = nullptr;
            index = 0;
            flag = true;
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
        throw ValueTypeError();
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
                AllocIIR *ir = new AllocIIR(var);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, TYPE::INTPOINTER);
            }
        } else {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, TYPE::FLOATPOINTER);
                AllocFIR *ir = new AllocFIR(var);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, TYPE::FLOATPOINTER);
            }
        }
        pushVars(var);
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
        VarValue *var(nullptr);
        std::vector<int> arrayDims;
        int arrayLen(1);

        for (size_t i(0); i < varDef->constExpList.size(); i++) {
            varDef->constExpList[i]->accept(*this);
            arrayDims.push_back(tempInt);
            arrayLen *= tempInt;
        }

        if (curDefType == TYPE::INT) {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, TYPE::INTPOINTER);
                AllocIIR *ir = new AllocIIR(var, arrayLen);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, TYPE::INTPOINTER);
            }
        } else {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, TYPE::FLOATPOINTER);
                AllocFIR *ir = new AllocFIR(var, arrayLen);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, TYPE::FLOATPOINTER);
            }
        }
        var->isArray = true;
        var->arrayDims = arrayDims;

        pushVars(var);
        if (varDef->initVal) {
            tempDims = varDef->constExpList.size();
            tempVal = var;
            varDef->initVal->accept(*this);
        }

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
        static int dims(0), index(0);
        dims++;
        static VarValue *var = nullptr;
        static bool flag = true;
        if (flag && dims == tempDims) {
            var = dynamic_cast<VarValue *>(tempVal);
            var->isArray = true;
            flag = false;
        }
        for (size_t i = 0; i < initVal->initValList.size(); ++i) {
            initVal->initValList[i]->accept(*this);
            if (useConst && dims == tempDims) {
                if (var->type == TYPE::INTPOINTER) {
                    if (curValType == TYPE::INT) {
                        var->push();
                        StoreIIR *ir = new StoreIIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push();
                        StoreIIR *ir = new StoreIIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                } else {
                    if (curValType == TYPE::INT) {
                        var->push();
                        StoreFIR *ir = new StoreFIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push();
                        StoreFIR *ir = new StoreFIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                }
            } else if (!useConst && dims == tempDims) {
                VarValue *t = nullptr;
                if (var->type == TYPE::INTPOINTER && tempVal->type == TYPE::FLOAT) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                    } else {
                        t = new VarValue(0, "", TYPE::INT);
                    }
                    CastFloat2IntIR *ir = new CastFloat2IntIR(t, tempVal);
                    cur_bb->pushIr(ir);
                } else if (var->type == TYPE::FLOATPOINTER && tempVal->type == TYPE::INT) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                    } else {
                        t = new VarValue(0, "", TYPE::FLOAT);
                    }
                    CastInt2FloatIR *ir = new CastInt2FloatIR(t, tempVal);
                    cur_bb->pushIr(ir);
                }
                if (var->type == TYPE::INTPOINTER) {
                    var->push();
                    StoreIIR *ir = new StoreIIR(var, t, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push();
                    StoreFIR *ir = new StoreFIR(var, t, index++);
                    cur_bb->pushIr(ir);
                }
            }
        }

        if(!flag && var->arrayDims[dims - 1] - initVal->initValList.size())
        {
            int cnt(var->arrayDims[dims - 1] - initVal->initValList.size());
            for(int i(dims); i < tempDims; i++)
            {
                cnt *= var->arrayDims[i];
            }
            
            index += cnt;
        }

        dims--;

        if (dims == 0) {
            tempVal = var;
            var = nullptr;
            index = 0;
            flag = true;
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
    pushFunctions(cur_func);
    if (funcDef->funcFParams) {
        funcDef->funcFParams->accept(*this);
        cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
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
        addParam(cur_func,tempVal);
    } else {
        if(funcFParam->defType->type == type_specifier::TYPE_INT)
        {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, TYPE::INTPOINTER);
            tempVal->arrayDims.push_back(0);
            for(auto width : funcFParam->expList)
            {
                width->accept(*this);
                tempVal->arrayDims.push_back(tempInt);
            }
        }
        else if(funcFParam->defType->type == type_specifier::TYPE_FLOAT)
        {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, TYPE::FLOATPOINTER);
            tempVal->arrayDims.push_back(0);
            for(auto width : funcFParam->expList)
            {
                width->accept(*this);
                tempVal->arrayDims.push_back(tempInt);
            }
        }
    }
}

void IrVisitor::visit(ParamArrayExpList *paramArrayExpList) {}

void IrVisitor::visit(Block *block) {
    cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    pushBB();
    for (size_t i = 0; i < block->blockItemList.size(); ++i) {
        block->blockItemList[i]->accept(*this);
        if (block->blockItemList[i]->stmt && (block->blockItemList[i]->stmt->block ||
                                              block->blockItemList[i]->stmt->selectStmt ||
                                              block->blockItemList[i]->stmt->iterationStmt)) {
            cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
            pushBB();
        }
    }
    cur_bb = cur_bb->parent;
}

void IrVisitor::visit(BlockItemList *blockItemList) {}

void IrVisitor::visit(BlockItem *blockItem) {
    if (!blockItem->stmt && !blockItem->constDecl && !blockItem->varDecl) return;
    if (blockItem->varDecl || blockItem->constDecl || (blockItem->stmt &&
                                                       blockItem->stmt->assignStmt || blockItem->stmt->returnStmt ||
                                                       blockItem->stmt->breakStmt)) {
        if (cur_bb == entry) {
            cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
            pushBB();
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
    if (!stmt) return;
    if (stmt->assignStmt) {
        stmt->assignStmt->accept(*this);
    }else if (stmt->exp) {
        stmt->exp->accept(*this);
    }else if (stmt->block) {
        stmt->block->accept(*this);
    }else if (stmt->selectStmt) {
        stmt->selectStmt->accept(*this);
    } else if (stmt->iterationStmt) {
        stmt->iterationStmt->accept(*this);
    } else if (stmt->breakStmt) {
        stmt->breakStmt->accept(*this);
    } else if(stmt->continueStmt) {
        stmt->continueStmt->accept(*this);
    }else if (stmt->returnStmt) {
        stmt->returnStmt->accept(*this);
    }
}

void IrVisitor::visit(AssignStmt *assignStmt) {
    assignStmt->lVal->accept(*this);
    auto left = tempVal;
    if (useConst) {
        throw LValIsConstError();
    }
    int index = tempInt;
    assignStmt->exp->accept(*this);
    if (useConst) {
        if (left->type == TYPE::INTPOINTER) {
            if (curValType == TYPE::INT) {
                StoreIIR* ir;
                if (!left->isArray) {
                    ir = new StoreIIR(left, tempInt);
                }else {
                    ir = new StoreIIR(left,tempInt,index);
                }
                cur_bb->pushIr(ir);
            } else {
                StoreIIR* ir;
                if (!left->isArray) {
                    ir = new StoreIIR(left, tempFloat);
                }else {
                    ir = new StoreIIR(left,tempFloat,index);
                }
                cur_bb->pushIr(ir);
            }
        } else {
            if (curValType == TYPE::INT) {
                StoreFIR* ir;
                if (!left->isArray) {
                    ir = new StoreFIR(left, tempInt);
                }else {
                    ir = new StoreFIR(left,tempInt,index);
                }
                cur_bb->pushIr(ir);
            } else {
                StoreFIR* ir;
                if (!left->isArray) {
                    ir = new StoreFIR(left, tempFloat);
                }else {
                    ir = new StoreFIR(left,tempFloat,index);
                }
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
    cur_bb = new SelectBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    pushBB();
    condBB.push(cur_bb);
    auto temp = cur_bb;
    selectStmt->cond->accept(*this);
    cur_bb = temp;
    isIF = true;
    selectStmt->ifStmt->accept(*this);
    if (selectStmt->elseStmt) {
        isIF = false;
        selectStmt->elseStmt->accept(*this);
    }
    cur_bb = tempBB;
    condBB.pop();
}

void IrVisitor::visit(IterationStmt *iterationStmt) {
    loopCnt++;
    auto tempBB = cur_bb;
    cur_bb = new IterationBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    pushBB();
    condBB.push(cur_bb);
    dynamic_cast<IterationBlock*>(cur_bb)->cond.push_back(new CondBlock(cur_bb, cur_func->name,cur_func->bbCnt++));
    iterationStmt->cond->accept(*this);
    iterationStmt->stmt->accept(*this);
    cur_bb = tempBB;
    condBB.pop();
    loopCnt--;
}

void IrVisitor::visit(BreakStmt *breakStmt) {
    if (!loopCnt) {
        throw BreakError();
    }
    cur_bb->pushIr(new BreakIR);
}

void IrVisitor::visit(ContinueStmt *continueStmt) {
    if (!loopCnt) {
        throw ContinueError();
    }
    cur_bb->pushIr(new ContinueIR);
}

void IrVisitor::visit(ReturnStmt *returnStmt) {
    if (returnStmt->exp) {
        if (cur_func->return_type == TYPE::VOID) {
            throw VoidFuncReturnValueUsedError();
        }
        returnStmt->exp->accept(*this);
        if (useConst) {
            if (curDefType == TYPE::INT) {
                if (curValType == TYPE::INT) {
                    cur_bb->pushIr(new ReturnIR(tempInt));
                } else {
                    cur_bb->pushIr(new ReturnIR((int) tempFloat));
                }
            } else {
                if (curValType == TYPE::INT) {
                    cur_bb->pushIr(new ReturnIR((float) tempInt));
                } else {
                    cur_bb->pushIr(new ReturnIR(tempFloat));
                }
            }
        } else {
            if (curDefType == TYPE::INT && tempVal->type == TYPE::FLOAT) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", TYPE::INT);;
                cur_bb->pushIr(new CastFloat2IntIR(t, tempVal));
                tempVal = t;
            } else if (curDefType == TYPE::FLOAT && tempVal->type == TYPE::INT){
                VarValue *t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);;
                cur_bb->pushIr(new CastInt2FloatIR(t, tempVal));
                tempVal = t;
            }
            cur_bb->pushIr(new ReturnIR(tempVal));
        }
    } else {
        if (cur_func->return_type != TYPE::VOID){
            throw ReturnValueNotFoundError();
        }
        cur_bb->pushIr(new ReturnIR(nullptr));
    }
}

void IrVisitor::visit(Exp *exp) {
    exp->addExp->accept(*this);
}

void IrVisitor::visit(Cond *cond) {
    cond->lOrExp->accept(*this);
    if (useConst) {
        CondBlock* bb = dynamic_cast<CondBlock*>(cur_bb);
        ConstValue* val = nullptr;
        if ((curValType == TYPE::INT && tempInt != 0 )||
            (curValType==TYPE::FLOAT && tempFloat != 0)){
            val = new ConstValue(cur_func->varCnt++,"",TYPE::INT);
            val->setInt(1);
            bb->val = val;
        }else {
            val = new ConstValue(cur_func->varCnt++,"",TYPE::INT);
            val->setInt(0);
            bb->val = val;
        }
    }
}

void IrVisitor::visit(LVal *lVal) {
    if (lVal->expList.empty()) {
        tempVal = findAllVal(lVal->identifier);
        if (!tempVal) {
            throw UndefinedVarError(lVal->identifier);
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
        Value *val = findAllVal(lVal->identifier);
        if (!val->isArray) {
            throw InvalidIndexOperatorError();
        }
        if (!val) {
            throw UndefinedVarError(lVal->identifier);
        }
        int arrayIndex(0), arrayDimLen(1);
        for (int i(lVal->expList.size() - 1); i >= 0; i--) {
            lVal->expList[i]->accept(*this);
            arrayIndex += arrayDimLen * tempInt;
            arrayDimLen *= val->arrayDims[i];
        }

        tempVal = val;
        if (typeid(*val) == typeid(ConstValue)) {
            useConst = true;
            if (tempVal->type == TYPE::INT) {
                curValType = TYPE::INT;
                tempInt = dynamic_cast<ConstValue *>(tempVal)->intValList[arrayIndex];
            } else {
                curValType = TYPE::FLOAT;
                tempFloat = dynamic_cast<ConstValue *>(tempVal)->floatValList[arrayIndex];
            }
        } else {
            useConst = false;
            tempInt = arrayIndex;
        }
    }
}

void IrVisitor::visit(PrimaryExp *primaryExp) {
    if (primaryExp->exp) {
        primaryExp->exp->accept(*this);
    } else if (primaryExp->lVal) {
        primaryExp->lVal->accept(*this);
        if (tempVal->isArray) {
            return;
        }
        if (tempVal->type == TYPE::INTPOINTER) {
            VarValue *v = nullptr;
            if (!isGlobal()) {
                v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
            } else {
                v = new VarValue(cnt++, "", TYPE::INT);
            }
            LoadIIR *ir = nullptr;
            if (tempVal->isArray) {
                ir = new LoadIIR(v, tempVal, tempInt);
            } else ir = new LoadIIR(v, tempVal);
            tempVal = v;
            cur_bb->pushIr(ir);
        } else if (tempVal->type == TYPE::FLOATPOINTER) {
            VarValue *v = nullptr;
            if (!isGlobal()) {
                v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
            } else {
                v = new VarValue(cnt++, "", TYPE::FLOAT);
            }
            LoadFIR *ir = nullptr;
            if (tempVal->isArray) {
                ir = new LoadFIR(v, tempVal, tempInt);
            } else ir = new LoadFIR(v, tempVal);
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
        args.clear();
        if (unaryExp->funcRParams) {
            unaryExp->funcRParams->accept(*this);
        }
        auto f = findFunc(unaryExp->identifier);
        if (f->return_type == TYPE::VOID) {
            cur_bb->pushIr(new CallIR(f,args));
        }else {
            Value* v = nullptr;
            if (f->return_type == TYPE::INT) {
                v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
            } else {
                v = new VarValue(cur_func->varCnt++,"",TYPE::FLOAT);
            }
            useConst = false;
            tempVal = v;
            cur_bb->pushIr(new CallIR(f,args,v));
        }
    }
}

void IrVisitor::visit(FuncRParams *funcRParams) {
    if (funcRParams->expList.size() != cur_func->params.size()) {
        throw ArgsNumberNotMatchError(cur_func->name);
    }
    for (size_t i = 0; i < funcRParams->expList.size(); ++i) {
        funcRParams->expList[i]->accept(*this);
        if (!useConst) {
            TYPE type = cur_func->params[i]->type;
            if ((tempVal->type == TYPE::INTPOINTER || tempVal->type == TYPE::FLOATPOINTER)
            && tempVal->type != type ||
                    (tempVal->type == TYPE::INT || tempVal->type == TYPE::FLOAT) &&
                            (tempVal->type == TYPE::INTPOINTER || tempVal->type == TYPE::FLOATPOINTER))
            {
                throw ArgsTypeNotMatchError(cur_func->name);
            }
            args.push_back(tempVal);
        }else {
            ConstValue* val;
            if (curValType == TYPE::INT) {
                val = new ConstValue(cur_func->varCnt++, "",TYPE::INT);
                val->setInt(tempInt);
            }else {
                val = new ConstValue(cur_func->varCnt++, "",TYPE::FLOAT);
                val->setFloat(tempFloat);
            }
            args.push_back(val);
        }
    }
}

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
    if (!relExp->relExp) {
        relExp->addExp->accept(*this);
    }else {
        relExp->relExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        TYPE lt = curValType;
        bool lUseConst = useConst;
        relExp->addExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            curValType = TYPE::INT;
            switch (relExp->op) {
                case relop::OP_LT:
                    if (lt == TYPE::INT && rt == TYPE::INT) {
                        tempInt = (li < ri);
                    }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                        tempInt = (lf < rf);
                    }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
                        tempInt = (li < rf);
                    }else {
                        tempInt = (lf < ri);
                    }
                    break;
                case relop::OP_GT:
                    if (lt == TYPE::INT && rt == TYPE::INT) {
                        tempInt = (li > ri);
                    }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                        tempInt = (lf > rf);
                    }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
                        tempInt = (li > rf);
                    }else {
                        tempInt = (lf > ri);
                    }
                    break;
                case relop::OP_LE:
                    if (lt == TYPE::INT && rt == TYPE::INT) {
                        tempInt = (li <= ri);
                    }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                        tempInt = (lf <= rf);
                    }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
                        tempInt = (li <= rf);
                    }else {
                        tempInt = (lf <= ri);
                    }
                    break;
                case relop::OP_GE:
                    if (lt == TYPE::INT && rt == TYPE::INT) {
                        tempInt = (li >= ri);
                    }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                        tempInt = (lf >= rf);
                    }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
                        tempInt = (li >= rf);
                    }else {
                        tempInt = (lf >= ri);
                    }
                    break;
            }
        }else if (lUseConst && !rUseConst){
            if (lt == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v,li,right,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v,li,right,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v,li,right,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v,li,right,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::INT && right->type == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::INT);;
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelIIR(v,li,right,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelIIR(v,li,right,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelIIR(v,li,right,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelIIR(v,li,right,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v,lf,right,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v,lf,right,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v,lf,right,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v,lf,right,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(t, right));
                right = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v,lf,right,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v,lf,right,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v,lf,right,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v,lf,right,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        }else if (!lUseConst && rUseConst) {
            if (left->type == TYPE::INT && rt == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelIIR(v,left,ri,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelIIR(v,left,ri,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelIIR(v,left,ri,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelIIR(v,left,ri,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::INT && rt == TYPE::FLOAT) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(t, left));
                left = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v,left,rf,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v,left,rf,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v,left,rf,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v,left,rf,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v,left,ri,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v,left,ri,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v,left,ri,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v,left,ri,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v,left,rf,OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v,left,rf,OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v,left,rf,OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v,left,rf,OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        }else if (!lUseConst && !rUseConst){
            if (left->type == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(v, left));
                left = v;
            } else if (left->type == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(v, right));
                right = v;
            }
            VarValue *v = nullptr;
            if (left->type == TYPE::INT) {
                v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
            } else {
                v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
            }
            Instruction *ir = nullptr;
            switch (relExp->op) {
                case relop::OP_LT:
                    ir = new RelIR(v,left,right,OP::LT);
                    break;
                case relop::OP_GT:
                    ir = new RelIR(v,left,right,OP::GT);
                    break;
                case relop::OP_LE:
                    ir = new RelIR(v,left,right,OP::LE);
                    break;
                case relop::OP_GE:
                    ir = new RelIR(v,left,right,OP::GE);
                    break;
            }
            tempVal = v;
            cur_bb->pushIr(ir);
        }
    }
}

void IrVisitor::visit(EqExp* eqExp) {
    if (!eqExp->eqExp) {
        eqExp->relExp->accept(*this);
    }else {
        eqExp->eqExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        TYPE lt = curValType;
        bool lUseConst = useConst;
        eqExp->relExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            curValType = TYPE::INT;
            switch (eqExp->op) {
                case relop::OP_EQU:
                    if (lt == TYPE::INT && rt == TYPE::INT) {
                        tempInt = (li == ri);
                    }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                        tempInt = (lf == rf);
                    }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
                        tempInt = (li == rf);
                    }else {
                        tempInt = (lf == ri);
                    }
                    break;
                case relop::OP_NE:
                    if (lt == TYPE::INT && rt == TYPE::INT) {
                        tempInt = (li != ri);
                    }else if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                        tempInt = (lf != rf);
                    }else if (lt == TYPE::INT && rt == TYPE::FLOAT) {
                        tempInt = (li != rf);
                    }else {
                        tempInt = (lf != ri);
                    }
                    break;
            }
        }else if (lUseConst && !rUseConst){
            if (lt == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v,li,right,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v,li,right,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::INT && right->type == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::INT);;
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelIIR(v,li,right,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelIIR(v,li,right,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v,lf,right,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v,lf,right,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(t, right));
                right = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v,lf,right,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v,lf,right,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        }else if (!lUseConst && rUseConst) {
            if (left->type == TYPE::INT && rt == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelIIR(v,left,ri,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelIIR(v,left,ri,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::INT && rt == TYPE::FLOAT) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(t, left));
                left = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v,left,rf,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v,left,rf,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v,left,ri,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v,left,ri,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type == TYPE::FLOAT && rt == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v,left,rf,OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v,left,rf,OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        }else if (!lUseConst && !rUseConst){
            if (left->type == TYPE::INT && right->type == TYPE::FLOAT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(v, left));
                left = v;
            } else if (left->type == TYPE::FLOAT && right->type == TYPE::INT) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
                cur_bb->pushIr(new CastInt2FloatIR(v, right));
                right = v;
            }
            VarValue *v = nullptr;
            if (left->type == TYPE::INT) {
                v = new VarValue(cur_func->varCnt++, "", TYPE::INT);
            } else {
                v = new VarValue(cur_func->varCnt++, "", TYPE::FLOAT);
            }
            Instruction *ir = nullptr;
            switch (eqExp->op) {
                case relop::OP_EQU:
                    ir = new RelIR(v,left,right,OP::EQU);
                    break;
                case relop::OP_NE:
                    ir = new RelIR(v,left,right,OP::NE);
                    break;
            }
            tempVal = v;
            cur_bb->pushIr(ir);
        }
    }
}
void IrVisitor::visit(LAndExp *lAndEXp) {
    cur_bb = new CondBlock(cur_bb,cur_func->name,cur_func->bbCnt++);
    if (typeid(*condBB.top()) == typeid(SelectBlock)) {
        dynamic_cast<SelectBlock*>(condBB.top())->cond.push_back(cur_bb);
    }else {
        dynamic_cast<IterationBlock*>(condBB.top())->cond.push_back(cur_bb);
    }
    if (!lAndEXp->lAndExp) {
        lAndEXp->eqExp->accept(*this);
    }else {
        lAndEXp->lAndExp->accept(*this);
        CondBlock* bb = dynamic_cast<CondBlock*>(cur_bb);
        bb->isAnd = true;
        if ((curValType == TYPE::INT && tempInt != 0 )||
            (curValType==TYPE::FLOAT && tempFloat != 0)){
            VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
            cur_bb->pushIr(new AllocIIR(var));
            cur_bb->pushIr(new StoreIIR(var,1));
            VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
            cur_bb->pushIr(new LoadIIR(v,var));
            bb->val = v;
        }else {
            VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
            cur_bb->pushIr(new AllocIIR(var));
            cur_bb->pushIr(new StoreIIR(var,0));
            VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
            cur_bb->pushIr(new LoadIIR(v,var));
            bb->val = v;
        }
        cur_bb = new CondBlock(cur_bb,cur_func->name,cur_func->bbCnt++);
        if (typeid(*condBB.top()) == typeid(SelectBlock)) {
            dynamic_cast<SelectBlock*>(condBB.top())->cond.push_back(cur_bb);
        }else {
            dynamic_cast<IterationBlock*>(condBB.top())->cond.push_back(cur_bb);
        }
        lAndEXp->eqExp->accept(*this);
        bb = dynamic_cast<CondBlock*>(cur_bb);
        if ((curValType == TYPE::INT && tempInt != 0 )||
            (curValType==TYPE::FLOAT && tempFloat != 0)){
            VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
            cur_bb->pushIr(new AllocIIR(var));
            cur_bb->pushIr(new StoreIIR(var,1));
            VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
            cur_bb->pushIr(new LoadIIR(v,var));
            bb->val = v;
        }else {
            VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
            cur_bb->pushIr(new AllocIIR(var));
            cur_bb->pushIr(new StoreIIR(var,0));
            VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
            cur_bb->pushIr(new LoadIIR(v,var));
            bb->val = v;
        }
    }
}

void IrVisitor::visit(LOrExp *lOrExp) {
    cur_bb = new CondBlock(cur_bb,cur_func->name,cur_func->bbCnt++);
    if (typeid(*condBB.top()) == typeid(SelectBlock)) {
        dynamic_cast<SelectBlock*>(condBB.top())->cond.push_back(cur_bb);
    }else {
        dynamic_cast<IterationBlock*>(condBB.top())->cond.push_back(cur_bb);
    }
    if (!lOrExp->lOrExp) {
        lOrExp->lAndExp->accept(*this);
    }else {
        lOrExp->lOrExp->accept(*this);
        CondBlock* bb = dynamic_cast<CondBlock*>(cur_bb);
        bb->isAnd = false;
        if (useConst) {
            if ((curValType == TYPE::INT && tempInt != 0 )||
                (curValType==TYPE::FLOAT && tempFloat != 0)){
                VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var,1));
                VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
                cur_bb->pushIr(new LoadIIR(v,var));
                bb->val = v;
            }else {
                VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var,0));
                VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
                cur_bb->pushIr(new LoadIIR(v,var));
                bb->val = v;
            }
        }else {
            bb->val = tempVal;
        }
        cur_bb = new CondBlock(cur_bb,cur_func->name,cur_func->bbCnt++);
        if (typeid(*condBB.top()) == typeid(SelectBlock)) {
            dynamic_cast<SelectBlock*>(condBB.top())->cond.push_back(cur_bb);
        }else {
            dynamic_cast<IterationBlock*>(condBB.top())->cond.push_back(cur_bb);
        }
        lOrExp->lAndExp->accept(*this);
        bb = dynamic_cast<CondBlock*>(cur_bb);
        if (useConst) {
            if ((curValType == TYPE::INT && tempInt != 0 )||
                (curValType==TYPE::FLOAT && tempFloat != 0)){
                VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var,1));
                VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
                cur_bb->pushIr(new LoadIIR(v,var));
                bb->val = v;
            }else {
                VarValue* var = new VarValue(cur_func->varCnt++,"",TYPE::INTPOINTER);
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var,0));
                VarValue* v = new VarValue(cur_func->varCnt++,"",TYPE::INT);
                cur_bb->pushIr(new LoadIIR(v,var));
                bb->val = v;
            }
        }else {
            bb->val = tempVal;
        }
    }
}

void IrVisitor::visit(ConstExp *constExp) {
    constExp->addExp->accept(*this);
}

void IrVisitor::visit(UnaryOp *unaryOp) {}