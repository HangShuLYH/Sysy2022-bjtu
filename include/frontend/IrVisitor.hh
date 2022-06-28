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
#include "Lin.hh"
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include "Value.hh"
class IrVisitor : public Visitor {
public:
    TempVal tempVal;
    std::vector<Function*> functions;
    std::vector<Value*> globalVars;
    Function *cur_func = nullptr;
    BasicBlock *entry = nullptr;
    int cnt = 0;
    BasicBlock *cur_bb = nullptr;
    std::stack<BasicBlock *> condBB;
    bool isIF = false;
    Type* curDefType;
    std::vector<TempVal> args; //temp args for cur_func
    int loopCnt = 0; //use for breakError and ContinueError
    Type* typeInt = new Type(TypeID::INT);
    Type* typeFloat = new Type(TypeID::FLOAT);
    Type* typeVoid = new Type(TypeID::VOID);
    Function* call_func;
    bool useArgs = false;
    IrVisitor() {
        entry = new NormalBlock(nullptr,"entry",0);
        cur_bb = entry;
    }

    void addParam(Function* func,Value* v) {
        func->params.push_back(v);
    }
    void pushVars(Value* var){
        if (isGlobal()) {
            pushGlobalVars(var);
        }else {
            cur_bb->pushVar(var);
        }
    }
    void pushFunctions(Function* func){
        functions.push_back(func);
    }
    void pushGlobalVars(Value *var) {
        var->setGlobal(true);
        globalVars.push_back(var);
    }
    void print(std::ostream& out = std::cout) {
        out << "globalVars:" << std::endl;
        for (size_t i = 0; i < globalVars.size(); ++i) {
            out << "\t";
            globalVars[i]->print(out);
            out << std::endl;
        }
        out << ".entryBB:" << std::endl;
        entry->print(out);
        for (size_t i = 0; i < functions.size(); ++i) {
            functions[i]->print(out);
        }
    }
    //Created by lin 5.22
    void getRelated(){
        std::cout << "begin relative:" << std::endl;
        for (size_t i = 0; i < functions.size(); ++i) {
            if(functions[i]->return_type->isVoid()){
                if(typeid(*functions[i]->basicBlocks.back()) != typeid(NormalBlock)){    // solve problem of void
                    functions[i]->basicBlocks.
                        push_back(new NormalBlock(nullptr, functions[i]->name, functions[i]->bbCnt++));
                }
                functions[i]->basicBlocks.back()->ir.push_back(new ReturnIR(nullptr));
            }
            functions[i]->basicBlocks = relative(functions[i]->basicBlocks, NULL);
        }
        std::cout << "end relative." << std::endl;
    }

    std::vector<BasicBlock*> relative(std::vector<BasicBlock*> bbs, BasicBlock* nextAB){
        if(bbs.empty()){
            return bbs;
        }
        for(size_t i = 0; i < bbs.size(); i++){
            BasicBlock* nextBB;
            if(i+1<bbs.size()){
                nextBB = frontOfNextBB(bbs[i + 1]);
            }else{
                nextBB = nextAB;
            }

            if(typeid(*bbs[i]) == typeid(SelectBlock)){
                dynamic_cast<SelectBlock*>(bbs[i])->ifStmt = relative(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt, nextBB);
                dynamic_cast<SelectBlock*>(bbs[i])->elseStmt = relative(dynamic_cast<SelectBlock*>(bbs[i])->elseStmt, nextBB);

                BasicBlock* firstBB;
                if(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt.empty()){
                    firstBB = nextBB;
                } else{
                    firstBB = dynamic_cast<SelectBlock*>(bbs[i])->ifStmt.front();
                }

                dynamic_cast<SelectBlock*>(bbs[i])->cond = relatedCond(dynamic_cast<SelectBlock*>(bbs[i])->cond, firstBB, nextBB);
            } else if(typeid(*bbs[i]) == typeid(IterationBlock)){

                dynamic_cast<IterationBlock*>(bbs[i])->whileStmt =
                        relative(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt, dynamic_cast<IterationBlock*>(bbs[i])->cond.front());

                BasicBlock* firstBB;
                if(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt.empty()){
                    firstBB = dynamic_cast<IterationBlock*>(bbs[i])->cond.front();
                } else{
                    firstBB = frontOfNextBB(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt.front());
                }

                dynamic_cast<IterationBlock*>(bbs[i])->cond = relatedCond(dynamic_cast<IterationBlock*>(bbs[i])->cond, firstBB, nextBB);

                dynamic_cast<IterationBlock*>(bbs[i])->whileStmt =
                        relatedContinueBreak(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt,
                                             dynamic_cast<IterationBlock*>(bbs[i])->cond.front(), nextBB);
            } else{     //NormalBlock
                dynamic_cast<NormalBlock*>(bbs[i])->nextBB = nextBB;
                dynamic_cast<NormalBlock*>(bbs[i])->ir.push_back(new JumpIR(nextBB));
                ReturnOfRelated* ro = relatedIR(dynamic_cast<NormalBlock*>(bbs[i])->ir);
                if(ro->type == 3){
                    dynamic_cast<NormalBlock*>(bbs[i])->
                        ir.erase(std::begin(dynamic_cast<NormalBlock*>(bbs[i])->ir)+ro->index+1,
                                 std::end(dynamic_cast<NormalBlock*>(bbs[i])->ir));
                }
            }
        }
        return bbs;
    }

