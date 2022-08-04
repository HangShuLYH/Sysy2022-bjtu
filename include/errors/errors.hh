//
// Created by hangshu on 22-5-22.
//
#include <utility>
#include <stdexcept>
#ifndef SYSY2022_BJTU_ERRORS_HH
#define SYSY2022_BJTU_ERRORS_HH
class SyntaxError : public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};
class ValueTypeError : public SyntaxError{
public:
    ValueTypeError() : SyntaxError("void should be type of Value"){}
};
class ConstNotInitError : public SyntaxError{
public:
    ConstNotInitError() : SyntaxError("Const Value should be assigned when compiling"){}
};
class BreakError : public SyntaxError{
public:
    BreakError() : SyntaxError("Break Stmt should be in a loop"){}
};
class VoidFuncReturnValueUsedError: public SyntaxError{
public:
    VoidFuncReturnValueUsedError() :SyntaxError("void function should not return a non-void value"){}
};
class ReturnValueNotFoundError : public SyntaxError{
public:
    ReturnValueNotFoundError() : SyntaxError("non-void function should return a value"){}
};
class ContinueError : public SyntaxError{
public:
    ContinueError() : SyntaxError("Continue Stmt should be in a loop"){}
};
class MainNotFoundError : public SyntaxError{
public:
    MainNotFoundError() : SyntaxError("Main function Not Found"){}
};
class MainWithArgsError : public SyntaxError{
public:
    MainWithArgsError() : SyntaxError("Main function should has no args"){}
};
class MainReturnError : public SyntaxError{
public:
    MainReturnError() : SyntaxError("Main function should return int value"){}
};
class LValIsConstError : public SyntaxError{
public:
    LValIsConstError() : SyntaxError("LVal should be a variable"){}
};
class UndefinedVarError : public SyntaxError{
public:
    UndefinedVarError(std::string name) : SyntaxError("Undefined variable: " + name){}
};
class InvalidIndexOperatorError : public SyntaxError{
public:
    InvalidIndexOperatorError() : SyntaxError("operator[] on non-array"){}
};
class ArgsNumberNotMatchError : public SyntaxError{
public:
    ArgsNumberNotMatchError(std::string name) : SyntaxError("Args number not Match " + name){}
};
class ArgsTypeNotMatchError : public SyntaxError{
public:
    ArgsTypeNotMatchError(std::string name) : SyntaxError("Args type not Match in function " + name){}
};
#endif //SYSY2022_BJTU_ERRORS_HH
