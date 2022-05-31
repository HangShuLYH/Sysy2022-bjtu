//
// Created by hangshu on 22-4-26.
//
#include "IrVisitor.hh"
#include <iostream>
#include <cmath>
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
    getRelated();
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
        if (!useConst) {
            throw ConstNotInitError();
        }
        ConstValue *var = nullptr;
        if (curDefType->isInt()) {
            if (curValType->isInt()) {
                var = new ConstValue(0, constDef->identifier, typeInt);
                var->setInt(tempInt);
            } else if (curValType->isFloat()) {
                var = new ConstValue(0, constDef->identifier, typeInt);
                var->setInt(tempFloat);
            }
        } else if (curDefType->isFloat()) {
            if (curValType->isInt()) {
                var = new ConstValue(0, constDef->identifier, typeFloat);
                var->setFloat(tempInt);
            } else if (curValType->isFloat()) {
                var = new ConstValue(0, constDef->identifier, typeFloat);
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

        if (curDefType->isInt()) {
            if (!isGlobal()) {
                var = new ConstValue(cur_func->varCnt++, constDef->identifier, new Type(TypeID::POINTER, typeInt));
                AllocIIR *ir = new AllocIIR(var, arrayLen);
                cur_bb->pushIr(ir);
            } else {
                var = new ConstValue(0, constDef->identifier, new Type(TypeID::POINTER, typeInt));
            }

        } else {
            if (!isGlobal()) {
                var = new ConstValue(cur_func->varCnt++, constDef->identifier, new Type(TypeID::POINTER, typeFloat));
                AllocFIR *ir = new AllocFIR(var, arrayLen);
                cur_bb->pushIr(ir);
            } else {
                var = new ConstValue(0, constDef->identifier, new Type(TypeID::POINTER, typeFloat));
            }

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
        if (flag) {
            var = dynamic_cast<ConstValue *>(tempVal);
            var->isArray = true;
            flag = false;
        }
        size_t init_len(0); // 该维度已有长度
        size_t num_cnt(0);

        size_t dim_len(1);
        for (int i(dims); i < var->arrayDims.size(); i++) {
            dim_len *= var->arrayDims[i];
        }

        for (size_t i = 0; i < constInitVal->constInitValList.size(); ++i) {
            if (!constInitVal->constInitValList[i]->constInitValList.empty()) {
                size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
                for (; left_len > 0; left_len--) {
                    if (var->type->getContained()->isInt()) {
                        var->push(0);
                        StoreIIR *ir = new StoreIIR(var, 0, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push((float) 0.0);
                        StoreFIR *ir = new StoreFIR(var, 0.0, index++);
                        cur_bb->pushIr(ir);
                    }
                }
                init_len += ceil((double) num_cnt / (double) dim_len) + 1;
                num_cnt = 0;
            }

            constInitVal->constInitValList[i]->accept(*this);
            if (useConst && constInitVal->constInitValList[i]->constInitValList.empty()) {
                num_cnt++;
                if (var->type->isInt()) {
                    if (curValType->isInt()) {
                        var->push(tempInt);
                        StoreIIR *ir = new StoreIIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push((int) tempFloat);
                        StoreIIR *ir = new StoreIIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                } else {
                    if (curValType->isInt()) {
                        var->push((float) tempInt);
                        StoreFIR *ir = new StoreFIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push(tempFloat);
                        StoreFIR *ir = new StoreFIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                }
            } else if (!useConst && constInitVal->constInitValList[i]->constInitValList.empty()) {
                num_cnt++;
                VarValue *t = nullptr;
                if (var->type->isInt() && tempVal->type->isFloat()) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", typeInt);
                    } else {
                        t = new VarValue(0, "", typeInt);
                    }
                    CastFloat2IntIR *ir = nullptr;
                    if (tempVal->isArray) {
                        ir = new CastFloat2IntIR(t, tempVal, tempInt);
                    } else ir = new CastFloat2IntIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                } else if (var->type->isFloat() && tempVal->type->isInt()) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", typeFloat);
                    } else {
                        t = new VarValue(0, "", typeFloat);
                    }
                    CastInt2FloatIR *ir = nullptr;
                    if (tempVal->isArray) {
                        ir = new CastInt2FloatIR(t, tempVal, tempInt);
                    } else ir = new CastInt2FloatIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                } else t = dynamic_cast<VarValue *>(tempVal);
                if (var->type->isInt()) {
                    var->push(0);
                    StoreIIR *ir = nullptr;
                    if (tempVal->isArray)
                        ir = new StoreIIR(var, tempVal, index++, tempInt);
                    else ir = new StoreIIR(var, tempVal, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push((float) 0.0);
                    StoreFIR *ir = nullptr;
                    if (tempVal->isArray)
                        ir = new StoreFIR(var, tempVal, index++, tempInt);
                    else ir = new StoreFIR(var, tempVal, index++);
                    cur_bb->pushIr(ir);
                }
            }
        }

        if (!flag && var->arrayDims[dims - 1] - init_len) {
            size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
            for (; left_len > 0; left_len--) {
                if (var->type->isInt()) {
                    var->push(0);
                    StoreIIR *ir = new StoreIIR(var, 0, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push((float) 0.0);
                    StoreFIR *ir = new StoreFIR(var, 0.0, index++);
                    cur_bb->pushIr(ir);
                }
            }

            init_len += ceil((double) num_cnt / (double) dim_len);
            num_cnt = 0;

            for (size_t left_len(dim_len * (var->arrayDims[dims - 1] - init_len)); left_len > 0; left_len--) {
                if (var->type->isInt()) {
                    var->push(0);
                    StoreIIR *ir = new StoreIIR(var, 0, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push(0);
                    StoreFIR *ir = new StoreFIR(var, 0.0, index++);
                    cur_bb->pushIr(ir);
                }
            }
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
        VarValue *var = nullptr;
        if (curDefType->isInt()) {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, new Type(TypeID::POINTER, typeInt));
                AllocIIR *ir = new AllocIIR(var);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, new Type(TypeID::POINTER, typeInt));
            }
        } else {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, new Type(TypeID::POINTER, typeFloat));
                AllocFIR *ir = new AllocFIR(var);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, new Type(TypeID::POINTER, typeFloat));
            }
        }
        pushVars(var);
        if (varDef->initVal) {
            varDef->initVal->accept(*this);
            if (useConst) {
                if (var->type->isPointer() && var->type->getContained()->isInt()) {
                    if (curValType->isInt()) {
                        StoreIIR *ir = new StoreIIR(var, tempInt);
                        cur_bb->pushIr(ir);
                    } else {
                        StoreIIR *ir = new StoreIIR(var, tempFloat);
                        cur_bb->pushIr(ir);
                    }
                } else {
                    if (curValType->isInt()) {
                        StoreFIR *ir = new StoreFIR(var, tempInt);
                        cur_bb->pushIr(ir);
                    } else {
                        StoreFIR *ir = new StoreFIR(var, tempFloat);
                        cur_bb->pushIr(ir);
                    }
                }
            } else {
                if (var->type->isIntPointer() && (tempVal->type->isFloat() || tempVal->type->isFloatPointer())) {
                    VarValue *t = nullptr;
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", typeInt);
                    } else {
                        t = new VarValue(0, "", typeInt);
                    }
                    CastFloat2IntIR *ir = nullptr;
                    if (tempVal->isArray) {
                        ir = new CastFloat2IntIR(t, tempVal, tempInt);
                    } else ir = new CastFloat2IntIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                } else if (var->type->isFloatPointer() && (tempVal->type->isInt() || tempVal->type->isIntPointer())) {
                    VarValue *t = nullptr;
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", typeFloat);
                    } else {
                        t = new VarValue(0, "", typeFloat);
                    }
                    CastInt2FloatIR *ir = nullptr;
                    if (tempVal->isArray) {
                        ir = new CastInt2FloatIR(t, tempVal, tempInt);
                    } else ir = new CastInt2FloatIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                }
                if (var->type->isIntPointer()) {
                    StoreIIR *ir = nullptr;
                    if (tempVal->isArray)
                        ir = new StoreIIR(var, tempVal, -1, tempInt);
                    else ir = new StoreIIR(var, tempVal);
                    cur_bb->pushIr(ir);
                } else {
                    StoreFIR *ir = nullptr;
                    if (tempVal->isArray)
                        ir = new StoreFIR(var, tempVal, -1, tempInt);
                    ir = new StoreFIR(var, tempVal);
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

        if (curDefType->isInt()) {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, new Type(TypeID::POINTER, typeInt));
                AllocIIR *ir = new AllocIIR(var, arrayLen);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, new Type(TypeID::POINTER, typeInt));
            }

        } else {
            if (!isGlobal()) {
                var = new VarValue(cur_func->varCnt++, varDef->identifier, new Type(TypeID::POINTER, typeFloat));
                AllocFIR *ir = new AllocFIR(var, arrayLen);
                cur_bb->pushIr(ir);
            } else {
                var = new VarValue(0, varDef->identifier, new Type(TypeID::POINTER, typeFloat));
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
            var = dynamic_cast<VarValue *>(tempVal);
            var->isArray = true;
            flag = false;
        }
        size_t init_len(0); // 该维度已有长度
        size_t num_cnt(0);

        size_t dim_len(1);
        for (int i(dims); i < var->arrayDims.size(); i++) {
            dim_len *= var->arrayDims[i];
        }

        for (size_t i = 0; i < initVal->initValList.size(); ++i) {
            if (!initVal->initValList[i]->initValList.empty()) {
                size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
                for (; left_len > 0; left_len--) {
                    if (var->type->isIntPointer()) {
                        var->push();
                        StoreIIR *ir = new StoreIIR(var, 0, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push();
                        StoreFIR *ir = new StoreFIR(var, 0.0, index++);
                        cur_bb->pushIr(ir);
                    }
                }
                init_len += ceil((double) num_cnt / (double) dim_len) + 1;
                num_cnt = 0;
            }
            initVal->initValList[i]->accept(*this);
            if (useConst && initVal->initValList[i]->initValList.empty()) {
                num_cnt++;
                if (var->type->isIntPointer()) {
                    if (curValType->isInt()) {
                        var->push();
                        StoreIIR *ir = new StoreIIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push();
                        StoreIIR *ir = new StoreIIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                } else {
                    if (curValType->isInt()) {
                        var->push();
                        StoreFIR *ir = new StoreFIR(var, tempInt, index++);
                        cur_bb->pushIr(ir);
                    } else {
                        var->push();
                        StoreFIR *ir = new StoreFIR(var, tempFloat, index++);
                        cur_bb->pushIr(ir);
                    }
                }
            } else if (!useConst && initVal->initValList[i]->initValList.empty()) {
                num_cnt++;
                VarValue *t = nullptr;
                if (var->type->isIntPointer() && (tempVal->type->isFloat() || tempVal->type->isFloatPointer())) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", typeInt);
                    } else {
                        t = new VarValue(0, "", typeInt);
                    }
                    CastFloat2IntIR *ir = nullptr;
                    if (tempVal->isArray) {
                        ir = new CastFloat2IntIR(t, tempVal, tempInt);
                    } else ir = new CastFloat2IntIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                } else if (var->type->isFloatPointer() && (tempVal->type->isInt() || tempVal->type->isIntPointer())) {
                    if (!isGlobal()) {
                        t = new VarValue(cur_func->varCnt++, "", typeFloat);
                    } else {
                        t = new VarValue(0, "", typeFloat);
                    }
                    CastInt2FloatIR *ir = nullptr;
                    if (tempVal->isArray) {
                        ir = new CastInt2FloatIR(t, tempVal, tempInt);
                    } else ir = new CastInt2FloatIR(t, tempVal);
                    cur_bb->pushIr(ir);
                    tempVal = t;
                }
                if (var->type->isIntPointer()) {
                    var->push();
                    StoreIIR *ir = nullptr;
                    if (tempVal->isArray)
                        ir = new StoreIIR(var, tempVal, index++, tempInt);
                    else ir = new StoreIIR(var, tempVal, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push();
                    StoreFIR *ir = nullptr;
                    if (tempVal->isArray)
                        ir = new StoreFIR(var, tempVal, index++, tempInt);
                    else ir = new StoreFIR(var, tempVal, index++);
                    cur_bb->pushIr(ir);
                }
            }
        }

        if (!flag && var->arrayDims[dims - 1] - init_len) {
            size_t left_len(num_cnt % dim_len == 0 ? 0 : dim_len - num_cnt % dim_len);
            for (; left_len > 0; left_len--) {
                if (var->type->isIntPointer()) {
                    var->push();
                    StoreIIR *ir = new StoreIIR(var, 0, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push();
                    StoreFIR *ir = new StoreFIR(var, 0.0, index++);
                    cur_bb->pushIr(ir);
                }
            }

            init_len += ceil((double) num_cnt / (double) dim_len);
            num_cnt = 0;

            for (size_t left_len(dim_len * (var->arrayDims[dims - 1] - init_len)); left_len > 0; left_len--) {
                if (var->type->isIntPointer()) {
                    var->push();
                    StoreIIR *ir = new StoreIIR(var, 0, index++);
                    cur_bb->pushIr(ir);
                } else {
                    var->push();
                    StoreFIR *ir = new StoreFIR(var, 0.0, index++);
                    cur_bb->pushIr(ir);
                }
            }
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
        function = new Function(funcDef->identifier, typeInt);
    } else if (funcDef->defType->type == type_specifier::TYPE_FLOAT) {
        function = new Function(funcDef->identifier, typeFloat);
    } else {
        function = new Function(funcDef->identifier, typeVoid);
    }
    cur_func = function;
    pushFunctions(cur_func);
    if (funcDef->funcFParams) {
        funcDef->funcFParams->accept(*this);
        cur_bb = new NormalBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
        cur_func->pushBB(cur_bb);
        for (size_t i = 0; i < cur_func->params.size(); ++i) {
            if (cur_func->params[i]->type->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, cur_func->params[i]->name,
                                           new Type(TypeID::POINTER, typeInt));
                cur_bb->pushVar(v);
                AllocIIR *ir1 = new AllocIIR(v);
                cur_bb->pushIr(ir1);
                StoreIIR *ir2 = new StoreIIR(v, cur_func->params[i]);
                cur_bb->pushIr(ir2);
            } else if (cur_func->params[i]->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, cur_func->params[i]->name,
                                           new Type(TypeID::POINTER, typeFloat));
                cur_bb->pushVar(v);
                AllocFIR *ir1 = new AllocFIR(v);
                cur_bb->pushIr(ir1);
                StoreFIR *ir2 = new StoreFIR(v, cur_func->params[i]);
                cur_bb->pushIr(ir2);
            } else if (cur_func->params[i]->type->isPointer()) {
                VarValue *v = new VarValue(cur_func->varCnt++, cur_func->params[i]->name,
                                           new Type(TypeID::POINTER, cur_func->params[i]->type));
                v->arrayDims = cur_func->params[i]->arrayDims;
                v->isArray = true;
                v->arrayLen = cur_func->params[i]->arrayLen;
                cur_bb->pushVar(v);
                if (cur_func->params[i]->type->isIntPointer()) {
                    cur_bb->pushIr(new AllocIIR(v));
                    cur_bb->pushIr(new StoreIIR(v, cur_func->params[i]));
                } else {
                    cur_bb->pushIr(new AllocFIR(v));
                    cur_bb->pushIr(new StoreFIR(v, cur_func->params[i]));
                }
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
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, typeFloat);
        } else if (funcFParam->defType->type == type_specifier::TYPE_INT) {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, typeInt);
        }
        addParam(cur_func, tempVal);
    } else {
        if (funcFParam->defType->type == type_specifier::TYPE_INT) {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, new Type(TypeID::POINTER, typeInt));
            tempVal->arrayDims.push_back(0);
            for (auto width: funcFParam->expList) {
                width->accept(*this);
                tempVal->arrayDims.push_back(tempInt);
            }
        } else if (funcFParam->defType->type == type_specifier::TYPE_FLOAT) {
            tempVal = new VarValue(cur_func->varCnt++, funcFParam->identifier, new Type(TypeID::POINTER, typeFloat));
            tempVal->arrayDims.push_back(0);
            for (auto width: funcFParam->expList) {
                width->accept(*this);
                tempVal->arrayDims.push_back(tempInt);
            }
        }
        addParam(cur_func, tempVal);
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
    Value *left = tempVal;
    if (tempInt != 0 || tempIndex) {
        if (!isGlobal()) {
            left = new VarValue(cur_func->varCnt++, "",
                                new Type(TypeID::POINTER, tempVal->type->getContained()));
        } else {
            left = new VarValue(cnt++, "",
                                new Type(TypeID::POINTER, tempVal->type->getContained()));
        }
        if (tempIndex){
            cur_bb->pushIr(new GEPIR(left,tempVal,tempIndex));
        }else {
            cur_bb->pushIr(new GEPIR(left, tempVal, tempInt));
        }
        tempIndex = nullptr;
    }
    if (useConst) {
        throw LValIsConstError();
    }
    int index = tempInt;
    assignStmt->exp->accept(*this);
    if (useConst) {
        if (left->type->isIntPointer()) {
            if (curValType->isInt()) {
                StoreIIR *ir;
                if (!left->isArray) {
                    ir = new StoreIIR(left, tempInt);
                } else {
                    ir = new StoreIIR(left, tempInt, index);
                }
                cur_bb->pushIr(ir);
            } else {
                StoreIIR *ir;
                if (!left->isArray) {
                    ir = new StoreIIR(left, tempFloat);
                } else {
                    ir = new StoreIIR(left, tempFloat, index);
                }
                cur_bb->pushIr(ir);
            }
        } else {
            if (curValType->isInt()) {
                StoreFIR *ir;
                if (!left->isArray) {
                    ir = new StoreFIR(left, tempInt);
                } else {
                    ir = new StoreFIR(left, tempInt, index);
                }
                cur_bb->pushIr(ir);
            } else {
                StoreFIR *ir;
                if (!left->isArray) {
                    ir = new StoreFIR(left, tempFloat);
                } else {
                    ir = new StoreFIR(left, tempFloat, index);
                }
                cur_bb->pushIr(ir);
            }
        }
    } else {
        //CAST
        if (left->type->isIntPointer() && tempVal->type->isFloat()) {
            VarValue *t = nullptr;
            if (!isGlobal()) {
                t = new VarValue(cur_func->varCnt++, "", typeInt);
            } else {
                t = new VarValue(cnt++, "", typeInt);
            }
            CastFloat2IntIR *ir = new CastFloat2IntIR(t, tempVal);
            cur_bb->pushIr(ir);
            tempVal = t;
        } else if (left->type->isFloatPointer() && tempVal->type->isInt()) {
            VarValue *t = nullptr;
            if (!isGlobal()) {
                t = new VarValue(cur_func->varCnt++, "", typeFloat);
            } else {
                t = new VarValue(cnt++, "", typeFloat);
            }
            CastInt2FloatIR *ir = new CastInt2FloatIR(t, tempVal);
            cur_bb->pushIr(ir);
            tempVal = t;
        }
        //STORE
        if (left->type->isIntPointer()) {
            cur_bb->pushIr(new StoreIIR(left, tempVal));
        } else {
            cur_bb->pushIr(new StoreFIR(left, tempVal));
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
    dynamic_cast<IterationBlock *>(cur_bb)->cond.push_back(new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++));
    iterationStmt->cond->accept(*this);
    if (iterationStmt->stmt &&
    iterationStmt->stmt->returnStmt ||
    iterationStmt->stmt->breakStmt ||
    iterationStmt->stmt->assignStmt ||
    iterationStmt->stmt->continueStmt||
    iterationStmt->stmt->assignStmt){
        cur_bb = new NormalBlock(cur_bb,cur_func->name,cur_func->bbCnt++);
        pushBB();
    }
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
        if (cur_func->return_type->isVoid()) {
            throw VoidFuncReturnValueUsedError();
        }
        returnStmt->exp->accept(*this);
        if (useConst) {
            if (curDefType->isInt()) {
                if (curValType->isInt()) {
                    cur_bb->pushIr(new ReturnIR(tempInt));
                } else {
                    cur_bb->pushIr(new ReturnIR((int) tempFloat));
                }
            } else {
                if (curValType->isInt()) {
                    cur_bb->pushIr(new ReturnIR((float) tempInt));
                } else {
                    cur_bb->pushIr(new ReturnIR(tempFloat));
                }
            }
        } else {
            if (curDefType->isInt() && tempVal->type->isFloat()) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", typeInt);;
                cur_bb->pushIr(new CastFloat2IntIR(t, tempVal));
                tempVal = t;
            } else if (curDefType->isFloat() && tempVal->type->isInt()) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", typeFloat);;
                cur_bb->pushIr(new CastInt2FloatIR(t, tempVal));
                tempVal = t;
            }
            cur_bb->pushIr(new ReturnIR(tempVal));
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
    if (useConst) {
        ConstValue *val = nullptr;
        if ((curValType->isInt() && tempInt != 0) ||
            (curValType->isFloat() && tempFloat != 0)) {
            val = new ConstValue(cur_func->varCnt++, "", typeInt);
            val->setInt(1);
            bb->val = val;
        } else {
            val = new ConstValue(cur_func->varCnt++, "", typeInt);
            val->setInt(0);
            bb->val = val;
        }
    }
}