    inline std::vector<BasicBlock*> relatedCond(std::vector<BasicBlock*> bbs, BasicBlock* firstBB, BasicBlock* nextAB){
        BasicBlock* lastOrBB = nextAB;
        dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->trueBB = firstBB;
        dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->falseBB = nextAB;
        dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->
            ir.push_back(new BranchIR(firstBB, nextAB, dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->val));

        for(int i = bbs.size() - 2; i >= 0; --i){
            if(dynamic_cast<CondBlock*>(bbs[i])->isAnd){
                dynamic_cast<CondBlock*>(bbs[i])->trueBB = bbs[i+1];
                dynamic_cast<CondBlock*>(bbs[i])->falseBB = lastOrBB;
                dynamic_cast<CondBlock*>(bbs[i])->
                        ir.push_back(new BranchIR(bbs[i+1], lastOrBB, dynamic_cast<CondBlock*>(bbs[i])->val));
            } else{
                dynamic_cast<CondBlock*>(bbs[i])->trueBB = firstBB;
                dynamic_cast<CondBlock*>(bbs[i])->falseBB = bbs[i+1];
                dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->
                        ir.push_back(new BranchIR(firstBB, bbs[i+1], dynamic_cast<CondBlock*>(bbs[i])->val));
                if(i+1<bbs.size()){
                    lastOrBB = bbs[i+1];
                }
            }
        }
        return bbs;
    }

    inline std::vector<BasicBlock*> relatedContinueBreak(std::vector<BasicBlock*> bbs, BasicBlock* firstCond, BasicBlock* nextAB) {
        if(!bbs.empty()){
            for(size_t i = 0; i < bbs.size(); i++){
                if(typeid(*bbs[i]) == typeid(IterationBlock)){
                    continue;
                } else if(typeid(*bbs[i]) == typeid(SelectBlock)){
                    dynamic_cast<SelectBlock*>(bbs[i])->ifStmt =
                            relatedContinueBreak(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt, firstCond, nextAB);
                    dynamic_cast<SelectBlock*>(bbs[i])->elseStmt =
                            relatedContinueBreak(dynamic_cast<SelectBlock*>(bbs[i])->elseStmt, firstCond, nextAB);
                }else if(typeid(*bbs[i]) == typeid(NormalBlock)){
                    ReturnOfRelated* ro = relatedIR(dynamic_cast<NormalBlock*>(bbs[i])->ir);
                    switch (ro->type) {
                        case 1:
                            dynamic_cast<NormalBlock*>(bbs[i])->nextBB = nextAB;
                            dynamic_cast<NormalBlock*>(bbs[i])->
                                    ir.erase(std::begin(dynamic_cast<NormalBlock*>(bbs[i])->ir)+ro->index,
                                             std::end(dynamic_cast<NormalBlock*>(bbs[i])->ir)-1);
                            break;
                        case 2:
                            dynamic_cast<NormalBlock*>(bbs[i])->nextBB = firstCond;
                            dynamic_cast<NormalBlock*>(bbs[i])->
                                    ir.erase(std::begin(dynamic_cast<NormalBlock*>(bbs[i])->ir)+ro->index,
                                             std::end(dynamic_cast<NormalBlock*>(bbs[i])->ir)-1);
                            break;
                    }
                }
            }
        }
        return bbs;
    }

    inline ReturnOfRelated* relatedIR(std::vector<Instruction*> ir){
       for(size_t i = 0; i < ir.size(); i++){
            if(typeid(*ir[i]) == typeid(BreakIR)){
                return new ReturnOfRelated(1, i); //on behalf of break
            } else if(typeid(*ir[i]) == typeid(ContinueIR)){
                return new ReturnOfRelated(2, i); //on behalf of continue
            } else if(typeid(*ir[i]) == typeid(ReturnIR)){
                return new ReturnOfRelated(3, i);
            }
        }
        return new ReturnOfRelated(0, 0); //nothing
    }

    inline BasicBlock* frontOfNextBB(BasicBlock* bb){
        if(typeid(*bb) == typeid(SelectBlock)){
            return dynamic_cast<SelectBlock*>(bb)->cond.front();
        }else if(typeid(*bb) == typeid(IterationBlock)){
            return dynamic_cast<IterationBlock*>(bb)->cond.front();
        } else if(typeid(*bb) == typeid(NormalBlock)){
            return bb;
        }
        return bb;
    }

    //end by lin
    bool isGlobal() {
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
                if (bb->vars[i]->getName() == name) {
                    return bb->vars[i];
                }
            }
            bb = bb->parent;
        }
        for (size_t i = 0; i < globalVars.size(); ++i) {
            if (globalVars[i]->getName() == name) {
                return globalVars[i];
            }
        }
        return nullptr;
    }

    inline Function* findFunc(std::string name) {
        for (size_t i = 0; i < functions.size(); ++i) {
            if (functions[i]->name == name) return functions[i];
        }
        return nullptr;
    }

    inline void pushBB() {
        if (!condBB.empty()) {
            if (typeid(*condBB.top()) == typeid(SelectBlock)){
                if (isIF) {
                    dynamic_cast<SelectBlock*>(condBB.top())->ifStmt.push_back(cur_bb);
                }else {
                    dynamic_cast<SelectBlock*>(condBB.top())->elseStmt.push_back(cur_bb);
                }
            }else{
                dynamic_cast<IterationBlock*>(condBB.top())->whileStmt.push_back(cur_bb);
            }
        }else {
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
