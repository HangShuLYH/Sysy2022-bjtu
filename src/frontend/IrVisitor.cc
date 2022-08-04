//
// Created by hangshu on 22-4-26.
//
#include "IrVisitor.hh"
#include <iostream>
#include <cmath>
#include "errors.hh"
#include "IRManager.hh"
#include "MIRBuilder.hh"

void IrVisitor::visit(CompUnit *compUnit) {
    for (size_t i = 0; i < compUnit->declDefList.size(); ++i) {
        cur_bb = entry;
        compUnit->declDefList[i]->accept(*this);
    }
    bool foundMain = false;
    for (size_t i = 0; i < functions.size(); ++i) {
        functions[i]->clear();
        if (functions[i]->name == "main") {
            foundMain = true;
            if (!functions[i]->return_type->isInt()) {
                throw MainReturnError();
            }
            if (functions[i]->params.size() > 0) {
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
        curDefType = typeInt;
    } else if (constDecl->defType->type == type_specifier::TYPE_FLOAT) {
        curDefType = typeFloat;
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
        if (tempVal.getVal()) {
            throw ConstNotInitError();
        }
        ConstValue *var = new ConstValue(constDef->identifier, curDefType, tempVal, isGlobal(),
                                         cur_func ? cur_func->varCnt++ : 0);
        pushVars(var);
    } else {
        ConstValue *var = new ConstValue(constDef->identifier,
                                         new Type(TypeID::POINTER, curDefType),
                                         isGlobal(), cur_func ? cur_func->varCnt++ : 0);
        std::vector<int> arrayDims;
        int arrayLen(1);
        for (size_t i(0); i < constDef->constExpList.size(); i++) {
            constDef->constExpList[i]->accept(*this);
            arrayDims.push_back(tempVal.getInt());
            arrayLen *= tempVal.getInt();
        }
        var->setArray(true);
        var->setArrayDims(arrayDims);
        if (!var->is_Global()) {
            cur_bb->pushIr(AllocIRManager::getIR(var, arrayLen));
        }
        pushVars(var);
        if (constDef->constInitVal) {
            tempVal.setVal(var);
            tempVal.setType(var->getType());
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
        if (flag) {
            var = dynamic_cast<ConstValue *>(tempVal.getVal());
            var->setArray(true);
            flag = false;
        }
        size_t init_len(0); // 该维度已有长度
        size_t num_cnt(0);

        size_t dim_len(1);
        for (int i(dims); i < var->getArrayDims().size(); i++) {
            dim_len *= var->getArrayDims()[i];
        }

        for (size_t i = 0; i < constInitVal->constInitValList.size(); ++i) {
            Value *t = new VarValue("", var->getType(), false, isGlobal() ? cnt++ : cur_func->varCnt++, true);
            if (!constInitVal->constInitValList[i]->constExp) {
                size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
                for (; left_len > 0; left_len--) {
                    if (var->getType()->isIntPointer()) {
                        var->push(0);
                        if (!var->is_Global()) {
                            cur_bb->pushIr(new GEPIR(t, var, index++));
                            cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                        }
                    } else {
                        var->push((float) 0.0);
                        if (!var->is_Global()) {
                            cur_bb->pushIr(new GEPIR(t, var, index++));
                            cur_bb->pushIr(StoreIRManager::getIR(t, (float) 0.0, new Type(TypeID::FLOAT, typeFloat)));
                        }
                    }
                }
                init_len += ceil((double) num_cnt / (double) dim_len) + 1;
                num_cnt = 0;
            }

            constInitVal->constInitValList[i]->accept(*this);
            if (!tempVal.getVal() && constInitVal->constInitValList[i]->constExp) {
                num_cnt++;
                if (var->getType()->isIntPointer()) {
                    if (tempVal.isInt()) {
                        var->push(tempVal.getInt());
                        if (!var->is_Global()) {
                            cur_bb->pushIr(new GEPIR(t, var, index++));
                            cur_bb->pushIr(StoreIRManager::getIR(t, tempVal.getInt(), new Type(TypeID::INT, typeInt)));
                        }
                    } else {
                        var->push((int) tempVal.getFloat());
                        if (!var->is_Global()) {
                            cur_bb->pushIr(new GEPIR(t, var, index++));
                            cur_bb->pushIr(
                                    StoreIRManager::getIR(t, tempVal.getFloat(), new Type(TypeID::FLOAT, typeFloat)));
                        }
                    }
                } else {
                    if (tempVal.isInt()) {
                        var->push((float) tempVal.getInt());
                        if (!var->is_Global()) {
                            cur_bb->pushIr(new GEPIR(t, var, index++));
                            cur_bb->pushIr(StoreIRManager::getIR(t, tempVal.getInt(), new Type(TypeID::INT, typeInt)));
                        }
                    } else {
                        var->push(tempVal.getFloat());
                        if (!var->is_Global()) {
                            cur_bb->pushIr(new GEPIR(t, var, index++));
                            cur_bb->pushIr(
                                    StoreIRManager::getIR(t, tempVal.getFloat(), new Type(TypeID::FLOAT, typeFloat)));
                        }
                    }
                }
            } else if (tempVal.getVal() && constInitVal->constInitValList[i]->constExp) {
                num_cnt++;
                VarValue *temp = nullptr;
                if (var->getType()->isInt() && tempVal.getVal()->getType()->isFloat()
                    || var->getType()->isFloat() && tempVal.getVal()->getType()->isInt()) {
                    temp = new VarValue("", var->getType(), isGlobal(), cur_func ? cur_func->varCnt++ : 0);
                    if (!temp->is_Global()) {
                        cur_bb->pushIr(CastIRManager::getIR(temp, tempVal));
                    }
                    tempVal.setVal(temp);
                } else temp = dynamic_cast<VarValue *>(tempVal.getVal());
                if (var->getType()->isInt()) {
                    var->push(0);
                    if (!var->is_Global()) {
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, tempVal));
                    }
                    // cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                } else {
                    var->push((float) 0.0);
                    if (!var->is_Global()) {
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, tempVal));
                    }
                    // cur_bb->pushIr(StoreIRManager::getIR(t, (float)0.0, new Type(TypeID::FLOAT, typeFloat)));
                }
            }
        }

        if (!flag && var->getArrayDims()[dims - 1] - init_len) {
            size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
            for (; left_len > 0; left_len--) {
                Value *t = new VarValue("", var->getType(), false, isGlobal() ? cnt++ : cur_func->varCnt++, true);
                if (var->getType()->isInt()) {
                    var->push(0);
                    if (!var->is_Global()) {
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                    }
                } else {
                    var->push((float) 0.0);
                    if (!var->is_Global()) {
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, (float) 0.0, new Type(TypeID::FLOAT, typeFloat)));
                    }
                }
            }

            init_len += ceil((double) num_cnt / (double) dim_len);
            num_cnt = 0;

            for (size_t left_len(dim_len * (var->getArrayDims()[dims - 1] - init_len)); left_len > 0; left_len--) {
                Value *t = new VarValue("", var->getType(), false, isGlobal() ? cnt++ : cur_func->varCnt++, true);
                if (var->getType()->isInt()) {
                    var->push(0);
                    if (!var->is_Global()) {
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                    }
                } else {
                    var->push(0);
                    if (!var->is_Global()) {
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, (float) 0.0, new Type(TypeID::FLOAT, typeFloat)));
                    }
                }
            }
        }

        dims--;

        if (dims == 0) {
            tempVal.setVal(var);
            var = nullptr;
            index = 0;
            flag = true;
        }
    }
}

