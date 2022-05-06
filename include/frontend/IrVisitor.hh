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
    std::vector<Function*> functions;
    std::vector<Value*> cur_val;
    Function* cur_func;
    BasicBlock* entry = nullptr;
    BasicBlock* cur_bb = nullptr;
    BasicBlock* cur_cond = nullptr;
    TYPE curDefType;
    bool useConst;
    TYPE curValType;
    int tempInt;
    float tempFloat;
    bool tempTrue;
    std::vector<int> tempIntList;
    std::vector<float> tempFloatList;
    Value* tempVal;
    IrVisitor() {
        entry = new BasicBlock(nullptr, nullptr);
        cur_bb = entry;
    }
    inline bool isGlobal() {
        if (!cur_bb->parent){
            return true;
        }
        return false;
    }
    inline Value*
    findAllVal(std::string name) {
        BasicBlock* bb = cur_bb;
        while(bb) {
            for (size_t i = 0; i < bb->vars.size(); ++i) {
                if (bb->vars[i]->name == name) {
                    return bb->vars[i];
                }
            }
            bb = bb->parent;
        }
        return nullptr;
    }
    inline bool findLocalVal(std::string name) {
        BasicBlock* bb = cur_bb;
        while(bb) {
            for (size_t i = 0; i < bb->vars.size(); ++i) {
                if(bb->vars[i]->name == name) {
                    return true;
                }
            }
            bb = bb->last;
        }
        return false;
    }
    inline bool findFunc(std::string name) {
        for (size_t i = 0; i < functions.size(); ++i) {
            if (functions[i]->name == name) return true;
        }
        return false;
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
