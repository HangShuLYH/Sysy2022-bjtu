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
    int stackSize = 0;
    int bbCnt = 0;
    int varCnt = 0;
    std::string name;
    Type* return_type;
    std::vector<BasicBlock*> basicBlocks;
    std::vector<Value*> params;
    std::set<Value*> allocaVars;
    bool variant_params = false;
    Function(std::string name,Type* type){
        this->name = name;
        return_type = type;
    }
    Function(std::string name,Type* type,std::vector<Value*> params) {
        this->name = name;
        this->return_type = type;
        this->params = params;
    }
    void pushBB(BasicBlock* basicBlock) {
        basicBlocks.push_back(basicBlock);
    }
    std::vector<BasicBlock*> getBB() {
        return basicBlocks;
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
    inline void print(std::ostream& out) {
        out << "define ";
        return_type->print(out);
        out << "@" << name << "(";
        for (size_t i = 0; i < params.size(); ++i) {
            params[i]->print(out);
            if (i != params.size() - 1){
                out << ",";
            }
        }
        out << ")" <<std::endl;
        for (size_t i = 0; i < basicBlocks.size(); ++i) {
            basicBlocks[i]->print(out);
        }
    }
};
#endif //SYSY2022_BJTU_FUNCTION_HH