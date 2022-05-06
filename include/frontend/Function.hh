//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_FUNCTION_HH
#define SYSY2022_BJTU_FUNCTION_HH
#include "string"
#include <vector>
#include <memory>
#include "BasicBlock.hh"
#include "Value.hh"
class Function{
public:
    std::string name;
    TYPE return_type;
    std::vector<BasicBlock*> basicBlocks;
    BasicBlock* entry;
    Function(std::string name,BasicBlock* entry,TYPE type){
        this->name = name;
        this->entry = entry;
        return_type = type;
    }
    void pushBB(BasicBlock* basicBlock) {
        basicBlocks.push_back(basicBlock);
    }
};
#endif //SYSY2022_BJTU_FUNCTION_HH
