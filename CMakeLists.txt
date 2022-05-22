cmake_minimum_required(VERSION 3.17)
project(Sysy2022-bjtu)
include_directories(include)
include_directories(include/frontend)
add_subdirectory(src/frontend)
add_executable(
        compiler
        main.cpp include/frontend/Instruction.hh include/frontend/Function.hh include/frontend/BasicBlock.hh include/frontend/Value.hh include/frontend/CompileUnit.hh include/frontend/IrVisitor.hh src/errors/errors.hh include/errors/errors.hh)
target_link_libraries(
        compiler
        driver
)