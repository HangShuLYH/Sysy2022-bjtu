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
    int bbCnt = 0;
    int varCnt = 0;
    std::string name;
    Type* return_type;
    std::vector<BasicBlock*> basicBlocks;
    std::vector<Value*> params;
    Function(std::string name,Type* type){
        this->name = name;
        return_type = type;
    }
    void pushBB(BasicBlock* basicBlock) {
        basicBlocks.push_back(basicBlock);
    }
    bool isArgs(std::string name) {
        for (size_t i = 0; i < params.size(); ++i) {
            if (params[i]->getName() == name) return true;
        }
        return false;
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
        return_type->print();
        std::cout << "@" << name << "(";
        for (size_t i = 0; i < params.size(); ++i) {
            params[i]->print();
            if (i != params.size() - 1){
                std::cout << ",";
            }
        }
        std::cout << ")" <<std::endl;
        for (size_t i = 0; i < basicBlocks.size(); ++i) {
            basicBlocks[i]->print();
        }
    }
};
#endif //SYSY2022_BJTU_FUNCTION_HH
