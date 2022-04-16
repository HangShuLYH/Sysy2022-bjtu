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

class TreeNode{
public:
    virtual void visit(int depth) = 0;
    virtual ~TreeNode(){}
};
class CompUnit:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<DeclDef>> declDefList;
};
class DeclDef:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<ConstDecl> constDecl = nullptr;
    std::shared_ptr<VarDecl> varDecl = nullptr;
    std::shared_ptr<FuncDef> funcDef = nullptr;
};
class ConstDecl:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<DefType> defType = nullptr;
    std::vector<std::shared_ptr<ConstDef>> constDefList;
};
class BType:TreeNode{
public:
    void visit(int depth) final;
    type_specifier type;
};
class ConstDefList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<ConstDef>> constDefList;
};
class ConstDef:TreeNode{
public:
    void visit(int depth) final;
    std::string identifier;
    std::vector<std::shared_ptr<ConstExp>> constExpList;
    std::shared_ptr<ConstInitVal> constInitVal = nullptr;
};
class ConstExpList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<ConstExp>> constExpList;
};
class ConstInitVal:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<ConstExp> constExp = nullptr;
    std::vector<std::shared_ptr<ConstInitVal>> constInitValList;
};
class ConstInitValList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<ConstInitVal>> constInitValList;
};
class VarDecl:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<DefType> defType = nullptr;
    std::vector<std::shared_ptr<VarDef>> varDefList;
};
class VarDef:TreeNode{
public:
    void visit(int depth) final;
    std::string identifier;
    std::vector<std::shared_ptr<ConstExp>> constExpList;
    std::shared_ptr<InitVal> initVal = nullptr;
};
class VarDefList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<VarDef>> varDefList;
};
class InitVal:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<Exp> exp = nullptr;
    std::vector<std::shared_ptr<InitVal>> initValList;
};
class InitValList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<InitVal>> initValList;
};
class FuncDef:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<DefType> defType = nullptr;
    std::string identifier;
    std::shared_ptr<FuncFParams> funcFParams = nullptr;
    std::shared_ptr<Block> block = nullptr;
};
class DefType:TreeNode{
public:
    void visit(int depth) final;
    type_specifier type;
};
class FuncFParams:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<FuncFParam>> funcFParamList;
};
class FuncFParam:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<DefType> defType = nullptr;
    std::string identifier;
    std::vector<std::shared_ptr<Exp>> expList;
};
class ParamArrayExpList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<Exp>> expList;
};
class Block:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<BlockItem>> blockItemList;
};
class BlockItemList:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<BlockItem>> blockItemList;
};
class BlockItem:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<ConstDecl> constDecl = nullptr;
    std::shared_ptr<VarDecl> varDecl = nullptr;
    std::shared_ptr<Stmt> stmt = nullptr;
};
class Stmt:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<LVal> lVal = nullptr;
    std::shared_ptr<Exp> exp = nullptr;
    std::shared_ptr<Block> block = nullptr;
    std::shared_ptr<Cond> cond = nullptr;
    std::shared_ptr<Stmt> stmt1 = nullptr;
    std::shared_ptr<Stmt> stmt2 = nullptr;
    bool isSelect;
    bool isIteration;
    bool isBreak;
    bool isContinue;
    bool isReturn;
};
class Exp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<AddExp> addExp = nullptr;
};
class Cond:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<LOrExp> lOrExp = nullptr;
};
class LVal:TreeNode{
public:
    void visit(int depth) final;
    std::string identifier;
    std::vector<std::shared_ptr<Exp>> expList;
};
class PrimaryExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<Exp> exp = nullptr;
    std::shared_ptr<LVal> lVal = nullptr;
    std::shared_ptr<Number> number = nullptr;
};
class Number:TreeNode{
public:
    void visit(int depth) final;
    type_specifier type;
    int intNum;
    float floatNum;
};
class UnaryExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<PrimaryExp> primaryExp = nullptr;
    std::string identifier;
    std::shared_ptr<FuncRParams> funcRParams = nullptr;
    std::shared_ptr<UnaryOp> unaryOp = nullptr;
    std::shared_ptr<UnaryExp> unaryExp = nullptr;
};
class UnaryOp:TreeNode{
public:
    void visit(int depth) final;
    unaryop op;
};
class FuncRParams:TreeNode{
public:
    void visit(int depth) final;
    std::vector<std::shared_ptr<Exp>> expList;
};
class MulExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<UnaryExp> unaryExp = nullptr;
    std::shared_ptr<MulExp> mulExp = nullptr;
    mulop op;
};
class AddExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<MulExp> mulExp = nullptr;
    std::shared_ptr<AddExp> addExp = nullptr;
    addop op;
};
class RelExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<AddExp> addExp = nullptr;
    std::shared_ptr<RelExp> relExp = nullptr;
    relop op;
};
class EqExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<RelExp> relExp = nullptr;
    std::shared_ptr<EqExp> eqExp = nullptr;
    relop op;
};
class LAndExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<EqExp> eqExp = nullptr;
    std::shared_ptr<LAndExp> lAndExp = nullptr;
};
class LOrExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<LAndExp> lAndExp = nullptr;
    std::shared_ptr<LOrExp> lOrExp = nullptr;
};
class ConstExp:TreeNode{
public:
    void visit(int depth) final;
    std::shared_ptr<AddExp> addExp = nullptr;
};
#endif //SYSY2022_BJTU_SYNTAX_TREE_HH
