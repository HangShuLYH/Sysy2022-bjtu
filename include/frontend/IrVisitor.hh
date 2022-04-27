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
class IrVisitor:public Visitor{
public:
    std::vector<std::shared_ptr<Function>> functions;
    std::vector<std::shared_ptr<Value>> globalVars;
    std::vector<std::shared_ptr<Value>> vars;
    std::vector<std::shared_ptr<Value>> cur_val;
    std::shared_ptr<Function> cur_func;
    std::shared_ptr<BasicBlock> entry;
    std::shared_ptr<BasicBlock> cur_bb;
    TYPE curDefType;
    bool useConst;
    TYPE curValType;
    int tempInt;
    float tempFloat;

    std::string cur_name;
    int var_cnt;
    std::vector<int> tempIntList;
    std::vector<float> tempFloatList;
    Value* tempVal;
    IrVisitor() {
        entry = std::shared_ptr<BasicBlock>(new BasicBlock(".init"));
        cur_bb = entry;
        var_cnt = 0;
    }
    inline bool isGlobal() {
        return cur_bb->name == ".init";
    }
    virtual void visit(CompUnit* compUnit);
    virtual void visit(DeclDef* declDef);
    virtual void visit(ConstDecl* constDecl);
    virtual void visit(ConstDef* constDef);
    virtual void visit(ConstDefList* constDefList);
    virtual void visit(ConstExpList* constExpList);
    virtual void visit(ConstInitVal* constInitVal);
    virtual void visit(ConstInitValList* constInitValList);
    virtual void visit(VarDecl* varDecl);
    virtual void visit(VarDefList* varDefList);
    virtual void visit(VarDef* varDef);
    virtual void visit(InitVal* initVal);
    virtual void visit(InitValList* initValList);
    virtual void visit(FuncDef* funcDef);
    virtual void visit(DefType* defType);
    virtual void visit(FuncFParams* funcFParams);
    virtual void visit(FuncFParam* funcFParam);
    virtual void visit(ParamArrayExpList* paramArrayExpList);
    virtual void visit(Block* block) ;
    virtual void visit(BlockItemList* blockItemList);
    virtual void visit(BlockItem* blockItem);
    virtual void visit(Stmt* stmt);
    virtual void visit(AssignStmt* assignStmt);
    virtual void visit(SelectStmt* selectStmt);
    virtual void visit(IterationStmt* iterationStmt);
    virtual void visit(BreakStmt* breakStmt);
    virtual void visit(ContinueStmt* continueStmt);
    virtual void visit(ReturnStmt* returnStmt);
    virtual void visit(Exp* exp);
    virtual void visit(Cond* cond);
    virtual void visit(LVal* lVal);
    virtual void visit(PrimaryExp* primaryExp);
    virtual void visit(Number* number);
    virtual void visit(UnaryExp* unaryExp);
    virtual void visit(FuncRParams* funcRParams);
    virtual void visit(MulExp* mulExp);
    virtual void visit(AddExp* addExp);
    virtual void visit(RelExp* relExp);
    virtual void visit(EqExp* eqExp);
    virtual void visit(LAndExp* lAndEXp);
    virtual void visit(LOrExp* lOrExp);
    virtual void visit(ConstExp* constExp);
    virtual void visit(UnaryOp* unaryOp);
};


#endif //SYSY2022_BJTU_IRVISITOR_HH