void IrVisitor::visit(ConstInitValList *constInitValList) {}

void IrVisitor::visit(VarDecl *varDecl) {
    if (varDecl->defType->type == type_specifier::TYPE_INT) {
        curDefType = typeInt;
    } else if (varDecl->defType->type == type_specifier::TYPE_FLOAT) {
        curDefType = typeFloat;
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
        VarValue *var = new VarValue(varDef->identifier,
                                     new Type(TypeID::POINTER, curDefType),
                                     isGlobal(), cur_func ? cur_func->varCnt++ : 0);
        pushVars(var);
        cur_bb->pushIr(AllocIRManager::getIR(var));
        if (varDef->initVal) {
            varDef->initVal->accept(*this);
            if (tempVal.getVal() && curDefType != tempVal.getType()) {
                VarValue *v = new VarValue("", curDefType,
                                           isGlobal(),
                                           cur_func ? cur_func->varCnt++ : 0);
                cur_bb->pushIr(CastIRManager::getIR(v, tempVal));
                tempVal.setVal(v);
            }
            cur_bb->pushIr(StoreIRManager::getIR(var, tempVal));
        }
    } else {
        VarValue *var(nullptr);
        std::vector<int> arrayDims;
        int arrayLen(1);
        for (size_t i(0); i < varDef->constExpList.size(); i++) {
            varDef->constExpList[i]->accept(*this);
            arrayDims.push_back(tempVal.getInt());
            arrayLen *= tempVal.getInt();
        }
        var = new VarValue(varDef->identifier, new Type(TypeID::POINTER, curDefType),
                           isGlobal(), cur_func ? cur_func->varCnt++ : 0);
        if (!var->is_Global()) {
            cur_bb->pushIr(AllocIRManager::getIR(var, arrayLen));
        }
        var->setArray(true);
        var->setArrayDims(arrayDims);
        pushVars(var);
        if (varDef->initVal) {
            tempVal.setVal(var);
            varDef->initVal->accept(*this);
        }
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
        if (flag) {
            var = dynamic_cast<VarValue *>(tempVal.getVal());
            var->setArray(true);
            flag = false;
        }
        size_t init_len(0); // 该维度已有长度
        size_t num_cnt(0);

        size_t dim_len(1);
        for (int i(dims); i < var->getArrayDims().size(); i++) {
            dim_len *= var->getArrayDims()[i];
        }

        for (size_t i = 0; i < initVal->initValList.size(); ++i) {
            Value *t = new VarValue("", var->getType(), false, isGlobal() ? cnt++ : cur_func->varCnt++, true);
            if (!initVal->initValList[i]->exp) {
                size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
                for (; left_len > 0; left_len--) {
                    if (var->getType()->isIntPointer()) {
                        var->push();
                        index++;
//                        cur_bb->pushIr(new GEPIR(t, var, index++));
//                        cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                    } else {
                        var->push();
                        index++;
//                        cur_bb->pushIr(new GEPIR(t, var, index++));
//                        cur_bb->pushIr(StoreIRManager::getIR(t, (float) 0.0, new Type(TypeID::FLOAT, typeFloat)));
                    }
                }
                init_len += ceil((double) num_cnt / (double) dim_len) + 1;
                num_cnt = 0;
            }

            initVal->initValList[i]->accept(*this);
            if (!tempVal.getVal() && initVal->initValList[i]->exp) {
                num_cnt++;
                if (var->getType()->isIntPointer()) {
                    if (tempVal.isInt()) {
                        var->push();
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, tempVal.getInt(), new Type(TypeID::INT, typeInt)));
                    } else {
                        var->push();
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(
                                StoreIRManager::getIR(t, tempVal.getFloat(), new Type(TypeID::FLOAT, typeFloat)));
                    }
                } else {
                    if (tempVal.isInt()) {
                        var->push();
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(StoreIRManager::getIR(t, tempVal.getInt(), new Type(TypeID::INT, typeInt)));
                    } else {
                        var->push();
                        cur_bb->pushIr(new GEPIR(t, var, index++));
                        cur_bb->pushIr(
                                StoreIRManager::getIR(t, tempVal.getFloat(), new Type(TypeID::FLOAT, typeFloat)));
                    }
                }
            } else if (tempVal.getVal() && initVal->initValList[i]->exp) {
                num_cnt++;
                if ((var->getType()->isIntPointer() &&
                     (tempVal.getVal()->getType()->isFloat() || tempVal.getVal()->getType()->isFloatPointer()))
                    || (var->getType()->isFloatPointer() &&
                        (tempVal.getVal()->getType()->isInt() || tempVal.getVal()->getType()->isIntPointer()))) {
                    VarValue *temp = new VarValue("", var->getType(), isGlobal(), cur_func ? cur_func->varCnt++ : 0);
                    cur_bb->pushIr(CastIRManager::getIR(temp, tempVal));
                    tempVal.setVal(temp);
                }
                var->push();
                cur_bb->pushIr(new GEPIR(t, var, index++));
                cur_bb->pushIr(StoreIRManager::getIR(t, tempVal));
            }
        }

        if (!flag && var->getArrayDims()[dims - 1] - init_len) {
            size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
            for (; left_len > 0; left_len--) {
                Value *t = new VarValue("", var->getType(), false, isGlobal() ? cnt++ : cur_func->varCnt++, true);
                if (var->getType()->isIntPointer()) {
                    var->push();
                    index++;
//                    cur_bb->pushIr(new GEPIR(t, var, index++));
//                    cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                } else {
                    var->push();
                    index++;
//                    cur_bb->pushIr(new GEPIR(t, var, index++));
//                    cur_bb->pushIr(StoreIRManager::getIR(t, (float) 0.0, new Type(TypeID::FLOAT, typeFloat)));
                }
            }

            init_len += ceil((double) num_cnt / (double) dim_len);
            num_cnt = 0;

            for (size_t left_len(dim_len * (var->getArrayDims()[dims - 1] - init_len)); left_len > 0; left_len--) {
                Value *t = new VarValue("", var->getType(), false, isGlobal() ? cnt++ : cur_func->varCnt++, true);
                if (var->getType()->isIntPointer()) {
                    var->push();
                    index++;
//                    cur_bb->pushIr(new GEPIR(t, var, index++));
//                    cur_bb->pushIr(StoreIRManager::getIR(t, 0, new Type(TypeID::INT, typeInt)));
                } else {
                    var->push();
                    index++;
//                    cur_bb->pushIr(new GEPIR(t, var, index++));
//                    cur_bb->pushIr(StoreIRManager::getIR(t, (float) 0.0, new Type(TypeID::FLOAT, typeFloat)));
                }
            }
        }

        dims--;

        if (dims == 0) {
            tempVal.setVal(var);
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
        function = new Function(funcDef->identifier, typeInt);
    } else if (funcDef->defType->type == type_specifier::TYPE_FLOAT) {
        function = new Function(funcDef->identifier, typeFloat);
    } else {
        function = new Function(funcDef->identifier, typeVoid);
    }
    cur_func = function;
    pushFunctions(cur_func);
    if (funcDef->funcFParams) {
        cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
        cur_func->pushBB(cur_bb);
        funcDef->funcFParams->accept(*this);
        for (size_t i = 0; i < cur_func->params.size(); ++i) {
            VarValue *v = new VarValue(cur_func->params[i]->getName(),
                                       new Type(TypeID::POINTER, cur_func->params[i]->getType()),
                                       isGlobal(), cur_func ? cur_func->varCnt++ : 0);
            cur_bb->pushVar(v);
            cur_bb->pushIr(AllocIRManager::getIR(v));
            cur_bb->pushIr(StoreIRManager::getIR(v, cur_func->params[i]));
            if (cur_func->params[i]->getType()->isPointer()) {
                v->setArrayDims(cur_func->params[i]->getArrayDims());
                v->setArray(true);
                v->setArrayLen(cur_func->params[i]->getArrayLen());
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
            tempVal.setVal(new VarValue(funcFParam->identifier, typeFloat, isGlobal(), cur_func->varCnt++));
        } else if (funcFParam->defType->type == type_specifier::TYPE_INT) {
            tempVal.setVal(new VarValue(funcFParam->identifier, typeInt, isGlobal(), cur_func->varCnt++));
        }
    } else {
        if (funcFParam->defType->type == type_specifier::TYPE_INT) {
            tempVal.setVal(new VarValue(funcFParam->identifier, new Type(TypeID::POINTER, typeInt), isGlobal(),
                                        cur_func->varCnt++));
            tempVal.getVal()->pushDim(0);
            TempVal t = tempVal;
            for (auto width: funcFParam->expList) {
                width->accept(*this);
                t.getVal()->pushDim(tempVal.getInt());
            }
            tempVal = t;
        } else if (funcFParam->defType->type == type_specifier::TYPE_FLOAT) {
            tempVal.setVal(new VarValue(funcFParam->identifier, new Type(TypeID::POINTER, typeFloat), isGlobal(),
                                        cur_func->varCnt++));
            tempVal.getVal()->pushDim(0);
            TempVal t = tempVal;
            for (auto width: funcFParam->expList) {
                width->accept(*this);
                t.getVal()->pushDim(tempVal.getInt());
            }
            tempVal = t;
        }
    }
    addParam(cur_func, tempVal.getVal());
}

