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
    }else if (declDef->funcDef){
        declDef->funcDef->accept(*this);
    }else if (declDef->constDecl){
        declDef->constDecl->accept(*this);
    }else {
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
        Value *var = nullptr;
        if (useConst) {
            if (curDefType == TYPE::INT) {
                if (curValType == TYPE::INT) {
                    var = new Value(constDef->identifier,TYPE::INT,true,true,tempInt,tempInt);
                } else if (curValType == TYPE::FLOAT) {
                    var = new Value(constDef->identifier,TYPE::INT,true,true,tempFloat,tempFloat);
                }
                new AllocIIR(var,cur_bb);
            } else if (curDefType == TYPE::FLOAT) {
                if (curValType == TYPE::INT) {
                    var = new Value(constDef->identifier,TYPE::FLOAT,true,true,tempInt,tempInt);
                } else if (curValType == TYPE::FLOAT) {
                    var = new Value(constDef->identifier,TYPE::FLOAT,true,true,tempFloat,tempFloat);
                }
                new AllocFIR(var,cur_bb);
            }
        }else {
            if (curDefType == TYPE::FLOAT) {
                var = new Value(constDef->identifier,TYPE::FLOAT,false,true,0,0);
                new AllocIIR(var,cur_bb);
            }else {
                var = new Value(constDef->identifier,TYPE::INT,false,true,0,0);
                new AllocFIR(var,cur_bb);
            }
            Value* v = nullptr;
            if (tempVal->type != curDefType){
                if (curDefType == TYPE::INT) {
                    v = new Value(tempVal);
                    v->type = TYPE::INT;
                    new CastFloat2IntIR(v,tempVal,cur_bb);
                }else if (curDefType == TYPE::FLOAT){
                    v = new Value(tempVal);
                    v->type = TYPE::FLOAT;
                    new CastInt2FloatIR(v,tempVal,cur_bb);
                }
            }
            new StoreIR(var,v,cur_bb);
        }
        cur_bb->pushVar(var);
    }else {

    }
}
void IrVisitor::visit(ConstDefList *constDefList) {}
void IrVisitor::visit(ConstExpList *constExpList) {}
void IrVisitor::visit(ConstInitVal *constInitVal) {
    if (constInitVal->constExp) {
        constInitVal->constExp->accept(*this);
    }else {
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
    if (varDef->constExpList.empty()){
        if (varDef->initVal) {
            varDef->initVal->accept(*this);
        }
        Value *var = nullptr;
        if(useConst && varDef->initVal) {
            if (curDefType == TYPE::INT) {
                if (curValType == TYPE::INT) {
                    var = new Value(varDef->identifier,TYPE::INT,true,false,tempInt,tempInt);
                } else if (curValType == TYPE::FLOAT) {
                    var = new Value(varDef->identifier,TYPE::INT,true,false,tempFloat,tempFloat);
                }
                new AllocIIR(var,cur_bb);
            } else if (curDefType == TYPE::FLOAT) {
                if (curValType == TYPE::INT) {
                    var = new Value(varDef->identifier,TYPE::FLOAT,true,false,tempInt,tempInt);
                } else if (curValType == TYPE::FLOAT) {
                    var = new Value(varDef->identifier,TYPE::FLOAT,true,false,tempFloat,tempFloat);
                }
                new AllocFIR(var,cur_bb);
            }
        }else {
            if (curDefType == TYPE::FLOAT) {
                if (isGlobal()) {
                    var = new Value(varDef->identifier,TYPE::FLOAT,true,false,0,0);
                }else {
                    var = new Value(varDef->identifier, TYPE::FLOAT, false, false, 0, 0);
                }
                new AllocFIR(var,cur_bb);
            }else {
                if (isGlobal()){
                    var = new Value(varDef->identifier,TYPE::INT,true,false,0,0);
                }else {
                    var = new Value(varDef->identifier, TYPE::INT, false, false, 0, 0);
                }
                new AllocIIR(var,cur_bb);
            }
            if (varDef->initVal) {
                Value *v = nullptr;
                if (tempVal->type != curDefType) {
                    if (curDefType == TYPE::INT) {
                        v = new Value(tempVal);
                        v->type = TYPE::INT;
                        new CastFloat2IntIR(v, tempVal, cur_bb);
                    } else if (curDefType == TYPE::FLOAT) {
                        v = new Value(tempVal);
                        v->type = TYPE::FLOAT;
                        new CastInt2FloatIR(v, tempVal, cur_bb);
                    }
                }
                new StoreIR(var, v, cur_bb);
            }
        }
        cur_bb->pushVar(var);
    }else{
        auto t = new Value(varDef->identifier,curDefType,true);
        for (size_t i = 0; i < varDef->constExpList.size(); ++i) {
            varDef->constExpList[i]->accept(*this);
            assert(curValType == INT);
            t->dims.push_back(tempInt);
        }

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
void IrVisitor::visit(FuncDef *funcDef) {
    if (findFunc(funcDef->identifier)) {
        std::cerr << "Duplicate Function Definition of " << funcDef->identifier << std::endl;
    }
    auto en = new NormalBlock(entry);
    cur_bb = en;
    Function* function;
    if (funcDef->defType->type == type_specifier::TYPE_INT){
        function = new Function(funcDef->identifier,en,TYPE::INT);
    }else if (funcDef->defType->type == type_specifier::TYPE_FLOAT) {
        function = new Function(funcDef->identifier,en,TYPE::FLOAT);
    }else {
        function = new Function(funcDef->identifier,en,TYPE::VOID);
    }
    cur_func = function;
    functions.push_back(cur_func);
    if (funcDef->funcFParams) {
        funcDef->funcFParams->accept(*this);
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
            tempVal = new Value(funcFParam->identifier,TYPE::FLOAT, false, false,0,0);
            new AllocFIR(tempVal,cur_bb);
        }else if (funcFParam->defType->type == type_specifier::TYPE_INT){
            tempVal = new Value(funcFParam->identifier,TYPE::INT, false, false,0,0);
            new AllocIIR(tempVal,cur_bb);
        }
        cur_bb->pushVar(tempVal);
    }else {

    }
}
void IrVisitor::visit(ParamArrayExpList *paramArrayExpList) {}
void IrVisitor::visit(Block *block) {
    cur_bb = new NormalBlock(cur_bb);
    pushBB(cur_bb);
    for (size_t i = 0; i < block->blockItemList.size(); ++i) {
        block->blockItemList[i]->accept(*this);
        if (block->blockItemList[i]->stmt && (block->blockItemList[i]->stmt->block||
        block->blockItemList[i]->stmt->selectStmt ||
        block->blockItemList[i]->stmt->iterationStmt)) {
            cur_bb = new NormalBlock(cur_bb);
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
        if (cur_bb == cur_func->entry) {
            cur_bb = new NormalBlock(cur_bb);
            if (!ifBB.empty()){
                if (isIF) {
                    ifBB.top()->ifStmt.push_back(cur_bb);
                }else {
                    ifBB.top()->elseStmt.push_back(cur_bb);
                }
            }else {
                cur_func->pushBB(cur_bb);
            }
        }
    }
    if (blockItem->varDecl) {
        blockItem->varDecl->accept(*this);
    }else if (blockItem->constDecl){
        blockItem->constDecl->accept(*this);
    }else if (blockItem->stmt) {
        blockItem->stmt->accept(*this);
    }
}
void IrVisitor::visit(Stmt *stmt) {
    if (stmt->assignStmt){
       stmt->assignStmt->accept(*this);
    }else if (stmt->block){
        stmt->block->accept(*this);
    }else if (stmt->selectStmt) {
        stmt->selectStmt->accept(*this);
    }else if (stmt->iterationStmt) {
        stmt->iterationStmt->accept(*this);
    }else if (stmt->breakStmt) {
        stmt->breakStmt->accept(*this);
    }else if (stmt->returnStmt) {
        stmt->returnStmt->accept(*this);
    }
}
void IrVisitor::visit(AssignStmt *assignStmt) {
    assignStmt->lVal->accept(*this);
    auto left = tempVal;
    assignStmt->exp->accept(*this);
    if (useConst) {
        if (curValType == TYPE::INT) {
            new StoreIR(left,tempInt,cur_bb);
        }else if (curValType == TYPE::FLOAT) {
            new StoreIR(left,tempFloat,cur_bb);
        }
    }else {
        if (left->type != tempVal->type) {
            if (left->type == TYPE::INT) {
                auto v = new Value(tempVal);
                v->type = TYPE::INT;
                new CastFloat2IntIR(v,tempVal,cur_bb);
            }else if (left->type == TYPE::FLOAT){
                auto v = new Value(tempVal);
                v->type = TYPE::FLOAT;
                new CastInt2FloatIR(v,tempVal,cur_bb);
            }
        }
        new StoreIR(left,tempVal,cur_bb);
    }
}
void IrVisitor::visit(SelectStmt *selectStmt) {
    auto tempBB = cur_bb;
    cur_bb = new SelectBlock(cur_bb);
    pushBB(cur_bb);
    ifBB.push(dynamic_cast<SelectBlock*>(cur_bb));
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
    cur_bb = new IterationBlock(cur_bb);
    pushBB(cur_bb);
    whileBB.push(dynamic_cast<IterationBlock*>(cur_bb));
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
    if (useConst) {
        useConst = false;
        if ((curDefType == TYPE::INT && tempInt != 0 )||
                (curDefType == TYPE::FLOAT && tempFloat != 0)) {
            tempVal = new Value("",TYPE::INT,true,false,1,1);
        }else {
            tempVal = new Value("",TYPE::INT,true,false,0,1);
        }
    }
}
void IrVisitor::visit(LVal *lVal) {
    useConst = false;
    if (lVal->expList.empty()) {
        tempVal = findAllVal(lVal->identifier);
        if (!tempVal) {
            std::cerr << "Undefined Identifier of "  << lVal->identifier << std::endl;
        }
    }else {

    }
}
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

            } else if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                tempInt = -tempInt;
                tempFloat = -tempFloat;
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                tempInt = !tempInt;
                tempFloat = !tempFloat;
            }
        }else {
            auto ir = new Instruction;
            auto v = new Value(tempVal);
            if (unaryExp->unaryOp->op == unaryop::OP_POS) {
                new UnaryIR(v,tempVal,OP::POS,cur_bb);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NEG) {
                new UnaryIR(v,tempVal,OP::NEG,cur_bb);
            } else if (unaryExp->unaryOp->op == unaryop::OP_NOT) {
                new UnaryIR(v,tempVal,OP::NOT,cur_bb);
            }
        }
    }else {

    }
}
void IrVisitor::visit(FuncRParams *funcRParams) {}
void IrVisitor::visit(MulExp *mulExp) {
    if (!mulExp->mulExp) {
        mulExp->unaryExp->accept(*this);
    }else {
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
        if (lUseConst && rUseConst){
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
            if (lUseConst) {
                if (lt == TYPE::INT) {
                    left = new Value("",TYPE::INT,true,false,li,0);
                }else if (lt == TYPE::FLOAT) {
                    left = new Value("",TYPE::FLOAT,true,false,0,lf);
                }
            }
            if (rUseConst) {
                if (rt == TYPE::INT) {
                    right = new Value("",TYPE::INT,true,false,ri,0);
                }else if (rt == TYPE::FLOAT) {
                    right = new Value("",TYPE::FLOAT,true,false,0,rf);
                }
            }
            assert(!(mulExp->op == mulop::OP_MOD &&
                     (left->type == TYPE::FLOAT || right->type == TYPE::FLOAT)));
            if (left->type != right->type) {
                if (left->type == TYPE::FLOAT) {
                    auto v = new Value(right);
                    v->type = TYPE::FLOAT;
                    new CastInt2FloatIR(v,right,cur_bb);
                    right = v;
                } else {
                    auto v = new Value(left);
                    v->type = TYPE::FLOAT;
                    new CastInt2FloatIR(v,left,cur_bb);
                    left = v;
                }
                tempVal = new Value(left);
                if (mulExp->op == mulop::OP_MUL) {
                    new BinaryIR(tempVal,left,right,OP::MULF,cur_bb);
                } else {
                    new BinaryIR(tempVal,left,right,OP::DIVF,cur_bb);
                }
            } else {
                tempVal = new Value(left);
                if (left->type == TYPE::INT) {
                    if (mulExp->op == mulop::OP_MUL) {
                        new BinaryIR(tempVal,left,right,OP::MULI,cur_bb);
                    } else if (mulExp->op == mulop::OP_DIV) {
                        new BinaryIR(tempVal,left,right,OP::DIVI,cur_bb);
                    } else if (mulExp->op == mulop::OP_MOD) {
                        new BinaryIR(tempVal,left,right,OP::MOD,cur_bb);
                    }
                } else {
                    if (mulExp->op == mulop::OP_MUL) {
                        new BinaryIR(tempVal,left,right,OP::MULF,cur_bb);
                    } else if (mulExp->op == mulop::OP_DIV) {
                        new BinaryIR(tempVal,left,right,OP::DIVF,cur_bb);
                    }
                }
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
        bool lUseConst = useConst;
        addExp->mulExp->accept(*this);
        auto right = tempVal;
        int ri = tempInt;
        float rf = tempFloat;
        TYPE rt = curValType;
        bool rUseConst = useConst;
        if (lUseConst && rUseConst) {
            useConst = true;
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
            if (lUseConst) {
                if (lt == TYPE::INT) {
                    left = new Value("",TYPE::INT,true,false,li,0);
                }else if (lt == TYPE::FLOAT) {
                    left = new Value("",TYPE::FLOAT,true,false,0,lf);
                }
            }
            if (rUseConst) {
                if (rt == TYPE::INT) {
                    right = new Value("",TYPE::INT,true,false,ri,0);
                }else if (rt == TYPE::FLOAT) {
                    right = new Value("",TYPE::FLOAT,true,false,0,rf);
                }
            }
            if (left->type != right->type) {
                if (left->type == TYPE::FLOAT) {
                    auto v = new Value(right);
                    v->type = TYPE::FLOAT;
                    new CastInt2FloatIR(v,right,cur_bb);
                    right = v;
                } else {
                    auto v = new Value(left);
                    v->type = TYPE::FLOAT;
                    new CastInt2FloatIR(v,left,cur_bb);
                    left = v;
                }
                tempVal = new Value(left);
                if (addExp->op == addop::OP_ADD) {
                    new BinaryIR(tempVal,left,right,OP::ADDF,cur_bb);
                } else if (addExp->op == addop::OP_SUB) {
                    new BinaryIR(tempVal,left,right,OP::SUBF,cur_bb);
                }
            } else {
                if (left->type == TYPE::INT) {
                    if (addExp->op == addop::OP_ADD) {
                        new BinaryIR(tempVal,left,right,OP::ADDI,cur_bb);
                    } else if (addExp->op == addop::OP_SUB) {
                        new BinaryIR(tempVal,left,right,OP::SUBI,cur_bb);
                    }
                } else {
                    if (addExp->op == addop::OP_ADD) {
                        new BinaryIR(tempVal,left,right,OP::ADDF,cur_bb);
                    } else if (addExp->op == addop::OP_SUB) {
                        new BinaryIR(tempVal,left,right,OP::SUBF,cur_bb);
                    }
                }
            }
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