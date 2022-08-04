//
// Created by 6220302 on 2022-04-15.
//

#ifndef SYSY2022_BJTU_SYNTAX_TREE_HH
#define SYSY2022_BJTU_SYNTAX_TREE_HH

#include <vector>
#include <memory>
#include <iostream>

enum type_specifier{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_VOID,
};
enum relop{
    OP_LE,
    OP_LT,
    OP_GE,
    OP_GT,
    OP_EQU,
    OP_NE
};
enum addop{
    OP_ADD,
    OP_SUB
};
enum mulop{
    OP_MUL,
    OP_DIV,
    OP_MOD
};
enum unaryop{
    OP_POS,
    OP_NEG,
    OP_NOT
};
enum logop{
    OP_AND,
    OP_OR
};
class TreeNode;
class CompUnit;
class DeclDef;
class ConstDecl;
class ConstDef;
class ConstDefList;
class ConstExpList;
class ConstInitVal;
class ConstInitValList;
class VarDecl;
class VarDefList;
class VarDef;
class InitVal;
class InitValList;
class FuncDef;
class DefType;
class FuncFParams;
class FuncFParam;
class ParamArrayExpList;
class Block;
class BlockItemList;
class BlockItem;
class Stmt;
class AssignStmt;
class SelectStmt;
class IterationStmt;
class BreakStmt;
class ContinueStmt;
class ReturnStmt;
class Exp;
class Cond;
class LVal;
class PrimaryExp;
class Number;
class UnaryExp;
class UnaryOp;
class FuncRParams;
class MulExp;
class AddExp;
class RelExp;
class EqExp;
class LAndExp;
class LOrExp;
class ConstExp;
class Visitor{
public:
    virtual void visit(CompUnit* compUnit) = 0;
    virtual void visit(DeclDef* declDef) = 0;
    virtual void visit(ConstDecl* constDecl) = 0;
    virtual void visit(ConstDef* constDef) = 0;
    virtual void visit(ConstDefList* constDefList) = 0;
    virtual void visit(ConstExpList* constExpList) = 0;
    virtual void visit(ConstInitVal* constInitVal) = 0;
    virtual void visit(ConstInitValList* constInitValList) = 0;
    virtual void visit(VarDecl* varDecl) = 0;
    virtual void visit(VarDefList* varDefList) = 0;
    virtual void visit(VarDef* varDef) = 0;
    virtual void visit(InitVal* initVal) = 0;
    virtual void visit(InitValList* initValList) = 0;
    virtual void visit(FuncDef* funcDef) = 0;
    virtual void visit(DefType* defType) = 0;
    virtual void visit(FuncFParams* funcFParams) = 0;
    virtual void visit(FuncFParam* funcFParam) = 0;
    virtual void visit(ParamArrayExpList* paramArrayExpList) = 0;
    virtual void visit(Block* block) = 0;
    virtual void visit(BlockItemList* blockItemList) = 0;
    virtual void visit(BlockItem* blockItem) = 0;
    virtual void visit(Stmt* stmt) = 0;
    virtual void visit(AssignStmt* assignStmt) = 0;
    virtual void visit(SelectStmt* selectStmt) = 0;
    virtual void visit(IterationStmt* iterationStmt) = 0;
    virtual void visit(BreakStmt* breakStmt) = 0;
    virtual void visit(ContinueStmt* continueStmt) = 0;
    virtual void visit(ReturnStmt* returnStmt) = 0;
    virtual void visit(Exp* exp) = 0;
    virtual void visit(Cond* cond) = 0;
    virtual void visit(LVal* lVal) = 0;
    virtual void visit(PrimaryExp* primaryExp) = 0;
    virtual void visit(Number* number) = 0;
    virtual void visit(UnaryExp* unaryExp) = 0;
    virtual void visit(FuncRParams* funcRParams) = 0;
    virtual void visit(MulExp* mulExp) = 0;
    virtual void visit(AddExp* addExp) = 0;
    virtual void visit(RelExp* relExp) = 0;
    virtual void visit(EqExp* eqExp) = 0;
    virtual void visit(LAndExp* lAndEXp) = 0;
    virtual void visit(LOrExp* lOrExp) = 0;
    virtual void visit(ConstExp* constExp) = 0;
    virtual void visit(UnaryOp* unaryOp) = 0;
};