void IrVisitor::visit(LVal *lVal) {
    tempVal = findAllVal(lVal->identifier);
    useConst = false;
    tempInt = 0;
    if (!tempVal) {
        throw UndefinedVarError(lVal->identifier);
    }
    if (cur_func != nullptr && cur_func->isArgs(tempVal->name)) {
        if (!tempVal->type->getContained()->isPointer()) return;
        auto v = new VarValue(cur_func->varCnt++, tempVal->name,
                              new Type(TypeID::POINTER, tempVal->type->getContained()->getContained()));
        v->isArray = tempVal->isArray;
        v->arrayDims = tempVal->arrayDims;
        v->arrayLen = tempVal->arrayLen;
        if (v->type->isInt()) {
            cur_bb->pushIr(new LoadIIR(v, tempVal));
        } else if (v->type->isFloat()) {
            cur_bb->pushIr(new LoadFIR(v, tempVal));
        } else if (v->type->getContained()->isInt()) {
            cur_bb->pushIr(new LoadIIR(v, tempVal));
        } else {
            cur_bb->pushIr(new LoadFIR(v, tempVal));
        }
        tempVal = v;
    }

    if (lVal->expList.empty()) {
        if (typeid(*tempVal) == typeid(ConstValue)) {
            useConst = true;
            if (tempVal->type->isInt()) {
                curValType = typeInt;
                tempInt = dynamic_cast<ConstValue *>(tempVal)->intVal;
            } else {
                curValType = typeFloat;
                tempFloat = dynamic_cast<ConstValue *>(tempVal)->floatVal;
            }
        } else {
            tempInt = 0;
        }
    } else {
        if (!tempVal->type->isPointer()) {
            throw InvalidIndexOperatorError();
        }
        bool useVal = false;
        int arrayIndex(0), arrayDimLen(1);
        Value *val = tempVal;
        Value *index = nullptr;
        for (int i = 1; i <= tempVal->arrayDims.size() - lVal->expList.size(); ++i) {
            arrayDimLen *= val->arrayDims[tempVal->arrayDims.size() - i];
        }
        for (int i(lVal->expList.size() - 1); i >= 0; i--) {
            lVal->expList[i]->accept(*this);
            if (useConst && !useVal) {
                arrayIndex += arrayDimLen * tempInt;
                arrayDimLen *= val->arrayDims[i];
            } else {
                if (!useVal) {
                    index = tempVal;
                    useVal = true;
                }else {
                    if (!useConst) {
                        Value *v1 = nullptr;
                        if (!isGlobal()) {
                            v1 = new VarValue(cur_func->varCnt++, "", typeInt);
                        } else {
                            v1 = new VarValue(cnt++, "", typeInt);
                        }
                        Value *v2 = nullptr;
                        if (!isGlobal()) {
                            v2 = new VarValue(cur_func->varCnt++, "", typeInt);
                        } else {
                            v2 = new VarValue(cnt++, "", typeInt);
                        }
                        cur_bb->pushIr(new MulIIR(v1, tempVal, arrayDimLen));
                        cur_bb->pushIr(new AddIR(v2, index, v1));
                        index = v2;
                    }else {
                        Value *v1 = nullptr;
                        if (!isGlobal()) {
                            v1 = new VarValue(cur_func->varCnt++, "", typeInt);
                        } else {
                            v1 = new VarValue(cnt++, "", typeInt);
                        }
                        int t = tempInt * arrayDimLen;
                        cur_bb->pushIr(new AddIIR(v1,index,t));
                        index = v1;
                    }
                }
                arrayDimLen *= val->arrayDims[i];
            }
        }
        tempVal = val;
        tempInt = arrayIndex;
        tempIndex = index;
        if (tempVal->arrayDims.size() == lVal->expList.size()) {
            tempVal->isArray = false;
            Value* v = nullptr;
            if (!isGlobal()) {
                v = new VarValue(cur_func->varCnt++,"",
                                 new Type(TypeID::POINTER,val->type->getContained()));
            }else {
                v = new VarValue(cnt++,"",
                                 new Type(TypeID::POINTER,val->type->getContained()));
            }
            if (arrayIndex != 0) {
                cur_bb->pushIr(new GEPIR(v,tempVal,arrayIndex));
            }else if (tempIndex) {
                cur_bb->pushIr(new GEPIR(v,tempVal,tempIndex));
                tempIndex = nullptr;
            }
            v->isArray = false;
            tempVal = v;
        }
        if (typeid(*val) == typeid(ConstValue)) {
            useConst = true;
            if (tempVal->type->isInt()) {
                curValType = typeInt;
                tempInt = dynamic_cast<ConstValue *>(tempVal)->intValList[arrayIndex];
            } else {
                curValType = typeFloat;
                tempFloat = dynamic_cast<ConstValue *>(tempVal)->floatValList[arrayIndex];
            }
        } else {
            useConst = false;
        }
    }
}