void IrVisitor::visit(ParamArrayExpList *paramArrayExpList) {}

void IrVisitor::visit(Block *block) {
    BasicBlock* temp = cur_bb;
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
    cur_bb = temp;
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
    } else if (stmt->exp) {
        stmt->exp->accept(*this);
    } else if (stmt->block) {
        stmt->block->accept(*this);
    } else if (stmt->selectStmt) {
        stmt->selectStmt->accept(*this);
    } else if (stmt->iterationStmt) {
        stmt->iterationStmt->accept(*this);
    } else if (stmt->breakStmt) {
        stmt->breakStmt->accept(*this);
    } else if (stmt->continueStmt) {
        stmt->continueStmt->accept(*this);
    } else if (stmt->returnStmt) {
        stmt->returnStmt->accept(*this);
    }
}

void IrVisitor::visit(AssignStmt *assignStmt) {
    assignStmt->lVal->accept(*this);
    Value *left = tempVal.getVal();
    if (!tempVal.getVal()) {
        throw LValIsConstError();
    }
    assignStmt->exp->accept(*this);
    if (tempVal.getVal()) {
        if (left->getType()->isIntPointer() && tempVal.isFloat() ||
            left->getType()->isFloatPointer() && tempVal.isInt()) {
            Value *v = new VarValue("", left->getType()->getContained(), isGlobal(),
                                    isGlobal() ? cnt++ : cur_func->varCnt++, true);
            cur_bb->pushIr(CastIRManager::getIR(v, tempVal));
            tempVal.setVal(v);
            tempVal.setType(v->getType());
        }
    }
    cur_bb->pushIr(StoreIRManager::getIR(left, tempVal));
}

