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
    BasicBlock* last;
    std::vector<Value*> vars;
    BasicBlock(BasicBlock* parent,
               BasicBlock* last) {
        this->parent = parent;
        this->last = last;
    }
    inline void pushIr(Instruction* instruction) {
        ir.push_back(instruction);
    }
    inline void pushVar(Value *v) {
        vars.push_back(v);
    }
    virtual ~BasicBlock(){}
};
class NormalBlock:public BasicBlock{
public:
    NormalBlock(BasicBlock* parent,BasicBlock* last) : BasicBlock(parent,last){}
};
class SelectBlock:public BasicBlock{
public:
};
class IterationBlock:public BasicBlock{
public:
};
#endif //SYSY2022_BJTU_BASICBLOCK_HH
