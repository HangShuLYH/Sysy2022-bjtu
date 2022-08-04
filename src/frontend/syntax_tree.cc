//
// Created by 6220302 on 2022-04-16.
//
#include "syntax_tree.hh"
#define DEBUG
#define space(x) for(int i = 0;i < (x);i++){std::cout<<"--";}

void CompUnit::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "CompUnit" << std::endl;
#endif
    for (int i = 0; i < declDefList.size(); i++) {
        declDefList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "CompUnit" << std::endl;
#endif
}

void DeclDef::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "DeclDef" << std::endl;
#endif
    if (constDecl) {
        constDecl->visit(depth + 1);
    } else if (varDecl) {
        varDecl->visit(depth + 1);
    } else {
        funcDef->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "DeclDef" << std::endl;
#endif
}

void ConstDecl::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstDecl" << std::endl;
#endif
    defType->visit(depth + 1);
    for (int i = 0; i < constDefList.size(); i++) {
        constDefList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ConstDecl" << std::endl;
#endif
}

void ConstDefList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstDefList" << std::endl;
#endif
    for (int i = 0; i < constDefList.size(); i++) {
        constDefList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ConstDefList" << std::endl;
#endif
}

void ConstDef::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstDef" << std::endl;
    space(depth + 1);
    std::cout << "id:" << identifier << std::endl;
#endif
    for (int i = 0; i < constExpList.size(); ++i) {
        constExpList[i]->visit(depth + 1);
    }
    constInitVal->visit(depth + 1);
#ifdef DEBUG
    space(depth);
    std::cout << "ConstDef" << std::endl;
#endif
}

void ConstExpList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstExpList" << std::endl;
#endif
    for (int i = 0; i < constExpList.size(); ++i) {
        constExpList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ConstExpList" << std::endl;
#endif
}

void ConstInitVal::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstInitVal" << std::endl;
#endif
    if (constExp) {
        constExp->visit(depth + 1);
    } else {
        for (int i = 0; i < constInitValList.size(); ++i) {
            constInitValList[i]->visit(depth + 1);
        }
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ConstInitVal" << std::endl;
#endif
}

void ConstInitValList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstInitValList" << std::endl;
#endif
    for (int i = 0; i < constInitValList.size(); ++i) {
        constInitValList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ConstInitValList" << std::endl;
#endif
}

void VarDecl::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "VarDecl" << std::endl;
#endif
    defType->visit(depth + 1);
    for (int i = 0; i < varDefList.size(); ++i) {
        varDefList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "VarDecl" << std::endl;
#endif
}

void VarDef::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "VarDef" << std::endl;
    space(depth + 1);
    std::cout << "id:" << identifier << std::endl;
#endif
    for (int i = 0; i < constExpList.size(); ++i) {
        constExpList[i]->visit(depth + 1);
    }
    if (initVal) {
        initVal->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "VarDef" << std::endl;
#endif
}

void VarDefList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "VarDefList" << std::endl;
#endif
    for (int i = 0; i < varDefList.size(); ++i) {
        varDefList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "VarDefList" << std::endl;
#endif
}

void InitVal::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "InitVal" << std::endl;
#endif
    if (exp) {
        exp->visit(depth + 1);
    } else {
        for (int i = 0; i < initValList.size(); ++i) {
            initValList[i]->visit(depth + 1);
        }
    }
#ifdef DEBUG
    space(depth);
    std::cout << "InitVal" << std::endl;
#endif
}

void InitValList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "InitValList" << std::endl;
#endif
    for (int i = 0; i < initValList.size(); ++i) {
        initValList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "InitValList" << std::endl;
#endif
}

void FuncDef::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "FuncDef" << std::endl;
#endif
    defType->visit(depth + 1);
#ifdef DEBUG
    space(depth + 1);
    std::cout << "id:" << identifier << std::endl;
#endif
    if (funcFParams) {
        funcFParams->visit(depth + 1);
    }
    block->visit(depth + 1);