void IrVisitor::visit(SelectStmt *selectStmt) {
    auto tempBB = cur_bb;
    cur_bb = new SelectBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    pushBB();
    condBB.push(cur_bb);
    dynamic_cast<SelectBlock *>(cur_bb)->cond.push_back(new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++));
    selectStmt->cond->accept(*this);
    bool temp = isIF;
    isIF = true;
    cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    pushBB();
    isIF = temp;
    if (selectStmt->ifStmt) {
        if (selectStmt->ifStmt->returnStmt ||
            selectStmt->ifStmt->breakStmt ||
            selectStmt->ifStmt->assignStmt ||
            selectStmt->ifStmt->continueStmt ||
            selectStmt->ifStmt->exp) {
        }
        temp = isIF;
        isIF = true;
        selectStmt->ifStmt->accept(*this);
        isIF = temp;
    }
    temp = isIF;
    isIF = false;
    cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    pushBB();
    isIF = temp;
    if (selectStmt->elseStmt) {
        if (selectStmt->elseStmt->returnStmt ||
            selectStmt->elseStmt->breakStmt ||
            selectStmt->elseStmt->assignStmt ||
            selectStmt->elseStmt->continueStmt ||
            selectStmt->elseStmt->exp) {
        }
        temp = isIF;
        isIF = false;
        selectStmt->elseStmt->accept(*this);
        isIF = temp;
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
    dynamic_cast<IterationBlock *>(cur_bb)->cond.push_back(new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++));
    iterationStmt->cond->accept(*this);
    if (iterationStmt->stmt) {
        if (iterationStmt->stmt->returnStmt ||
            iterationStmt->stmt->breakStmt ||
            iterationStmt->stmt->assignStmt ||
            iterationStmt->stmt->continueStmt ||
            iterationStmt->stmt->exp) {
            cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
            pushBB();
        }
        iterationStmt->stmt->accept(*this);
    }
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
        if (cur_func->return_type->isVoid()) {
            throw VoidFuncReturnValueUsedError();
        }
        returnStmt->exp->accept(*this);
        if (!tempVal.getVal()) {
            if (cur_func->return_type->isInt()) {
                if (tempVal.isInt()) {
                    cur_bb->pushIr(new ReturnIR(tempVal.getInt()));
                } else {
                    cur_bb->pushIr(new ReturnIR((int) tempVal.getFloat()));
                }
            } else {
                if (tempVal.isInt()) {
                    cur_bb->pushIr(new ReturnIR((float) tempVal.getInt()));
                } else {
                    cur_bb->pushIr(new ReturnIR(tempVal.getFloat()));
                }
            }
        } else {
            VarValue *t = nullptr;
            if (!cur_func->return_type->isVoid()) {
                t = new VarValue("", curDefType, isGlobal(), cur_func->varCnt++);
            }
            if (cur_func->return_type->isInt() && tempVal.getVal()->getType()->isFloat()) {
                cur_bb->pushIr(new CastFloat2IntIR(t, tempVal.getVal()));
            } else if (cur_func->return_type->isFloat() && tempVal.getVal()->getType()->isInt()) {
                cur_bb->pushIr(new CastInt2FloatIR(t, tempVal.getVal()));
            }
            cur_bb->pushIr(new ReturnIR(tempVal.getVal()));
        }
    } else {
        if (!cur_func->return_type->isVoid()) {
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
    CondBlock *bb = dynamic_cast<CondBlock *>(cur_bb);
    bb->val = tempVal;
}

void IrVisitor::visit(LVal *lVal) {
    tempVal.setVal(findAllVal(lVal->identifier));
    if (!tempVal.getVal()) {
        throw UndefinedVarError(lVal->identifier);
    }
    tempVal.setType(tempVal.getVal()->getType());
    if (cur_func && cur_func->isArgs(tempVal.getVal()->getName())) {
        if (!tempVal.getVal()->getType()->getContained()->isPointer()) return;
        auto v = new VarValue(tempVal.getVal()->getName(),
                              new Type(TypeID::POINTER, tempVal.getVal()->getType()->getContained()->getContained()),
                              isGlobal(), cur_func->varCnt++);
        v->setArray(tempVal.getVal()->is_Array());
        v->setArrayDims(tempVal.getVal()->getArrayDims());
        v->setArrayLen(tempVal.getVal()->getArrayLen());
        cur_bb->pushIr(LoadIRManager::getIR(v, tempVal.getVal()));
        tempVal.setVal(v);
        tempVal.setType(v->getType());
    }
    if (lVal->expList.empty()) {
        if (typeid(ConstValue) == typeid(*tempVal.getVal())) {
            if (tempVal.isInt()) {
                tempVal.setInt(dynamic_cast<ConstValue *>(tempVal.getVal())->getIntVal());
            } else {
                tempVal.setFloat(dynamic_cast<ConstValue *>(tempVal.getVal())->getFloatVal());
            }
            tempVal.setVal(nullptr);
        }
        if (tempVal.getVal() && tempVal.getVal()->getArrayDims().size() != 0) {
            Value *v1 = new VarValue("", tempVal.getType(), isGlobal(),
                                     isGlobal() ? cnt++ : cur_func->varCnt++,
                                     true);
            cur_bb->pushIr(new GEPIR(v1,tempVal.getVal(),0));
            tempVal.setVal(v1);
            tempVal.setType(v1->getType());
            useArgs = true;
        }
        return;
    }

    if (!tempVal.getVal()->getType()->isPointer()) {
        throw InvalidIndexOperatorError();
    }
    bool useVal = false;
    int arrayIndex(0), arrayDimLen(1);
    TempVal val = tempVal;
    Value *index = nullptr;
    for (int i = 1; i <= tempVal.getVal()->getArrayDims().size() - lVal->expList.size(); ++i) {
        arrayDimLen *= val.getVal()->getArrayDims()[tempVal.getVal()->getArrayDims().size() - i];
    }
    for (int i(lVal->expList.size() - 1); i >= 0; i--) {
        lVal->expList[i]->accept(*this);
        if (!tempVal.getVal() && !useVal) {
            arrayIndex += arrayDimLen * tempVal.getInt();
            arrayDimLen *= val.getVal()->getArrayDims()[i];
        } else {
            if (!useVal) {
                index = tempVal.getVal();
                Value *v1 = new VarValue("", typeInt, isGlobal(),
                                         isGlobal() ? cnt++ : cur_func->varCnt++,
                                         true);
                TempVal t1;
                t1.setType(typeInt);
                t1.setVal(v1);

                TempVal t2;
                t2.setType(typeInt);
                t2.setVal(index);

                TempVal t3;
                t3.setType(typeInt);
                t3.setInt(arrayDimLen);
                t3.setVal(nullptr);

                TempVal t4;
                t4.setType(typeInt);
                t4.setInt(arrayIndex);
                t4.setVal(nullptr);

                Value *v2 = new VarValue("", typeInt, isGlobal(),
                                         isGlobal() ? cnt++ : cur_func->varCnt++,
                                         true);
                TempVal t5;
                t5.setType(typeInt);
                t5.setVal(v2);
                cur_bb->pushIr(ArithmeticIRManager::getIR(t1, t2, t3, '*'));
                cur_bb->pushIr(ArithmeticIRManager::getIR(t5, t1, t4, '+'));
                useVal = true;
                index = v2;
            }else {
                if (tempVal.getVal()) {
                    Value *v1 = new VarValue("", typeInt, isGlobal(),
                                             isGlobal() ? cnt++ : cur_func->varCnt++,
                                             true);
                    TempVal t1;
                    t1.setType(v1->getType());
                    t1.setVal(v1);

                    Value *v2 = new VarValue("", typeInt, isGlobal(),
                                             isGlobal() ? cnt++ : cur_func->varCnt++,
                                             true);
                    TempVal t2;
                    t2.setType(v2->getType());
                    t2.setVal(v2);

                    TempVal t3;
                    t3.setType(typeInt);
                    t3.setInt(arrayDimLen);

                    TempVal t4;
                    t4.setType(index->getType());
                    t4.setVal(index);
                    cur_bb->pushIr(ArithmeticIRManager::getIR(t1, tempVal, t3, '*'));
                    cur_bb->pushIr(ArithmeticIRManager::getIR(t2, t4, t1, '+'));
                    index = v2;
                } else {
                    Value *v1 = new VarValue("", typeInt, isGlobal(),
                                             isGlobal() ? cnt++ : cur_func->varCnt++,
                                             true);
                    TempVal t1;
                    t1.setType(v1->getType());
                    t1.setVal(v1);

                    int t = tempVal.getInt() * arrayDimLen;
                    TempVal t2;
                    t2.setType(typeInt);
                    t2.setInt(t);

                    TempVal t3;
                    t3.setType(index->getType());
                    t3.setVal(index);
                    cur_bb->pushIr(ArithmeticIRManager::getIR(t1, t3, t2, '+'));
                    index = v1;
                }
            }
            arrayDimLen *= val.getVal()->getArrayDims()[i];
        }
    }
    tempVal = val;
    if (typeid(*tempVal.getVal()) == typeid(ConstValue)
        && !index) {
        if (tempVal.getType()->isIntPointer()) {
            tempVal.setInt(dynamic_cast<ConstValue *>(tempVal.getVal())->getIntValList()[arrayIndex]);
        } else {
            tempVal.setFloat(dynamic_cast<ConstValue *>(tempVal.getVal())->getFloatValList()[arrayIndex]);
        }
        tempVal.setType(tempVal.getType()->getContained());
        tempVal.setVal(nullptr);
        return;
    }
    if (lVal->expList.size() < tempVal.getVal()->getArrayDims().size()) {
        useArgs = true;
        Value *v1 = new VarValue("", tempVal.getType(), isGlobal(),
                                 isGlobal() ? cnt++ : cur_func->varCnt++,
                                 true);
        if (!index) {
            cur_bb->pushIr(new GEPIR(v1, tempVal.getVal(), arrayIndex));
        } else {
            cur_bb->pushIr(new GEPIR(v1, tempVal.getVal(),index));
        }
        tempVal.setVal(v1);
        tempVal.setType(v1->getType());
        return;
    }
    Value *v = new VarValue("",
                            new Type(TypeID::POINTER, val.getVal()->getType()->getContained()),
                            isGlobal(),
                            isGlobal() ? cnt++ : cur_func->varCnt++, true);
    if (!index) {
        if (typeid(ConstValue) == typeid(*tempVal.getVal())) {
            tempVal.setType(tempVal.getVal()->getType()->getContained());
            if (tempVal.getType()->isInt()) {
                tempVal.setInt(dynamic_cast<ConstValue *>(tempVal.getVal())->getArrayVal(arrayIndex));
            } else {
                tempVal.setFloat(dynamic_cast<ConstValue *>(tempVal.getVal())->getArrayVal(arrayIndex));
            }
            tempVal.setVal(nullptr);
            return;
        } else {
            cur_bb->pushIr(new GEPIR(v, tempVal.getVal(), arrayIndex));
        }
    } else {
        cur_bb->pushIr(new GEPIR(v, tempVal.getVal(), index));
    }
    tempVal.setVal(v);
    tempVal.setType(v->getType());
}

void IrVisitor::visit(PrimaryExp *primaryExp) {
    if (primaryExp->exp) {
        primaryExp->exp->accept(*this);
    } else if (primaryExp->lVal) {
        primaryExp->lVal->accept(*this);
        if (tempVal.getType()->isInt() || tempVal.getType()->isFloat() || useArgs) {
            if (useArgs) useArgs = false;
            return;
        }
        VarValue *v = new VarValue("", tempVal.getVal()->getType()->getContained(),
                                   isGlobal(),
                                   isGlobal() ? cnt++ : cur_func->varCnt++, true);
        cur_bb->pushIr(LoadIRManager::getIR(v, tempVal.getVal()));
        tempVal.setVal(v);
        tempVal.setType(v->getType());
    } else if (primaryExp->number) {
        primaryExp->number->accept(*this);
    }
}

void IrVisitor::visit(Number *number) {
    if (number->type == type_specifier::TYPE_FLOAT) {
        tempVal.setFloat(number->floatNum);
        tempVal.setType(typeFloat);
    } else if (number->type == type_specifier::TYPE_INT) {
        tempVal.setInt(number->intNum);
        tempVal.setType(typeInt);
    }
    tempVal.setVal(nullptr);
}

void IrVisitor::visit(UnaryExp *unaryExp) {
    if (unaryExp->primaryExp) {
        unaryExp->primaryExp->accept(*this);
    } else if (unaryExp->unaryExp) {
        unaryExp->unaryExp->accept(*this);
        if (unaryExp->unaryOp->op == unaryop::OP_POS) {
            return;
        }
        //cal const
        if (!tempVal.getVal()) {
            if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                tempVal.setInt(-tempVal.getInt());
                tempVal.setFloat(-tempVal.getFloat());
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                tempVal.setInt(!tempVal.getInt());
                tempVal.setFloat(!tempVal.getFloat());
            }
        } else {
            TempVal t = tempVal;
            VarValue *v = nullptr;
            if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                v = new VarValue("", tempVal.getType(), isGlobal(),
                                 isGlobal() ? cnt++ : cur_func->varCnt++, true);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                v = new VarValue("", typeInt, isGlobal(),
                                 isGlobal() ? cnt++ : cur_func->varCnt++, true);
            }
            tempVal.setVal(v);
            tempVal.setType(v->getType());
            if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                cur_bb->pushIr(UnaryIRManager::getIR(tempVal, t, '-'));
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                cur_bb->pushIr(UnaryIRManager::getIR(tempVal, t, '!'));
            }
        }
    } else if (unaryExp->identifier != "") {
        args_stack.push({});
        call_func = findFunc(unaryExp->identifier);
        call_func_stack.push(call_func);
        Function *temp = call_func;
        if (unaryExp->funcRParams) {
            unaryExp->funcRParams->accept(*this);
        }
        args = args_stack.top();
        args_stack.pop();
        call_func = call_func_stack.top();
        call_func_stack.pop();
        if (call_func->return_type->isVoid()) {
            cur_bb->pushIr(new CallIR(call_func, args));
        } else {
            Value *v = new VarValue("", call_func->return_type,
                                    isGlobal(), cur_func->varCnt++);
            tempVal.setVal(v);
            tempVal.setType(v->getType());
            call_func = temp;
            cur_bb->pushIr(new CallIR(call_func, args, v));
        }
    } else {
        tempVal.setType(typeString);
        tempVal.setString(unaryExp->stringConst);
        globalVars.push_back(new VarValue(unaryExp->stringConst, typeString, false, 0));
    }
}

