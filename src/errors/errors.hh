//
// Created by hangshu on 22-5-22.
//
#include <utility>
#include <stdexcept>
#ifndef SYSY2022_BJTU_ERRORS_HH
#define SYSY2022_BJTU_ERRORS_HH
class SyntexError : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};
class DuplicateDefinition : public SyntexError {
public:
    DuplicateDefinition(std::string name) : SyntexError("Duplicate Definition:" + name){}
};
#endif //SYSY2022_BJTU_ERRORS_HH