#ifdef DEBUG
    space(depth);
    std::cout << "FuncDef" << std::endl;
#endif
}

void DefType::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "DefType" << std::endl;
    space(depth + 1);
    if (type == type_specifier::TYPE_VOID) {
        std::cout << "void" << std::endl;
    } else if (type == type_specifier::TYPE_INT) {
        std::cout << "int" << std::endl;
    } else if (type == type_specifier::TYPE_FLOAT) {
        std::cout << "float" << std::endl;
    }
    space(depth);
    std::cout << "DefType" << std::endl;
#endif
}

void FuncFParams::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "FuncFParamas" << std::endl;
#endif
    for (int i = 0; i < funcFParamList.size(); ++i) {
        funcFParamList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "FuncFParamas" << std::endl;
#endif
}

void FuncFParam::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "FuncFParam" << std::endl;
#endif
    defType->visit(depth + 1);
#ifdef DEBUG
    space(depth + 1);
    std::cout << "id:" << identifier << std::endl;
#endif
    for (int i = 0; i < expList.size(); ++i) {
        expList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "FuncFParam" << std::endl;
#endif
}

void ParamArrayExpList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ParamArrayExpList" << std::endl;
#endif
    for (int i = 0; i < expList.size(); ++i) {
        expList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ParamArrayExpList" << std::endl;
#endif
}

void Block::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "Block" << std::endl;
#endif
    for (int i = 0; i < blockItemList.size(); ++i) {
        blockItemList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "Block" << std::endl;
#endif
}

void BlockItemList::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "BlockItemList" << std::endl;
#endif
    for (int i = 0; i < blockItemList.size(); ++i) {
        blockItemList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "BlockItemList" << std::endl;
#endif
}

void BlockItem::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "BlockItem" << std::endl;
#endif
    if (constDecl) {
        constDecl->visit(depth + 1);
    } else if (varDecl) {
        varDecl->visit(depth + 1);
    } else if (stmt) {
        stmt->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "BlockItem" << std::endl;
#endif
}

void Stmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "Stmt" << std::endl;
#endif
    if (exp) {
        exp->visit(depth+1);
    }else if (assignStmt) {
        assignStmt->visit(depth+1);
    }else if (block){
        block->visit(depth+1);
    }else if (selectStmt){
        selectStmt->visit(depth+1);
    }else if(iterationStmt){
        iterationStmt->visit(depth+1);
    }else if (breakStmt){
        breakStmt->visit(depth+1);
    }else if (returnStmt){
        returnStmt->visit(depth+1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "Stmt" << std::endl;
#endif
}
void AssignStmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "AssignStmt" << std::endl;
#endif
    lVal->visit(depth+1);
    exp->visit(depth+1);
#ifdef DEBUG
    space(depth);
    std::cout << "AssignStmt" << std::endl;
#endif
}
void SelectStmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "SelectStmt" << std::endl;
#endif
    cond->visit(depth+1);
    if (ifStmt) {
        ifStmt->visit(depth + 1);
    }
    if (elseStmt){
        elseStmt->visit(depth+1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "SelectStmt" << std::endl;
#endif
}
void IterationStmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "IterationStmt" << std::endl;
#endif
    cond->visit(depth+1);
    if (stmt) {
        stmt->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "IterationStmt" << std::endl;
#endif
}
void BreakStmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "BreakStmt" << std::endl;
#endif
#ifdef DEBUG
    space(depth);
    std::cout << "BreakStmt" << std::endl;
#endif
}
void ContinueStmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ContinueStmt" << std::endl;
#endif
#ifdef DEBUG
    space(depth);
    std::cout << "ContinueStmt" << std::endl;
#endif
}

void ReturnStmt::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ReturnStmt" << std::endl;
#endif
    if (exp) {
        exp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "ReturnStmt" << std::endl;
#endif
}

void Exp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "Exp" << std::endl;
#endif
    addExp->visit(depth + 1);