void IrVisitor::visit(FuncRParams *funcRParams) {
    if (funcRParams->expList.size() != call_func->params.size() && !call_func->variant_params) {
        throw ArgsNumberNotMatchError(call_func->name);
    }
    for (size_t i = 0; i < funcRParams->expList.size(); ++i) {
        funcRParams->expList[i]->accept(*this);
        Function* f = call_func_stack.top();
        if (f->params[i]->getType()->isInt() && tempVal.getType()->isFloat() ||
            f->params[i]->getType()->isFloat() && tempVal.getType()->isInt()) {
            if (tempVal.getVal()) {
                Value *v = new VarValue("", f->params[i]->getType(), isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(v, tempVal));
                tempVal.setVal(v);
                tempVal.setType(v->getType());
            } else {
                if (tempVal.getType()->isInt()) {
                    tempVal.setType(typeFloat);
                    tempVal.setFloat(tempVal.getInt());
                } else {
                    tempVal.setType(typeInt);
                    tempVal.setInt(tempVal.getFloat());
                }
            }
        }
        std::vector<TempVal> aa = args_stack.top();
        aa.push_back(tempVal);
        args_stack.pop();
        args_stack.push(aa);
    }
}

void IrVisitor::visit(MulExp *mulExp) {
    if (!mulExp->mulExp) {
        mulExp->unaryExp->accept(*this);
    } else {
        mulExp->mulExp->accept(*this);
        auto left = tempVal;
        mulExp->unaryExp->accept(*this);
        auto right = tempVal;
        //cal const
        if (!left.getVal() && !right.getVal()) {
            if (mulExp->op == mulop::OP_MUL) {
                tempVal = TempVal::calConstArithmetic(left, right, '*');
            } else if (mulExp->op == mulop::OP_DIV) {
                tempVal = TempVal::calConstArithmetic(left, right, '/');
            } else {
                tempVal = TempVal::calConstArithmetic(left, right, '%');
            }
            return;
        }
        //cast
        if (left.getType() != right.getType()) {
            if (left.isInt() && left.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(t, left));
                left.setVal(t);
                left.setType(typeFloat);
            }
            if (right.isInt() && right.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(t, right));
                right.setVal(t);
                right.setType(typeFloat);
            }
        }
        //cal
        Value *res = new VarValue("", left.getType(), isGlobal(),
                                  isGlobal() ? cnt++ : cur_func->varCnt++, true);
        tempVal.setType(left.getType());
        tempVal.setVal(res);
        if (mulExp->op == mulop::OP_MUL) {
            cur_bb->pushIr(ArithmeticIRManager::getIR(tempVal, left, right, '*'));
        } else if (mulExp->op == mulop::OP_DIV) {
            cur_bb->pushIr(ArithmeticIRManager::getIR(tempVal, left, right, '/'));
        } else {
            cur_bb->pushIr(ArithmeticIRManager::getIR(tempVal, left, right, '%'));
        }
    }
}

