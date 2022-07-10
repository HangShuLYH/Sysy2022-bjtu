//
// Created by hangshu on 22-7-4.
//

#ifndef SYSY2022_BJTU_CODEGEN_HH
#define SYSY2022_BJTU_CODEGEN_HH

#include <map>
#include "Value.hh"
#include "reg.hh"
#include "IrVisitor.hh"
#include <string>
class Codegen {
private:
    IrVisitor irVisitor;
    std::map<Value *, GR> gRegMapping;
    std::map<Value *, FR> fRegMapping;
    std::map<Value*, int> stackMapping;
    int stackSize = 0;
    std::map<Value*, int> globalMapping;
    std::string asm_code;
    std::ostream& out;
    void translateFunction(Function* function);
    void generateGlobalCode();
    std::vector<Instr*> translateInstr(Instruction* ir);
    GR getGR(Value* src);
    FR getFR(Value* src);
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
    void comment(std::string s);
public:
    Codegen(IrVisitor &irVisitor, std::ostream& out) : irVisitor(irVisitor),out(out) {}
    void generateProgramCode();
};

#endif //SYSY2022_BJTU_CODEGEN_HH
