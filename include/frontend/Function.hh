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
#include <iostream>
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
    inline void clear() {
        auto iter = basicBlocks.begin();
        while(iter != basicBlocks.end()) {
            if (typeid(**iter) == typeid(NormalBlock)){
                if ((*iter)->ir.empty()) {
                    iter = basicBlocks.erase(iter);
                }else {
                    ++iter;
                }
            }else {
                (*iter)->clear();
                ++iter;
            }
        }
    }
    inline void print() {
        std::cout << "define ";
        if (return_type == TYPE::INT) {
            std::cout << "int";
        }else if (return_type == TYPE::FLOAT){
            std::cout << "float";
        }else {
            std::cout << "float";
        }
        std::cout << "@" << name << "(";
        for (size_t i = 0; i < entry->vars.size(); ++i) {
            
        }
        for (size_t i = 0; i < basicBlocks.size(); ++i) {
            basicBlocks[i]->print();
        }
    }
};
#endif //SYSY2022_BJTU_FUNCTION_HH