void IrVisitor::visit(AddExp *addExp) {
    if (!addExp->addExp) {
        addExp->mulExp->accept(*this);
    } else {
        addExp->addExp->accept(*this);
        auto left = tempVal;
        addExp->mulExp->accept(*this);
        auto right = tempVal;
        if (left.isInt() && right.isInt()) {
            if (left.getInt() == 1000000000) {
                std::cout << "\n";
            }
        }
        //cal const
        if (!left.getVal() && !right.getVal()) {
            if (addExp->op == addop::OP_ADD) {
                tempVal = TempVal::calConstArithmetic(left, right, '+');
            } else {
                tempVal = TempVal::calConstArithmetic(left, right, '-');
            }
            return;
        }
        //cast
        if (left.getType() != right.getType()) {
            if (left.isInt() && left.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(t, left));
                left.setVal(t);
                left.setType(typeFloat);
            }
            if (right.isInt() && right.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(t, right));
                right.setVal(t);
                right.setType(typeFloat);
            }
        }
        //cal
        Value *res = new VarValue("", left.getType(), isGlobal(),
                                  isGlobal() ? cnt++ : cur_func->varCnt++, true);
        tempVal.setType(left.getType());
        tempVal.setVal(res);
        if (addExp->op == addop::OP_ADD) {
            cur_bb->pushIr(ArithmeticIRManager::getIR(tempVal, left, right, '+'));
        } else {
            cur_bb->pushIr(ArithmeticIRManager::getIR(tempVal, left, right, '-'));
        }
    }
}