void IrVisitor::visit(PrimaryExp *primaryExp) {
    if (primaryExp->exp) {
        primaryExp->exp->accept(*this);
    } else if (primaryExp->lVal) {
        primaryExp->lVal->accept(*this);
        if (typeid(ConstValue) == typeid(*tempVal)) {
            return;
        }

        if (useArgs) {
            if (tempVal->isArray){
            VarValue *v = new VarValue(cur_func->varCnt++, "",
                                       new Type(TypeID::POINTER,
                                                tempVal->type->getContained()));
                if (tempIndex) {
                    cur_bb->pushIr(new GEPIR(v, tempVal, tempIndex));
                } else if (tempInt != 0) {
                    cur_bb->pushIr(new GEPIR(v, tempVal, tempInt));
                } else {
                    return;
                }
                tempVal = v;
                return;
            }else {
                Value* v = nullptr;
                if (tempVal->type->isIntPointer()) {
                    v = new VarValue(cur_func->varCnt++,"",typeInt);
                    cur_bb->pushIr(new LoadIIR(v,tempVal));
                }else {
                    v = new VarValue(cur_func->varCnt++,"",typeFloat);
                    cur_bb->pushIr(new LoadFIR(v,tempVal));
                }
                tempVal = v;
                return;
            }
        }

        VarValue *v = nullptr;
        if (!isGlobal()) {
            if (tempVal->type->getContained()->isInt()) {
                v = new VarValue(cur_func->varCnt++, "", typeInt);
            } else {
                v = new VarValue(cur_func->varCnt++, "", typeFloat);
            }
        } else {
            if (tempVal->type->getContained()->isInt()) {
                v = new VarValue(cnt++, "", typeInt);
            } else {
                v = new VarValue(cnt++, "", typeFloat);
            }
        }
        if (tempInt != 0 || tempIndex) {
            VarValue *v2 = nullptr;
            if (!isGlobal()) {
                v2 = new VarValue(cur_func->varCnt++, "",
                                  new Type(TypeID::POINTER, tempVal->type->getContained()));
            } else {
                v2 = new VarValue(cnt++, "",
                                  new Type(TypeID::POINTER, tempVal->type->getContained()));
            }
            if (tempIndex) {
                cur_bb->pushIr(new GEPIR(v2,tempVal,tempIndex));
            }else {
                cur_bb->pushIr(new GEPIR(v2, tempVal, tempInt));
            }
            if (v->type->isInt()) {
                cur_bb->pushIr(new LoadIIR(v, v2));
            } else {
                cur_bb->pushIr(new LoadFIR(v, v2));
            }
        }else {
            if (v->type->isInt()) {
                cur_bb->pushIr(new LoadIIR(v, tempVal));
            } else {
                cur_bb->pushIr(new LoadFIR(v, tempVal));
            }
        }
        tempVal = v;
        tempIndex = nullptr;
    } else if (primaryExp->number) {
        primaryExp->number->accept(*this);
    }
}

