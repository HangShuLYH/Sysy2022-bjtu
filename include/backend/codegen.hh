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
const std::set<GR> caller_save_regs = {GR(0),GR(1),GR(2),GR(3),GR(12),GR(14)};
const std::set<GR> callee_save_regs = {GR(4),GR(5),GR(6),GR(7),GR(8),GR(9),GR(10),GR(11)};
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
    int translateFunction(Function* function);
    void generateGlobalCode();
    std::vector<Instr*> translateInstr(Instruction* ir);
    GR getGR(Value* src);
    FR getFR(Value* src);
    void comment(std::string s);
public:
    Codegen(IrVisitor &irVisitor, std::ostream& out) : irVisitor(irVisitor),out(out) {}
    void generateProgramCode();
};

#endif //SYSY2022_BJTU_CODEGEN_HH