void IrVisitor::visit(RelExp *relExp) {
    if (!relExp->relExp) {
        relExp->addExp->accept(*this);
    } else {
        relExp->relExp->accept(*this);
        auto left = tempVal;
        relExp->addExp->accept(*this);
        auto right = tempVal;
        //cal const
        if (!left.getVal() && !right.getVal()) {
            tempVal = TempVal::calConstLogical(left, right, relExp->op, typeInt);
            return;
        }
        //cast
        if (left.getType() != right.getType()) {
            if (left.isInt()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);

                cur_bb->pushIr(CastIRManager::getIR(t, left));
                left.setVal(t);
                left.setType(typeFloat);
            }
            if (right.isInt() && right.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);

                cur_bb->pushIr(CastIRManager::getIR(t, right));
                right.setVal(t);
                right.setType(typeFloat);
            }
        }
        //cal
        Value *res = new VarValue("", typeInt, isGlobal(),
                                  isGlobal() ? cnt++ : cur_func->varCnt++, true);
        tempVal.setType(typeInt);
        tempVal.setVal(res);
        cur_bb->pushIr(LogicalIRManager::getIR(tempVal, left, right, relExp->op));
    }
}

void IrVisitor::visit(EqExp *eqExp) {
    if (!eqExp->eqExp) {
        eqExp->relExp->accept(*this);
    } else {
        eqExp->eqExp->accept(*this);
        auto left = tempVal;
        eqExp->relExp->accept(*this);
        auto right = tempVal;
        //cal const
        if (!left.getVal() && !right.getVal()) {
            tempVal = TempVal::calConstLogical(left, right, eqExp->op, typeInt);
            return;
        }
        //cast
        if (left.getType() != right.getType()) {
            if (left.isInt() && left.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(t, left));
                left.setVal(t);
                left.setType(typeFloat);
            }
            if (right.isInt() && right.getVal()) {
                Value *t = new VarValue("", typeFloat, isGlobal(),
                                        isGlobal() ? cnt++ : cur_func->varCnt++, true);
                cur_bb->pushIr(CastIRManager::getIR(t, right));
                right.setVal(t);
                right.setType(typeFloat);
            }
        }
        //cal
        Value *res = new VarValue("", typeInt, isGlobal(),
                                  isGlobal() ? cnt++ : cur_func->varCnt++, true);
        tempVal.setType(typeInt);
        tempVal.setVal(res);
        cur_bb->pushIr(LogicalIRManager::getIR(tempVal, left, right, eqExp->op));
    }
}

