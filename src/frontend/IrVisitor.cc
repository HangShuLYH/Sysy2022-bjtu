//
// Created by hangshu on 22-4-26.
//
#include "IrVisitor.hh"
#include <iostream>
void IrVisitor::visit(CompUnit *compUnit) {
    for (size_t i = 0; i < compUnit->declDefList.size(); ++i) {
        compUnit->declDefList[i]->accept(*this);
    }
}
void IrVisitor::visit(DeclDef *declDef) {
    if (declDef->varDecl) {
        declDef->varDecl->accept(*this);
    }else if (declDef->funcDef){
        declDef->funcDef->accept(*this);
    }else if (declDef->constDecl){
        declDef->funcDef->accept(*this);
    }else {
        std::cerr << "This should never be seen in IrVisitor(DeclDef)!" << std::endl;
    }
}
void IrVisitor::visit(ConstDecl *constDecl) {}
void IrVisitor::visit(ConstDef *constDef) {}
void IrVisitor::visit(ConstDefList *constDefList) {}
void IrVisitor::visit(ConstExpList *constExpList) {}
void IrVisitor::visit(ConstInitVal *constInitVal) {}
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
    if (varDef->constExpList.size() == 0){
        if (varDef->initVal) {
            varDef->initVal->accept(*this);
        }
        Instruction *ir = new Instruction;
        Value *var = nullptr;
        if (curDefType == TYPE::FLOAT) {
            if (useConst && varDef->initVal) {
                var = Instruction::CreateAllocFIR(varDef->identifier, true,tempFloat,ir);
            }else {
                var = Instruction::CreateAllocFIR(varDef->identifier, false,0,ir);
            }
        }else if (curDefType == TYPE::INT){
            if (useConst && varDef->initVal) {
                if (curValType == TYPE::FLOAT) {
                    var = Instruction::CreateAllocIIR(varDef->identifier, true, tempFloat, ir);
                }else if(curValType == TYPE::INT){
                    var = Instruction::CreateAllocIIR(varDef->identifier, true, tempInt, ir);
                }
            }else {
                if (curValType == TYPE::FLOAT) {
                    var = Instruction::CreateAllocFIR(varDef->identifier, true, tempFloat, ir);
                }else if(curValType == TYPE::INT){
                    var = Instruction::CreateAllocFIR(varDef->identifier, true, tempInt, ir);
                }
            }
        }
        var->name = varDef->identifier;
        cur_bb->push(ir);
        ir = new Instruction;
        if (!useConst && varDef->initVal) {
            if (tempVal->type != curDefType){
                if (curDefType == TYPE::INT) {
                    tempVal = Instruction::CreateCastFloat2IntIR(tempVal,ir);
                }else if (curDefType == TYPE::FLOAT){
                    tempVal = Instruction::CreateCastInt2FloatIR(tempVal,ir);
                }
                cur_bb->push(ir);
            }
            ir = new Instruction;
            tempVal = Instruction::CreateLoadIR(var,tempVal,ir);
            cur_bb->push(ir);
        }
        auto v = std::shared_ptr<Value>(var);
        if (isGlobal()) {
            globalVars.push_back(v);
        }
        vars.push_back(v);
    }else{

    }
}
void IrVisitor::visit(InitVal *initVal) {
    if (initVal->exp) {
        initVal->exp->accept(*this);
    }else {
        for (size_t i = 0; i < initVal->initValList.size(); ++i){
            initVal->initValList[i]->accept(*this);
        }
    }
}
void IrVisitor::visit(InitValList *initValList) {}
void IrVisitor::visit(FuncDef *funcDef) {}
void IrVisitor::visit(DefType *defType) {}
void IrVisitor::visit(FuncFParams *funcFParams) {}
void IrVisitor::visit(FuncFParam *funcFParam) {}
void IrVisitor::visit(ParamArrayExpList *paramArrayExpList) {}
void IrVisitor::visit(Block *block) {}
void IrVisitor::visit(BlockItemList *blockItemList) {}
void IrVisitor::visit(BlockItem *blockItem) {}
void IrVisitor::visit(Stmt *stmt) {}
void IrVisitor::visit(AssignStmt *assignStmt) {}
void IrVisitor::visit(SelectStmt *selectStmt) {}
void IrVisitor::visit(IterationStmt *iterationStmt) {}
void IrVisitor::visit(BreakStmt *breakStmt) {}
void IrVisitor::visit(ContinueStmt *continueStmt) {}
void IrVisitor::visit(ReturnStmt *returnStmt) {}
void IrVisitor::visit(Exp *exp) {
    exp->addExp->accept(*this);
}
void IrVisitor::visit(Cond *cond) {}
void IrVisitor::visit(LVal *lVal) {}
void IrVisitor::visit(PrimaryExp *primaryExp) {
    if (primaryExp->exp) {
        primaryExp->exp->accept(*this);
    }else if (primaryExp->lVal) {
        primaryExp->lVal->accept(*this);
    }else if(primaryExp->number) {
        primaryExp->number->accept(*this);
    }
}
void IrVisitor::visit(Number *number) {
    if (number->type == type_specifier::TYPE_FLOAT) {
        tempFloat = number->floatNum;
        curValType = TYPE::FLOAT;
    }else if (number->type == type_specifier::TYPE_INT) {
        tempInt = number->intNum;
        curValType = TYPE::INT;
    }
    useConst = true;
}
void IrVisitor::visit(UnaryExp *unaryExp) {
    if (unaryExp->primaryExp) {
        unaryExp->primaryExp->accept(*this);
    }else if (unaryExp->unaryExp) {
        unaryExp->unaryExp->accept(*this);
        if (useConst){
            if (unaryExp->unaryOp->op == unaryop::OP_POS) {
                tempInt = tempInt;
                tempFloat = tempFloat;
            } else if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                tempInt = -tempInt;
                tempFloat = -tempFloat;
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                tempInt = !tempInt;
                tempFloat = !tempFloat;
            }
        }else {
            Instruction* ir = new Instruction;
            if (unaryExp->unaryOp->op == unaryop::OP_POS) {
                tempVal = Instruction::CreateUnaryPOSIR(tempVal, ir);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                tempVal = Instruction::CreateUnaryNEGIR(tempVal, ir);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                tempVal = Instruction::CreateUnaryNOTIR(tempVal, ir);
            }
            cur_bb->push(ir);
        }
    }else {

    }
}
void IrVisitor::visit(FuncRParams *funcRParams) {}
void IrVisitor::visit(MulExp *mulExp) {
    if (!mulExp->mulExp) {
        mulExp->unaryExp->accept(*this);
    }else {
        mulExp->unaryExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        TYPE lt = curValType;
        mulExp->mulExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        if (useConst){
            assert(!(mulExp->op == mulop::OP_MOD &&
                    (lt == TYPE::FLOAT || rt == TYPE::FLOAT)));
            if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = lf * rf;
                }else if (mulExp->op == mulop::OP_DIV){
                    tempFloat = lf/rf;
                }
            }else if (lt == TYPE::INT & rt == TYPE::INT) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempInt = li * ri;
                }else if (mulExp->op == mulop::OP_DIV){
                    tempInt = li/ri;
                }else if (mulExp->op == mulop::OP_MOD){
                    tempInt = li % ri;
                }
            }else if (lt == TYPE::FLOAT) {
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = lf * ri;
                }else if (mulExp->op == mulop::OP_DIV){
                    tempFloat = lf / ri;
                }
                curValType = TYPE::FLOAT;
            }else if (lt == TYPE::INT){
                if (mulExp->op == mulop::OP_MUL) {
                    tempFloat = li * rf;
                }else if (mulExp->op == mulop::OP_DIV){
                    tempFloat = li / rf;
                }
                curValType = TYPE::FLOAT;
            }
        }else {
            useConst = false;
            assert(!(mulExp->op == mulop::OP_MOD &&
                     (left->type == TYPE::FLOAT || right->type == TYPE::FLOAT)));
            if (left->type != right->type) {
                Instruction *ir = new Instruction;
                if (left->type == TYPE::FLOAT) {
                    right = Instruction::CreateCastInt2FloatIR(right, ir);
                } else {
                    left = Instruction::CreateCastInt2FloatIR(left, ir);
                }
                cur_bb->push(ir);
                ir = new Instruction;
                if (mulExp->op == mulop::OP_MUL) {
                    tempVal = Instruction::CreateMULFIR(left, right, ir);
                } else {
                    tempVal = Instruction::CreateDIVFIR(left, right, ir);
                }
                cur_bb->push(ir);
            } else {
                Instruction *ir = new Instruction;
                if (left->type == TYPE::INT) {
                    if (mulExp->op == mulop::OP_MUL) {
                        tempVal = Instruction::CreateMULIIR(left, right, ir);
                    } else if (mulExp->op == mulop::OP_DIV) {
                        tempVal = Instruction::CreateDIVIIR(left, right, ir);
                    } else if (mulExp->op == mulop::OP_MOD) {
                        tempVal = Instruction::CreateMODIR(left, right, ir);
                    }
                } else {
                    if (mulExp->op == mulop::OP_MUL) {
                        tempVal = Instruction::CreateMULFIR(left, right, ir);
                    } else if (mulExp->op == mulop::OP_DIV) {
                        tempVal = Instruction::CreateDIVFIR(left, right, ir);
                    }
                }
                cur_bb->push(ir);
            }
        }
    }
}
void IrVisitor::visit(AddExp *addExp) {
    if (!addExp->addExp) {
        addExp->mulExp->accept(*this);
    }else {
        addExp->addExp->accept(*this);
        auto left = tempVal;
        int li = tempInt;
        float lf = tempFloat;
        TYPE lt = curValType;
        addExp->mulExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        if (useConst) {
            if (lt == TYPE::FLOAT && rt == TYPE::FLOAT){
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = lf + rf;
                }else if (addExp->op == addop::OP_SUB){
                    tempFloat = lf - rf;
                }
            }else if (lt == TYPE::INT & rt == TYPE::INT) {
                if (addExp->op == addop::OP_ADD) {
                    tempInt = li + ri;
                }else if (addExp->op == addop::OP_SUB){
                    tempInt = li - ri;
                }
            }else if (lt == TYPE::FLOAT) {
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = lf + ri;
                }else if (addExp->op == addop::OP_SUB){
                    tempFloat = lf - ri;
                }
                curValType = TYPE::FLOAT;
            }else if (lt == TYPE::INT){
                if (addExp->op == addop::OP_ADD) {
                    tempFloat = li + rf;
                }else if (addExp->op == addop::OP_SUB){
                    tempFloat = li - rf;
                }
                curValType = TYPE::FLOAT;
            }
        }else {
            useConst = false;
            if (left->type != right->type) {
                Instruction *ir = new Instruction;
                if (left->type == TYPE::FLOAT) {
                    right = Instruction::CreateCastInt2FloatIR(right, ir);
                } else {
                    left = Instruction::CreateCastInt2FloatIR(left, ir);
                }
                cur_bb->push(ir);
                ir = new Instruction;
                if (addExp->op == addop::OP_ADD) {
                    tempVal = Instruction::CreateADDFIR(left, right, ir);
                } else if (addExp->op == addop::OP_SUB) {
                    tempVal = Instruction::CreateSUBFIR(left, right, ir);
                }
                cur_bb->push(ir);
            } else {
                Instruction *ir = new Instruction;
                if (left->type == TYPE::INT) {
                    if (addExp->op == addop::OP_ADD) {
                        tempVal = Instruction::CreateADDIIR(left, right, ir);
                    } else if (addExp->op == addop::OP_SUB) {
                        tempVal = Instruction::CreateSUBIIR(left, right, ir);
                    }
                } else {
                    if (addExp->op == addop::OP_ADD) {
                        tempVal = Instruction::CreateADDFIR(left, right, ir);
                    } else if (addExp->op == addop::OP_SUB) {
                        tempVal = Instruction::CreateSUBFIR(left, right, ir);
                    }
                }
                cur_bb->push(ir);
            }
        }
    }
}
void IrVisitor::visit(RelExp *relExp) {}
void IrVisitor::visit(EqExp *eqExp) {}
void IrVisitor::visit(LAndExp *lAndEXp) {}
void IrVisitor::visit(LOrExp *lOrExp) {}
void IrVisitor::visit(ConstExp *constExp) {}
void IrVisitor::visit(UnaryOp *unaryOp) {}