void IrVisitor::visit(Number *number) {
    if (number->type == type_specifier::TYPE_FLOAT) {
        tempFloat = number->floatNum;
        curValType = typeFloat;
    } else if (number->type == type_specifier::TYPE_INT) {
        tempInt = number->intNum;
        curValType = typeInt;
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
            if (tempVal->type->isInt()) {
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeInt);
                }
            } else {
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
        call_func = findFunc(unaryExp->identifier);
        if (unaryExp->funcRParams) {
            unaryExp->funcRParams->accept(*this);
        }
        if (call_func->return_type->isVoid()) {
            cur_bb->pushIr(new CallIR(call_func, args));
        } else {
            Value *v = nullptr;
            if (call_func->return_type->isInt()) {
                v = new VarValue(cur_func->varCnt++, "", typeInt);
            } else {
                v = new VarValue(cur_func->varCnt++, "", typeFloat);
            }
            useConst = false;
            tempVal = v;
            cur_bb->pushIr(new CallIR(call_func, args, v));
        }
    }
}

void IrVisitor::visit(FuncRParams *funcRParams) {
    if (funcRParams->expList.size() != call_func->params.size()) {
        throw ArgsNumberNotMatchError(call_func->name);
    }
    for (size_t i = 0; i < funcRParams->expList.size(); ++i) {
        useArgs = true;
        funcRParams->expList[i]->accept(*this);
        useArgs = false;
        if (!useConst) {
            args.push_back(tempVal);
        } else {
            ConstValue *val;
            if (curValType->isInt()) {
                val = new ConstValue(cur_func->varCnt++, "", typeInt);
                val->setInt(tempInt);
            } else {
                val = new ConstValue(cur_func->varCnt++, "", typeFloat);
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
        Type *lt = curValType;
        bool lUseConst = useConst;
        mulExp->unaryExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        Type *rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            assert(!(mulExp->op == mulop::OP_MOD &&
                     (lt->isFloat() || rt->isFloat())));
            if (lt->isFloat() && rt->isFloat()) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = lf * rf;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempFloat = lf / rf;
                }
            } else if (lt->isInt() & rt->isInt()) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempInt = li * ri;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempInt = li / ri;
                } else if (mulExp->op == mulop::OP_MOD) {
                    tempInt = li % ri;
                }
            } else if (lt->isFloat()) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = lf * ri;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempFloat = lf / ri;
                }
                curValType = typeFloat;
            } else if (lt->isInt()) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = li * rf;
                } else if (mulExp->op == mulop::OP_DIV) {
                    tempFloat = li / rf;
                }
                curValType = typeFloat;
            }
        } else if (lUseConst && !rUseConst) {
            if (lt->isInt() && right->type->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (lt->isInt() && right->type->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeInt);
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
            } else if (lt->isFloat() && right->type->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeInt);
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
            } else if (lt->isFloat() && right->type->isInt()) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    t = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, right);
                cur_bb->pushIr(ir1);
                right = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            if (left->type->isInt() && rt->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeInt);
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
            } else if (left->type->isInt() && rt->isFloat()) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    t = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, left);
                cur_bb->pushIr(ir1);
                left = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (left->type->isFloat() && rt->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (left->type->isFloat() && rt->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            if (left->type->isInt() && right->type->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, left);
                cur_bb->pushIr(ir);
                left = v;
            } else if (left->type->isFloat() && right->type->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, right);
                cur_bb->pushIr(ir);
                right = v;
            }
            VarValue *v = nullptr;
            if (!isGlobal()) {
                if (left->type->isInt()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                }
            } else {
                if (left->type->isInt()) {
                    v = new VarValue(cnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
        Type *lt = curValType;
        bool lUseConst = useConst;
        addExp->mulExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        Type *rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            if (lt->isFloat() && rt->isFloat()) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = lf + rf;
                } else if (addExp->op == addop::OP_SUB) {
                    tempFloat = lf - rf;
                }
            } else if (lt->isInt() & rt->isInt()) {
                if (addExp->op == addop::OP_ADD) {
                    tempInt = li + ri;
                } else if (addExp->op == addop::OP_SUB) {
                    tempInt = li - ri;
                }
            } else if (lt->isFloat()) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = lf + ri;
                } else if (addExp->op == addop::OP_SUB) {
                    tempFloat = lf - ri;
                }
                curValType = typeFloat;
            } else if (lt->isInt()) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = li + rf;
                } else if (addExp->op == addop::OP_SUB) {
                    tempFloat = li - rf;
                }
                curValType = typeFloat;
            }
        } else if (lUseConst && !rUseConst) {
            if (lt->isInt() && right->type->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (lt->isInt() && right->type->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeInt);
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
            } else if (lt->isFloat() && right->type->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (lt->isFloat() && right->type->isInt()) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    t = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, right);
                cur_bb->pushIr(ir1);
                right = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            if (left->type->isInt() && rt->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeInt);
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
            } else if (left->type->isInt() && rt->isFloat()) {
                VarValue *t = nullptr;
                if (!isGlobal()) {
                    t = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    t = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir1 = new CastInt2FloatIR(t, left);
                cur_bb->pushIr(ir1);
                left = t;

                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (left->type->isFloat() && rt->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            } else if (left->type->isFloat() && rt->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
            if (left->type->isInt() && right->type->isFloat()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, left);
                cur_bb->pushIr(ir);
                left = v;
            } else if (left->type->isFloat() && right->type->isInt()) {
                VarValue *v = nullptr;
                if (!isGlobal()) {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
                }
                CastInt2FloatIR *ir = new CastInt2FloatIR(v, right);
                cur_bb->pushIr(ir);
                right = v;
            }
            VarValue *v = nullptr;
            if (!isGlobal()) {
                if (left->type->isInt()) {
                    v = new VarValue(cur_func->varCnt++, "", typeInt);
                } else {
                    v = new VarValue(cur_func->varCnt++, "", typeFloat);
                }
            } else {
                if (left->type->isInt()) {
                    v = new VarValue(cnt++, "", typeInt);
                } else {
                    v = new VarValue(cnt++, "", typeFloat);
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
    } else {
        relExp->relExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        Type *lt = curValType;
        bool lUseConst = useConst;
        relExp->addExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        Type *rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            curValType = typeInt;
            switch (relExp->op) {
                case relop::OP_LT:
                    if (lt->isInt() && rt->isInt()) {
                        tempInt = (li < ri);
                    } else if (lt->isFloat() && rt->isFloat()) {
                        tempInt = (lf < rf);
                    } else if (lt->isInt() && rt->isFloat()) {
                        tempInt = (li < rf);
                    } else {
                        tempInt = (lf < ri);
                    }
                    break;
                case relop::OP_GT:
                    if (lt->isInt() && rt->isInt()) {
                        tempInt = (li > ri);
                    } else if (lt->isFloat() && rt->isFloat()) {
                        tempInt = (lf > rf);
                    } else if (lt->isInt() && rt->isFloat()) {
                        tempInt = (li > rf);
                    } else {
                        tempInt = (lf > ri);
                    }
                    break;
                case relop::OP_LE:
                    if (lt->isInt() && rt->isInt()) {
                        tempInt = (li <= ri);
                    } else if (lt->isFloat() && rt->isFloat()) {
                        tempInt = (lf <= rf);
                    } else if (lt->isInt() && rt->isFloat()) {
                        tempInt = (li <= rf);
                    } else {
                        tempInt = (lf <= ri);
                    }
                    break;
                case relop::OP_GE:
                    if (lt->isInt() && rt->isInt()) {
                        tempInt = (li >= ri);
                    } else if (lt->isFloat() && rt->isFloat()) {
                        tempInt = (lf >= rf);
                    } else if (lt->isInt() && rt->isFloat()) {
                        tempInt = (li >= rf);
                    } else {
                        tempInt = (lf >= ri);
                    }
                    break;
            }
        } else if (lUseConst && !rUseConst) {
            if (lt->isInt() && right->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v, li, right, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v, li, right, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v, li, right, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v, li, right, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt->isInt() && right->type->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);;
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelIIR(v, li, right, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelIIR(v, li, right, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelIIR(v, li, right, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelIIR(v, li, right, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt->isFloat() && right->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v, lf, right, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v, lf, right, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v, lf, right, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v, lf, right, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt->isFloat() && right->type->isInt()) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(t, right));
                right = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v, lf, right, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v, lf, right, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v, lf, right, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v, lf, right, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        } else if (!lUseConst && rUseConst) {
            if (left->type->isInt() && rt->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelIIR(v, left, ri, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelIIR(v, left, ri, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelIIR(v, left, ri, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelIIR(v, left, ri, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type->isInt() && rt->isFloat()) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(t, left));
                left = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v, left, rf, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v, left, rf, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v, left, rf, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v, left, rf, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type->isFloat() && rt->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v, left, ri, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v, left, ri, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v, left, ri, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v, left, ri, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type->isFloat() && rt->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (relExp->op) {
                    case relop::OP_LT:
                        ir = new RelFIR(v, left, rf, OP::LT);
                        break;
                    case relop::OP_GT:
                        ir = new RelFIR(v, left, rf, OP::GT);
                        break;
                    case relop::OP_LE:
                        ir = new RelFIR(v, left, rf, OP::LE);
                        break;
                    case relop::OP_GE:
                        ir = new RelFIR(v, left, rf, OP::GE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        } else if (!lUseConst && !rUseConst) {
            if (left->type->isInt() && right->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(v, left));
                left = v;
            } else if (left->type->isFloat() && right->type->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(v, right));
                right = v;
            }
            VarValue *v = nullptr;
            if (left->type->isInt()) {
                v = new VarValue(cur_func->varCnt++, "", typeInt);
            } else {
                v = new VarValue(cur_func->varCnt++, "", typeFloat);
            }
            Instruction *ir = nullptr;
            switch (relExp->op) {
                case relop::OP_LT:
                    ir = new RelIR(v, left, right, OP::LT);
                    break;
                case relop::OP_GT:
                    ir = new RelIR(v, left, right, OP::GT);
                    break;
                case relop::OP_LE:
                    ir = new RelIR(v, left, right, OP::LE);
                    break;
                case relop::OP_GE:
                    ir = new RelIR(v, left, right, OP::GE);
                    break;
            }
            tempVal = v;
            cur_bb->pushIr(ir);
        }
    }
}

void IrVisitor::visit(EqExp *eqExp) {
    if (!eqExp->eqExp) {
        eqExp->relExp->accept(*this);
    } else {
        eqExp->eqExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        Type *lt = curValType;
        bool lUseConst = useConst;
        eqExp->relExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        Type *rt = curValType;
        bool rUseConst = useConst;
        useConst = false;
        if (lUseConst && rUseConst) {
            useConst = true;
            curValType = typeInt;
            switch (eqExp->op) {
                case relop::OP_EQU:
                    if (lt->isInt() && rt->isInt()) {
                        tempInt = (li == ri);
                    } else if (lt->isFloat() && rt->isFloat()) {
                        tempInt = (lf == rf);
                    } else if (lt->isInt() && rt->isFloat()) {
                        tempInt = (li == rf);
                    } else {
                        tempInt = (lf == ri);
                    }
                    break;
                case relop::OP_NE:
                    if (lt->isInt() && rt->isInt()) {
                        tempInt = (li != ri);
                    } else if (lt->isFloat() && rt->isFloat()) {
                        tempInt = (lf != rf);
                    } else if (lt->isInt() && rt->isFloat()) {
                        tempInt = (li != rf);
                    } else {
                        tempInt = (lf != ri);
                    }
                    break;
            }
        } else if (lUseConst && !rUseConst) {
            if (lt->isInt() && right->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v, li, right, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v, li, right, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt->isInt() && right->type->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);;
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelIIR(v, li, right, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelIIR(v, li, right, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt->isFloat() && right->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v, lf, right, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v, lf, right, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (lt->isFloat() && right->type->isInt()) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(t, right));
                right = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v, lf, right, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v, lf, right, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        } else if (!lUseConst && rUseConst) {
            if (left->type->isInt() && rt->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelIIR(v, left, ri, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelIIR(v, left, ri, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type->isInt() && rt->isFloat()) {
                VarValue *t = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(t, left));
                left = t;
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v, left, rf, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v, left, rf, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type->isFloat() && rt->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v, left, ri, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v, left, ri, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            } else if (left->type->isFloat() && rt->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                Instruction *ir = nullptr;
                switch (eqExp->op) {
                    case relop::OP_EQU:
                        ir = new RelFIR(v, left, rf, OP::EQU);
                        break;
                    case relop::OP_NE:
                        ir = new RelFIR(v, left, rf, OP::NE);
                        break;
                }
                tempVal = v;
                cur_bb->pushIr(ir);
            }
        } else if (!lUseConst && !rUseConst) {
            if (left->type->isInt() && right->type->isFloat()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(v, left));
                left = v;
            } else if (left->type->isFloat() && right->type->isInt()) {
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeFloat);
                cur_bb->pushIr(new CastInt2FloatIR(v, right));
                right = v;
            }
            VarValue *v = nullptr;
            if (left->type->isInt()) {
                v = new VarValue(cur_func->varCnt++, "", typeInt);
            } else {
                v = new VarValue(cur_func->varCnt++, "", typeFloat);
            }
            Instruction *ir = nullptr;
            switch (eqExp->op) {
                case relop::OP_EQU:
                    ir = new RelIR(v, left, right, OP::EQU);
                    break;
                case relop::OP_NE:
                    ir = new RelIR(v, left, right, OP::NE);
                    break;
            }
            tempVal = v;
            cur_bb->pushIr(ir);
        }
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
        if (useConst) {
            if ((curValType->isInt() && tempInt != 0) ||
                (curValType == typeFloat && tempFloat != 0)) {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 1));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            } else {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 0));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            }
        } else {
            bb->val = tempVal;
        }
        cur_bb = new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
        if (typeid(*condBB.top()) == typeid(SelectBlock)) {
            dynamic_cast<SelectBlock *>(condBB.top())->cond.push_back(cur_bb);
        } else {
            dynamic_cast<IterationBlock *>(condBB.top())->cond.push_back(cur_bb);
        }
        lAndEXp->eqExp->accept(*this);
        bb = dynamic_cast<CondBlock *>(cur_bb);
        if (useConst) {
            if ((curValType->isInt() && tempInt != 0) ||
                (curValType == typeFloat && tempFloat != 0)) {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 1));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            } else {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 0));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            }
        } else {
            bb->val = tempVal;
        }
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
        if (useConst) {
            if ((curValType->isInt() && tempInt != 0) ||
                (curValType == typeFloat && tempFloat != 0)) {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 1));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            } else {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 0));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            }
        } else {
            bb->val = tempVal;
        }
        cur_bb = new CondBlock(cur_bb, cur_func->name, cur_func->bbCnt++);
        if (typeid(*condBB.top()) == typeid(SelectBlock)) {
            dynamic_cast<SelectBlock *>(condBB.top())->cond.push_back(cur_bb);
        } else {
            dynamic_cast<IterationBlock *>(condBB.top())->cond.push_back(cur_bb);
        }
        lOrExp->lAndExp->accept(*this);
        bb = dynamic_cast<CondBlock *>(cur_bb);
        if (useConst) {
            if ((curValType->isInt() && tempInt != 0) ||
                (curValType == typeFloat && tempFloat != 0)) {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 1));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            } else {
                VarValue *var = new VarValue(cur_func->varCnt++, "", new Type(TypeID::POINTER, typeInt));
                cur_bb->pushIr(new AllocIIR(var));
                cur_bb->pushIr(new StoreIIR(var, 0));
                VarValue *v = new VarValue(cur_func->varCnt++, "", typeInt);
                cur_bb->pushIr(new LoadIIR(v, var));
                bb->val = v;
            }
        } else {
            bb->val = tempVal;
        }
    }
}

void IrVisitor::visit(ConstExp *constExp) {
    constExp->addExp->accept(*this);
}

void IrVisitor::visit(UnaryOp *unaryOp) {}