void IrVisitor::visit(LAndExp *lAndEXp) {
    cur_bb = new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    if (typeid(*condBB.top()) == typeid(SelectBlock)) {
        dynamic_cast<SelectBlock *>(condBB.top())->cond.push_back(cur_bb);
    } else {
        dynamic_cast<IterationBlock *>(condBB.top())->cond.push_back(cur_bb);
    }
    if (!lAndEXp->lAndExp) {
        lAndEXp->eqExp->accept(*this);
    } else {
        lAndEXp->lAndExp->accept(*this);
        CondBlock *bb = dynamic_cast<CondBlock *>(cur_bb);
        bb->isAnd = true;
        bb->val = tempVal;
        cur_bb = new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
        if (typeid(*condBB.top()) == typeid(SelectBlock)) {
            dynamic_cast<SelectBlock *>(condBB.top())->cond.push_back(cur_bb);
        } else {
            dynamic_cast<IterationBlock *>(condBB.top())->cond.push_back(cur_bb);
        }
        lAndEXp->eqExp->accept(*this);
        bb = dynamic_cast<CondBlock *>(cur_bb);
        bb->val = tempVal;
    }
}

void IrVisitor::visit(LOrExp *lOrExp) {
    cur_bb = new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
    if (typeid(*condBB.top()) == typeid(SelectBlock)) {
        dynamic_cast<SelectBlock *>(condBB.top())->cond.push_back(cur_bb);
    } else {
        dynamic_cast<IterationBlock *>(condBB.top())->cond.push_back(cur_bb);
    }
    if (!lOrExp->lOrExp) {
        lOrExp->lAndExp->accept(*this);
    } else {
        lOrExp->lOrExp->accept(*this);
        CondBlock *bb = dynamic_cast<CondBlock *>(cur_bb);
        bb->isAnd = false;
        bb->val = tempVal;
        cur_bb = new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
        if (typeid(*condBB.top()) == typeid(SelectBlock)) {
            dynamic_cast<SelectBlock *>(condBB.top())->cond.push_back(cur_bb);
        } else {
            dynamic_cast<IterationBlock *>(condBB.top())->cond.push_back(cur_bb);
        }
        lOrExp->lAndExp->accept(*this);
        bb = dynamic_cast<CondBlock *>(cur_bb);
        bb->val = tempVal;
    }
}

void IrVisitor::visit(ConstExp *constExp) {
    constExp->addExp->accept(*this);
}

void IrVisitor::visit(UnaryOp *unaryOp) {}