#ifdef DEBUG
    space(depth);
    std::cout << "Exp" << std::endl;
#endif
}

void Cond::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "Cond" << std::endl;
#endif
    lOrExp->visit(depth + 1);
#ifdef DEBUG
    space(depth);
    std::cout << "Cond" << std::endl;
#endif
}

void LVal::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "LVal" << std::endl;
    space(depth + 1);
    std::cout << "id:" << identifier << std::endl;
#endif
    for (int i = 0; i < expList.size(); ++i) {
        expList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "LVal" << std::endl;
#endif
}

void PrimaryExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "PrimaryExp" << std::endl;
#endif
    if (exp) {
        exp->visit(depth + 1);
    } else if (lVal) {
        lVal->visit(depth + 1);
    } else if (number) {
        number->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "PrimaryExp" << std::endl;
#endif
}

void Number::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "Number" << std::endl;
    space(depth + 1);
    if (type == type_specifier::TYPE_INT) {
        std::cout << "int:" << intNum << std::endl;
    } else if (type == type_specifier::TYPE_FLOAT) {
        std::cout << "float:" << floatNum << std::endl;
    }
    space(depth);
    std::cout << "Number" << std::endl;
#endif
}

void UnaryExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "UnaryExp" << std::endl;
#endif
    if (primaryExp) {
        primaryExp->visit(depth + 1);
    } else if (funcRParams) {
#ifdef DEBUG
        space(depth + 1);
        std::cout << "id:" << identifier << std::endl;
#endif
        funcRParams->visit(depth + 1);
    } else if (unaryOp) {
        unaryOp->visit(depth + 1);
        unaryExp->visit(depth + 1);
    } else if (identifier != ""){
#ifdef DEBUG
        space(depth + 1);
        std::cout << "id:" << identifier << std::endl;
#endif
    } else {
        space(depth + 1);
        std::cout << "stringConst:" << stringConst << std::endl;
    }
#ifdef DEBUG
    space(depth);
    std::cout << "UnaryExp" << std::endl;
#endif
}

void UnaryOp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "UnaryOp" << std::endl;
    if (op == unaryop::OP_POS) {
        space(depth + 1);
        std::cout << "+" << std::endl;
    } else if (op == unaryop::OP_NEG) {
        space(depth + 1);
        std::cout << "-" << std::endl;
    } else if (op == unaryop::OP_NOT) {
        space(depth + 1);
        std::cout << "!" << std::endl;
    }
    space(depth);
    std::cout << "UnaryOp" << std::endl;
#endif
}

void FuncRParams::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "FuncFParams" << std::endl;
#endif
    for (int i = 0; i < expList.size(); ++i) {
        expList[i]->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "FuncFParams" << std::endl;
#endif
}

void MulExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "MulExp" << std::endl;
#endif
    if (mulExp) {
        mulExp->visit(depth + 1);
#ifdef DEBUG
        space(depth + 1);
        if (op == mulop::OP_MUL) {
            std::cout << "*" << std::endl;
        } else if (op == mulop::OP_DIV) {
            std::cout << "/" << std::endl;
        } else if (op == mulop::OP_MOD) {
            std::cout << "%" << std::endl;
        }
#endif
        unaryExp->visit(depth + 1);
    } else {
        unaryExp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "MulExp" << std::endl;
#endif
}

void AddExp::visit(int depth) {
#ifdef DEBUG
    space(depth + 1);
    std::cout << "AddExp" << std::endl;
#endif
    if (addExp) {
        addExp->visit(depth + 1);
#ifdef DEBUG
        space(depth + 1);
        if (op == addop::OP_ADD) {
            std::cout << "+" << std::endl;
        } else if (op == addop::OP_SUB) {
            std::cout << "-" << std::endl;
        }
#endif
        mulExp->visit(depth + 1);
    } else {
        mulExp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth + 1);
    std::cout << "AddExp" << std::endl;
#endif
}

