//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_IRVISITOR_HH
#define SYSY2022_BJTU_IRVISITOR_HH

#include <vector>
#include <memory>
#include "CompileUnit.hh"
#include "Function.hh"
#include "parser.hh"
#include "syntax_tree.hh"
#include <stack>

class IrVisitor : public Visitor {
public:
    std::vector<Function*> functions;
    std::vector<Value*> globalVars;
    Function *cur_func = nullptr;
    BasicBlock *entry = nullptr;
    int cnt = 0;
    BasicBlock *cur_bb = nullptr;
    std::stack<SelectBlock *> ifBB;
    std::stack<IterationBlock *> whileBB;
    bool isIF = false;
    TYPE curDefType;
    bool useConst;
    TYPE curValType;
    int tempInt;
    float tempFloat;
    Value *tempVal;

    IrVisitor() {
        entry = new NormalBlock(nullptr,0);
        cur_bb = entry;
    }
    void print() {
        std::cout << "globalVars:" << std::endl;
        for (size_t i = 0; i < globalVars.size(); ++i) {
            std::cout << "\t";
            globalVars[i]->print();
            std::cout << std::endl;
        }
        std::cout << ".entryBB:" << std::endl;
        entry->print();
        for (size_t i = 0; i < functions.size(); ++i) {
            functions[i]->print();
        }
    }
    inline bool isGlobal() {
        if (cur_bb == entry) {
            return true;
        }
        return false;
    }

    inline Value *
    findAllVal(std::string name) {
        BasicBlock *bb = cur_bb;
        while (bb) {
            for (size_t i = 0; i < bb->vars.size(); ++i) {
                if (bb->vars[i]->name == name) {
                    return bb->vars[i];
                }
            }
            bb = bb->parent;
        }
        for (size_t i = 0; i < globalVars.size(); ++i) {
            if (globalVars[i]->name == name) {
                return globalVars[i];
            }
        }
        return nullptr;
    }

    inline bool findFunc(std::string name) {
        for (size_t i = 0; i < functions.size(); ++i) {
            if (functions[i]->name == name) return true;
        }
        return false;
    }

    inline void pushBB(BasicBlock *) {
        if (!ifBB.empty()) {
            if (isIF) {
                ifBB.top()->ifStmt.push_back(cur_bb);
            } else {
                ifBB.top()->elseStmt.push_back(cur_bb);
            }
        } else if (!whileBB.empty()) {
            whileBB.top()->whileStmt.push_back(cur_bb);
        } else {
            cur_func->pushBB(cur_bb);
        }
    }

    virtual void visit(CompUnit *compUnit);

    virtual void visit(DeclDef *declDef);

    virtual void visit(ConstDecl *constDecl);

    virtual void visit(ConstDef *constDef);

    virtual void visit(ConstDefList *constDefList);

    virtual void visit(ConstExpList *constExpList);

    virtual void visit(ConstInitVal *constInitVal);

    virtual void visit(ConstInitValList *constInitValList);

    virtual void visit(VarDecl *varDecl);

    virtual void visit(VarDefList *varDefList);

    virtual void visit(VarDef *varDef);

    virtual void visit(InitVal *initVal);

    virtual void visit(InitValList *initValList);

    virtual void visit(FuncDef *funcDef);

    virtual void visit(DefType *defType);

    virtual void visit(FuncFParams *funcFParams);

    virtual void visit(FuncFParam *funcFParam);

    virtual void visit(ParamArrayExpList *paramArrayExpList);

    virtual void visit(Block *block);

    virtual void visit(BlockItemList *blockItemList);

    virtual void visit(BlockItem *blockItem);

    virtual void visit(Stmt *stmt);

    virtual void visit(AssignStmt *assignStmt);

    virtual void visit(SelectStmt *selectStmt);

    virtual void visit(IterationStmt *iterationStmt);

    virtual void visit(BreakStmt *breakStmt);

    virtual void visit(ContinueStmt *continueStmt);

    virtual void visit(ReturnStmt *returnStmt);

    virtual void visit(Exp *exp);

    virtual void visit(Cond *cond);

    virtual void visit(LVal *lVal);

    virtual void visit(PrimaryExp *primaryExp);

    virtual void visit(Number *number);

    virtual void visit(UnaryExp *unaryExp);

    virtual void visit(FuncRParams *funcRParams);

    virtual void visit(MulExp *mulExp);

    virtual void visit(AddExp *addExp);

    virtual void visit(RelExp *relExp);

    virtual void visit(EqExp *eqExp);

    virtual void visit(LAndExp *lAndEXp);

    virtual void visit(LOrExp *lOrExp);

    virtual void visit(ConstExp *constExp);

    virtual void visit(UnaryOp *unaryOp);
};


#endif //SYSY2022_BJTU_IRVISITOR_HH
