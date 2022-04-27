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
    std::vector<std::shared_ptr<BasicBlock>> basicBlocks;
    std::vector<std::shared_ptr<Value>> params;
    std::shared_ptr<BasicBlock> entry;
};
#endif //SYSY2022_BJTU_FUNCTION_HH
