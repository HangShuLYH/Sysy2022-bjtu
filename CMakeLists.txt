cmake_minimum_required(VERSION 3.16)
project(Sysy2022-bjtu)
include_directories(include)
include_directories(include/frontend)
include_directories(include/backend)
include_directories(include/errors)
include_directories(include/optimize)
add_subdirectory(src/frontend)
add_executable(
        compiler
        main.cpp include/frontend/Instruction.hh include/frontend/Function.hh include/frontend/BasicBlock.hh include/frontend/Value.hh include/frontend/CompileUnit.hh include/frontend/IrVisitor.hh include/errors/errors.hh include/frontend/IRManager.hh include/frontend/MIRBuilder.hh src/frontend/MIRBuilder.cc include/backend/codegen.hh src/backend/codegen.cc include/backend/reg.hh include/backend/instr.hh include/backend/allocRegs.hh src/backend/allocRegs.cc)
target_link_libraries(
        compiler
        driver
)