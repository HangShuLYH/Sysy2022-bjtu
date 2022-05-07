//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_BASICBLOCK_HH
#define SYSY2022_BJTU_BASICBLOCK_HH
#include <string>
#include "Instruction.hh"
class Instruction;
class BasicBlock{
public:
    std::vector<Instruction*> ir;
    BasicBlock* parent;
    std::vector<Value*> vars;
    int cnt;
    BasicBlock(BasicBlock* parent,int cnt) {
        this->parent = parent;
        this->cnt = cnt;
    }
    void pushIr(Instruction* instruction) {
        ir.push_back(instruction);
    }
    void pushVar(Value *v) {
        vars.push_back(v);
    }
    virtual void print() = 0;
    virtual void clear() = 0;
    virtual ~BasicBlock(){}
};
class NormalBlock:public BasicBlock{
public:
    NormalBlock(BasicBlock* parent,int cnt) : BasicBlock(parent,cnt){}
    void print() override final{
        std::cout << "<label>" << cnt << std::endl;
        for (size_t i = 0; i < ir.size(); ++i) {
            std::cout << "\t";
            ir[i]->print();
        }
    };
    void clear() override final{}
};
class SelectBlock:public BasicBlock{
public:
    std::vector<BasicBlock*> cond;
    std::vector<BasicBlock*> ifStmt;
    std::vector<BasicBlock*> elseStmt;
    BasicBlock* next;
    SelectBlock(BasicBlock* parent,int cnt) : BasicBlock(parent,cnt){}
    void print() override final{};
    void clear() override final{
        auto iter = cond.begin();
        while (iter != cond.end()){
            if ((*iter)->ir.empty()) {
                iter = cond.erase(iter);
            }else {
                ++iter;
            }
        }
        iter = ifStmt.begin();
        while (iter != ifStmt.end()){
            if ((*iter)->ir.empty()) {
                iter = ifStmt.erase(iter);
            }else {
                ++iter;
            }
        }
        iter = elseStmt.begin();
        while (iter != elseStmt.end()){
            if ((*iter)->ir.empty()) {
                iter = elseStmt.erase(iter);
            }else {
                ++iter;
            }
        }
    }
};
class IterationBlock:public BasicBlock{
public:
    std::vector<BasicBlock*> cond;
    std::vector<BasicBlock*> whileStmt;
    IterationBlock(BasicBlock* parent,int cnt) : BasicBlock(parent,cnt){}
    void print() override final{

    }
    void clear() override final{
        auto iter = cond.begin();
        while (iter != cond.end()){
            if ((*iter)->ir.empty()) {
                iter = cond.erase(iter);
            }else {
                ++iter;
            }
        }
        iter = whileStmt.begin();
        while (iter != whileStmt.end()){
            if ((*iter)->ir.empty()) {
                iter = whileStmt.erase(iter);
            }else {
                ++iter;
            }
        }
    }
};
#endif //SYSY2022_BJTU_BASICBLOCK_HH