class TreeNode{
public:
    virtual void visit(int depth) = 0;
    virtual void accept(Visitor &visitor) = 0;
    virtual ~TreeNode(){}
};
class CompUnit:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<DeclDef>> declDefList;
};
class DeclDef:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<ConstDecl> constDecl = nullptr;
    std::shared_ptr<VarDecl> varDecl = nullptr;
    std::shared_ptr<FuncDef> funcDef = nullptr;
};
class ConstDecl:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<DefType> defType = nullptr;
    std::vector<std::shared_ptr<ConstDef>> constDefList;
};
class ConstDefList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<ConstDef>> constDefList;
};
class ConstDef:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::string identifier;
    std::vector<std::shared_ptr<ConstExp>> constExpList;
    std::shared_ptr<ConstInitVal> constInitVal = nullptr;
};
class ConstExpList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<ConstExp>> constExpList;
};
class ConstInitVal:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<ConstExp> constExp = nullptr;
    std::vector<std::shared_ptr<ConstInitVal>> constInitValList;
};
class ConstInitValList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<ConstInitVal>> constInitValList;
};
class VarDecl:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<DefType> defType = nullptr;
    std::vector<std::shared_ptr<VarDef>> varDefList;
};
class VarDef:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::string identifier;
    std::vector<std::shared_ptr<ConstExp>> constExpList;
    std::shared_ptr<InitVal> initVal = nullptr;
};
class VarDefList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<VarDef>> varDefList;
};
class InitVal:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<Exp> exp = nullptr;
    std::vector<std::shared_ptr<InitVal>> initValList;
};
class InitValList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<InitVal>> initValList;
};
class FuncDef:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<DefType> defType = nullptr;
    std::string identifier;
    std::shared_ptr<FuncFParams> funcFParams = nullptr;
    std::shared_ptr<Block> block = nullptr;
};
class DefType:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    type_specifier type;
};
class FuncFParams:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<FuncFParam>> funcFParamList;
};
class FuncFParam:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<DefType> defType = nullptr;
    std::string identifier;
    bool isArray;
    std::vector<std::shared_ptr<Exp>> expList;
};
class ParamArrayExpList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<Exp>> expList;
};
class Block:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<BlockItem>> blockItemList;
};
class BlockItemList:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<BlockItem>> blockItemList;
};
class BlockItem:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<ConstDecl> constDecl = nullptr;
    std::shared_ptr<VarDecl> varDecl = nullptr;
    std::shared_ptr<Stmt> stmt = nullptr;
};
class Stmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<Exp> exp = nullptr;
    std::shared_ptr<AssignStmt> assignStmt = nullptr;
    std::shared_ptr<Block> block = nullptr;
    std::shared_ptr<SelectStmt> selectStmt = nullptr;
    std::shared_ptr<IterationStmt> iterationStmt = nullptr;
    std::shared_ptr<BreakStmt> breakStmt = nullptr;
    std::shared_ptr<ContinueStmt> continueStmt = nullptr;
    std::shared_ptr<ReturnStmt> returnStmt = nullptr;
};
class AssignStmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<LVal> lVal;
    std::shared_ptr<Exp> exp;
};
class SelectStmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<Cond> cond = nullptr;
    std::shared_ptr<Stmt> ifStmt = nullptr;
    std::shared_ptr<Stmt> elseStmt = nullptr;
};
class IterationStmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<Cond> cond = nullptr;
    std::shared_ptr<Stmt> stmt = nullptr;
};
class BreakStmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
};
class ContinueStmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
};
class ReturnStmt:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<Exp> exp;
};
class Exp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<AddExp> addExp = nullptr;
};
class Cond:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<LOrExp> lOrExp = nullptr;
};
class LVal:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::string identifier;
    std::vector<std::shared_ptr<Exp>> expList;
};
class PrimaryExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<Exp> exp = nullptr;
    std::shared_ptr<LVal> lVal = nullptr;
    std::shared_ptr<Number> number = nullptr;
};
class Number:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    type_specifier type;
    int intNum;
    float floatNum;
};
class UnaryExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<PrimaryExp> primaryExp = nullptr;
    std::string identifier = "";
    std::shared_ptr<FuncRParams> funcRParams = nullptr;
    std::shared_ptr<UnaryOp> unaryOp = nullptr;
    std::shared_ptr<UnaryExp> unaryExp = nullptr;
    std::string stringConst = "";
};
class UnaryOp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    unaryop op;
};
class FuncRParams:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::vector<std::shared_ptr<Exp>> expList;
};
class MulExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<UnaryExp> unaryExp = nullptr;
    std::shared_ptr<MulExp> mulExp = nullptr;
    mulop op;
};
class AddExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<MulExp> mulExp = nullptr;
    std::shared_ptr<AddExp> addExp = nullptr;
    addop op;
};
class RelExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<AddExp> addExp = nullptr;
    std::shared_ptr<RelExp> relExp = nullptr;
    relop op;
};
class EqExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<RelExp> relExp = nullptr;
    std::shared_ptr<EqExp> eqExp = nullptr;
    relop op;
};
class LAndExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<EqExp> eqExp = nullptr;
    std::shared_ptr<LAndExp> lAndExp = nullptr;
};
class LOrExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<LAndExp> lAndExp = nullptr;
    std::shared_ptr<LOrExp> lOrExp = nullptr;
};
class ConstExp:TreeNode{
public:
    void visit(int depth) final;
    void accept(Visitor &visitor) override final;
    std::shared_ptr<AddExp> addExp = nullptr;
};
#endif //SYSY2022_BJTU_SYNTAX_TREE_HH
