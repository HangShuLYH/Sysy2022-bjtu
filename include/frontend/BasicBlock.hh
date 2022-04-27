//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_BASICBLOCK_HH
#define SYSY2022_BJTU_BASICBLOCK_HH
#include <string>
#include "Instruction.hh"
class BasicBlock{
public:
    std::string name;
    std::vector<std::shared_ptr<Instruction>> ir;
    BasicBlock(std::string name) {
        this->name = name;
    }
    inline void push(Instruction* instruction) {
        ir.push_back(std::shared_ptr<Instruction>(instruction));
    }
};
#endif //SYSY2022_BJTU_BASICBLOCK_HH
