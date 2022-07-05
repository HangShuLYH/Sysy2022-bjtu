//
// Created by hangshu on 22-7-4.
//

#ifndef SYSY2022_BJTU_CODEGEN_HH
#define SYSY2022_BJTU_CODEGEN_HH

#include <map>
#include "Value.hh"
#include "reg.hh"
#include "IrVisitor.hh"

class Codegen {
private:
    IrVisitor irVisitor;
    std::map<Value *, GR> gRegMapping;
    std::map<Value *, FR> fRegMapping;
public:
    Codegen(IrVisitor &irVisitor) : irVisitor(irVisitor) {}

    void regAlloc();

    void calLiveInfo(Function *function,
                     std::map<BasicBlock *, std::set<Value *>> &liveIn,
                     std::map<BasicBlock *, std::set<Value *>> &liveOut,
                     std::map<BasicBlock *, std::set<Value *>> &def,
                     std::map<BasicBlock *, std::set<Value *>> &use);

    void printLiveInfo(Function *function,
                       std::map<BasicBlock *, std::set<Value *>> &liveIn,
                       std::map<BasicBlock *, std::set<Value *>> &liveOut);

    void createIG(std::map<Value *, std::set<Value *>>& IG,
                  std::map<BasicBlock *, std::set<Value *>> &liveIn,
                  std::map<BasicBlock *, std::set<Value *>> &liveOut);
};

#endif //SYSY2022_BJTU_CODEGEN_HH
