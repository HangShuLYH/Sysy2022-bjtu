//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_COMPILEUNIT_HH
#define SYSY2022_BJTU_COMPILEUNIT_HH
#include <memory>
#include <vector>
#include "Instruction.hh"
#include "Function.hh"
class CompileUnit{
public:
    std::vector<std::shared_ptr<Value>> globalVars;
    std::vector<std::shared_ptr<Function>> functions;
};
#endif //SYSY2022_BJTU_COMPILEUNIT_HH
