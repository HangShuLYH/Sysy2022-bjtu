//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_BASICBLOCK_HH
#define SYSY2022_BJTU_BASICBLOCK_HH
#include <string>
#include "Instruction.hh"
class BasicBlock{
public:
    std::vector<Instruction*> ir;
    BasicBlock* parent;
    std::vector<Value*> vars;
    std::string name;
    BasicBlock(BasicBlock* parent,std::string func_name,int cnt) {
        this->parent = parent;
        name = func_name + "::BB" +  std::to_string(cnt);
    }
    void pushIr(Instruction* instruction) {
        ir.push_back(instruction);
    }
    void pushVar(Value *v) {
        vars.push_back(v);
    }
    virtual void print(std::ostream& out) = 0;
    virtual void clear() = 0;
    virtual ~BasicBlock(){}
};
class NormalBlock:public BasicBlock{
public:
    BasicBlock* nextBB = nullptr;
    NormalBlock(BasicBlock* parent,std::string func_name, int cnt) : BasicBlock(parent,func_name,cnt){}
    void print(std::ostream& out) override final{
        out << name << std::endl;
        for (size_t i = 0; i < ir.size(); ++i) {
            std::cout << "\t";
            ir[i]->print(out);
        }
    };
    void clear() override final{}
};
class CondBlock:public BasicBlock{
public:
    BasicBlock* trueBB = nullptr;
    BasicBlock* falseBB = nullptr;
    Value* val = nullptr;
    bool isAnd = false;
    CondBlock(BasicBlock* parent,std::string func_name,int cnt): BasicBlock(parent,func_name,cnt){}
    void print(std::ostream& out) override final{
        out << name << std::endl;
        for (size_t i = 0; i < ir.size(); ++i) {
            std::cout << "\t";
            ir[i]->print(out);
        }
    }
    void clear() override final{}
};
class SelectBlock:public BasicBlock{
public:
    std::vector<BasicBlock*> cond;
    std::vector<BasicBlock*> ifStmt;
    std::vector<BasicBlock*> elseStmt;

    SelectBlock(BasicBlock* parent,std::string func_name,int cnt) : BasicBlock(parent,func_name,cnt){}
    void print(std::ostream& out) override final{
        for (size_t i = 0; i < cond.size(); ++i) {
            cond[i]->print(out);
        }
        for (size_t i = 0; i < ifStmt.size(); ++i) {
            ifStmt[i]->print(out);
        }
        for (size_t i = 0; i < elseStmt.size(); ++i) {
            elseStmt[i]->print(out);
        }
    };
    void clear() override final{
        auto iter = cond.begin();
        while (iter != cond.end()){
            if ((*iter)->ir.empty() &&
                !dynamic_cast<CondBlock*>(*iter)->val) {
                iter = cond.erase(iter);
            }else {
                ++iter;
            }
        }

        iter = ifStmt.begin();
        while (iter != ifStmt.end()){
            if (typeid(**iter) == typeid(NormalBlock)){
                if ((*iter)->ir.empty()) {
                    iter = ifStmt.erase(iter);
                }else {
                    ++iter;
                }
            }else {
                (*iter)->clear();
                ++iter;
            }
        }
        iter = elseStmt.begin();
        while (iter != elseStmt.end()){
            if (typeid(**iter) == typeid(NormalBlock)){
                if ((*iter)->ir.empty()) {
                    iter = elseStmt.erase(iter);
                }else {
                    ++iter;
                }
            }else {
                (*iter)->clear();
                ++iter;
            }
        }
    }
};
class IterationBlock:public BasicBlock{
public:
    std::vector<BasicBlock*> cond;
    std::vector<BasicBlock*> whileStmt;

    IterationBlock(BasicBlock* parent,std::string func_name,int cnt) : BasicBlock(parent,func_name,cnt){}
    void print(std::ostream& out) override final{
        for (size_t i = 0; i < cond.size(); ++i) {
            cond[i]->print(out);
        }
        for (size_t i = 0; i < whileStmt.size(); ++i) {
            whileStmt[i]->print(out);
        }
    }
    void clear() override final{
        auto iter = cond.begin();
        while (iter != cond.end()){
            if ((*iter)->ir.empty() &&
            !dynamic_cast<CondBlock*>(*iter)->val) {
                iter = cond.erase(iter);
            }else {
                ++iter;
            }
        }
        iter = whileStmt.begin();
        while (iter != whileStmt.end()){
            if (typeid(**iter) == typeid(NormalBlock)){
                if ((*iter)->ir.empty()) {
                    iter = whileStmt.erase(iter);
                }else {
                    ++iter;
                }
            }else {
                (*iter)->clear();
                ++iter;
            }
        }
    }
};
#endif //SYSY2022_BJTU_BASICBLOCK_HH