void RelExp::visit(int depth) {
#ifdef DEBUG
    space(depth + 1);
    std::cout << "RelExp" << std::endl;
#endif
    if (relExp) {
        relExp->visit(depth + 1);
#ifdef DEBUG
        space(depth + 1);
        if (op == relop::OP_LT) {
            std::cout << "<" << std::endl;
        } else if (op == relop::OP_LE) {
            std::cout << "<=" << std::endl;
        } else if (op == relop::OP_GT) {
            std::cout << ">" << std::endl;
        } else if (op == relop::OP_GE) {
            std::cout << ">=" << std::endl;
        }
#endif
        addExp->visit(depth + 1);
    } else {
        addExp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth + 1);
    std::cout << "RelExp" << std::endl;
#endif
}

void EqExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "EqExp" << std::endl;
#endif
    if (eqExp) {
        eqExp->visit(depth + 1);
#ifdef DEBUG
        space(depth + 1);
        if (op == relop::OP_EQU) {
            std::cout << "==" << std::endl;
        } else if (op == relop::OP_NE) {
            std::cout << "!=" << std::endl;
        }
#endif
        relExp->visit(depth + 1);
    } else {
        relExp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "EqExp" << std::endl;
#endif
}

void LAndExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "LAndExp" << std::endl;
#endif
    if (lAndExp) {
        lAndExp->visit(depth + 1);
        eqExp->visit(depth + 1);
    } else {
        eqExp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "LAndExp" << std::endl;
#endif
}

void LOrExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "LOrExp" << std::endl;
#endif
    if (lOrExp) {
        lOrExp->visit(depth + 1);
        lAndExp->visit(depth + 1);
    } else {
        lAndExp->visit(depth + 1);
    }
#ifdef DEBUG
    space(depth);
    std::cout << "LOrExp" << std::endl;
#endif
}

void ConstExp::visit(int depth) {
#ifdef DEBUG
    space(depth);
    std::cout << "ConstExp" << std::endl;
#endif
    addExp->visit(depth + 1);
#ifdef DEBUG
    space(depth);
    std::cout << "ConstExp" << std::endl;
#endif
}

void CompUnit::accept(Visitor &visitor) {
    visitor.visit(this);
}
void DeclDef::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstDecl::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstDefList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstDef::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstExpList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstInitVal::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstInitValList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void VarDecl::accept(Visitor &visitor) {
    visitor.visit(this);
}
void VarDef::accept(Visitor &visitor) {
    visitor.visit(this);
}
void VarDefList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void InitVal::accept(Visitor &visitor) {
    visitor.visit(this);
}
void InitValList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void FuncDef::accept(Visitor &visitor) {
    visitor.visit(this);
}
void DefType::accept(Visitor &visitor) {
    visitor.visit(this);
}
void FuncFParams::accept(Visitor &visitor) {
    visitor.visit(this);
}
void FuncFParam::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ParamArrayExpList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void Block::accept(Visitor &visitor) {
    visitor.visit(this);
}
void BlockItemList::accept(Visitor &visitor) {
    visitor.visit(this);
}
void BlockItem::accept(Visitor &visitor) {
    visitor.visit(this);
}
void Stmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void AssignStmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void SelectStmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void IterationStmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void BreakStmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ContinueStmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ReturnStmt::accept(Visitor &visitor) {
    visitor.visit(this);
}
void Exp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void Cond::accept(Visitor &visitor) {
    visitor.visit(this);
}
void LVal::accept(Visitor &visitor) {
    visitor.visit(this);
}
void PrimaryExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void Number::accept(Visitor &visitor) {
    visitor.visit(this);
}
void UnaryExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void UnaryOp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void FuncRParams::accept(Visitor &visitor) {
    visitor.visit(this);
}
void MulExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void AddExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void RelExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void EqExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void LAndExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void LOrExp::accept(Visitor &visitor) {
    visitor.visit(this);
}
void ConstExp::accept(Visitor &visitor) {
    visitor.visit(this);
}