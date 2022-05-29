//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_INSTRUCTION_HH
#define SYSY2022_BJTU_INSTRUCTION_HH
#include <string>
#include <iostream>
#include "Value.hh"
enum class OP{
    POS,
    NEG,
    NOT,
    LT,
    GT,
    LE,
    GE,
    EQU,
    NE
};
class Instruction{
public:
    virtual void print() = 0;
    virtual ~Instruction(){}
};
class AllocIIR:public Instruction{
public:
    bool isArray = false;
    int arrayLen;
    Value* v;
    AllocIIR(Value* v){
        this->v = v;
    }
    AllocIIR(Value* v, int arrayLen) {
        this->isArray = true;
        this->arrayLen = arrayLen;
        this->v = v;
    }
    void print() override final{
        v->print();
        std::cout << " = AllocaI";
        if(isArray)
            std::cout << "(" << arrayLen << ")";
        std::cout << std::endl;
    }
};
class AllocFIR:public Instruction{
public:
    bool isArray = false;
    int arrayLen;
    Value* v;
    AllocFIR(Value* v){
        this->v = v;
    }
    AllocFIR(Value* v, int arrayLen) {
        this->isArray = true;
        this->arrayLen = arrayLen;
        this->v = v;
    }
    void print() override final{
        v->print();
        std::cout << " = AllocaF";
        if(isArray)
            std::cout << "(" << arrayLen << ")";
        std::cout << std::endl;
    }
};
class LoadIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool v1_array = false;
    bool v2_array = false;
    int v1_index;
    int v2_index;
    LoadIIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    LoadIIR(Value* v1,Value* v2, int v1_index){
        this->v1_array = true;
        this->v1_index = v1_index;
        this->v1 = v1;
        this->v2 = v2;
    }
    LoadIIR(Value* v1,Value* v2, int v1_index, int v2_index){
        if(v1_index >= 0)
        {
            this->v1_array = true;
            this->v1_index = v1_index;
        }
        this->v2_array = true;
        this->v2_index = v2_index;
        this->v1 = v1;
        this->v2 = v2;
    }
    void print() override final{
        v1->print();
        if(v1_array)
            std::cout << "[" << v1_index << "]";
        std::cout << " = LoadI ";
        v2->print();
        if(v2_array)
            std::cout << "[" << v2_index << "]";
        std::cout << std::endl;
    }
};
class LoadFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool v1_array = false;
    bool v2_array = false;
    int v1_index;
    int v2_index;
    LoadFIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    LoadFIR(Value* v1,Value* v2, int v1_index){
        this->v1_array = true;
        this->v1_index = v1_index;
        this->v1 = v1;
        this->v2 = v2;
    }
    LoadFIR(Value* v1,Value* v2, int v1_index, int v2_index){
        if(v1_index >= 0)
        {
            this->v1_array = true;
            this->v1_index = v1_index;
        }
        this->v2_array = true;
        this->v2_index = v2_index;
        this->v1 = v1;
        this->v2 = v2;
    }
    void print() override final{
        v1->print();
        if(v1_array)
            std::cout << "[" << v1_index << "]";
        std::cout << " = LoadI ";
        v2->print();
        if(v2_array)
            std::cout << "[" << v2_index << "]";
        std::cout << std::endl;
    }
};
class StoreIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool v1_array = false;
    bool v2_array = false;
    int v1_index;
    int v2_index;
    bool useConst;
    int val;
    StoreIIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        useConst = false;
    }
    StoreIIR(Value* v1,int val){
        this->v1 = v1;
        this->val = val;
        useConst = true;
    }
    StoreIIR(Value* v1,Value* v2, int v1_index){
        this->v1_index = v1_index;
        this->v1_array = true;
        this->v1 = v1;
        this->v2 = v2;
        useConst = false;
    }
    StoreIIR(Value* v1,int val, int v1_index){
        this->v1_index = v1_index;
        this->v1_array = true;
        this->v1 = v1;
        this->val = val;
        useConst = true;
    }
    StoreIIR(Value* v1,Value* v2, int v1_index, int v2_index){
        if(v1_index >= 0)
        {
            this->v1_index = v1_index;
            this->v1_array = true;
        }
        this->v2_index = v2_index;
        this->v2_array = true;
        this->v1 = v1;
        this->v2 = v2;
        useConst = false;
    }
    void print() override final{
        std::cout << "StoreI ";
        if (useConst) {
            std::cout << "int " << val << " ";
        }else {
            v2->print();
            if(v2_array)
                std::cout << "[" << v2_index << "]";
            std::cout << " ";
        }
        v1->print();
        if(v1_array)
            std::cout << "[" << v1_index << "]";
        std::cout << std::endl;
    }
};
class StoreFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool v1_array = false;
    bool v2_array = false;
    int v1_index;
    int v2_index;
    bool useConst;
    float val;
    StoreFIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        useConst = false;
    }
    StoreFIR(Value* v1,float val){
        this->v1 = v1;
        this->val = val;
        useConst = true;
    }
    StoreFIR(Value* v1,Value* v2, int v1_index){
        this->v1_index = v1_index;
        this->v1_array = true;
        this->v1 = v1;
        this->v2 = v2;
        useConst = false;
    }
    StoreFIR(Value* v1,int val, int v1_index){
        this->v1_index = v1_index;
        this->v1_array = true;
        this->v1 = v1;
        this->val = val;
        useConst = true;
    }
    StoreFIR(Value* v1,Value* v2, int v1_index, int v2_index){
        if(v1_index >= 0)
        {
            this->v1_index = v1_index;
            this->v1_array = true;
        }
        this->v2_index = v2_index;
        this->v2_array = true;
        this->v1 = v1;
        this->v2 = v2;
        useConst = false;
    }
    void print() override final{
        std::cout << "StoreF ";
        if (useConst) {
            std::cout << "float " << val << " ";
        }else {
            v2->print();
            if(v2_array)
                std::cout << "[" << v2_index << "]";
            std::cout << " ";
        }
        v1->print();
        if(v1_array)
            std::cout << "[" << v1_index << "]";
        std::cout << std::endl;
    }
};
class CastInt2FloatIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool v2_array = false;
    int v2_index;
    CastInt2FloatIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    CastInt2FloatIR(Value* v1,Value* v2, int v2_index){
        this->v1 = v1;
        this->v2 = v2;
        this->v2_index = v2_index;
        this->v2_array = true;
    }
    void print() override final{
        v1->print();
        std::cout << " = CastInt2Float ";
        v2->print();
        if(v2_array)
            std::cout << "[" << v2_index << "]";
        std::cout << std::endl;
    }
};
class CastFloat2IntIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool v2_array = false;
    int v2_index;
    CastFloat2IntIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    CastFloat2IntIR(Value* v1,Value* v2, int v2_index){
        this->v1 = v1;
        this->v2 = v2;
        this->v2_index = v2_index;
        this->v2_array = true;
    }
    void print() override final{
        v1->print();
        std::cout << " = CastFloat2Int ";
        v2->print();
        if(v2_array)
            std::cout << "[" << v2_index << "]";
        std::cout << std::endl;
    }
};
class AddIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    AddIR(Value* v1,Value* v2,Value* v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    void print() override final{
        v1->print();
        std::cout << " = Add ";
        v2->print();
        std::cout << " ";
        v3->print();
        std::cout << std::endl;
    }
};
class AddIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    int val;
    AddIIR(Value* v1,Value* v2,int val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    AddIIR(Value* v1,int val,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = AddI ";
        v2->print();
        std::cout << " int " << val;
        std::cout << std::endl;
    }
};
class AddFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    float val;
    AddFIR(Value* v1,Value* v2,float val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    AddFIR(Value* v1,float val,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = AddF ";
        v2->print();
        std::cout << " float " << val;
        std::cout << std::endl;
    }
};
class SubIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    SubIR(Value* v1,Value* v2,Value* v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    void print() override final{
        v1->print();
        std::cout << " = Sub ";
        v2->print();
        std::cout << " ";
        v3->print();
        std::cout << std::endl;
    }
};
class SubIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    int val;
    bool constFirst = false;
    SubIIR(Value* v1,Value* v2,int val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    SubIIR(Value* v1,int val,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
        constFirst = true;
    }
    void print() override final{
        v1->print();
        std::cout << " = SubI ";
        if (!constFirst) {
            v2->print();
            std::cout << " int " << val;
            std::cout << std::endl;
        }else {
            std::cout << " int "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class SubFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    float val;
    bool constFirst = false;
    SubFIR(Value* v1,Value* v2,float val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    SubFIR(Value* v1,float val,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
        constFirst = true;
    }
    void print() override final{
        v1->print();
        std::cout << " = SubF ";
        if (!constFirst) {
            v2->print();
            std::cout << " float " << val;
            std::cout << std::endl;
        }else {
            std::cout << " float "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class MulIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    MulIR(Value* v1,Value* v2,Value* v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    void print() override final{
        v1->print();
        std::cout << " = Mul ";
        v2->print();
        std::cout << " ";
        v3->print();
        std::cout << std::endl;
    }
};
class MulIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    int val;
    MulIIR(Value* v1,Value* v2,int val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    MulIIR(Value* v1,int val,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = MulI ";
        v2->print();
        std::cout << " int " << val;
        std::cout << std::endl;
    }
};
class MulFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    float val;
    MulFIR(Value* v1,Value* v2,float val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    MulFIR(Value* v1,float val,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = MulF ";
        v2->print();
        std::cout << " float " << val;
        std::cout << std::endl;
    }
};
class DivIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    DivIR(Value* v1,Value* v2,Value* v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    void print() override final{
        v1->print();
        std::cout << " = Div ";
        v2->print();
        std::cout << " ";
        v3->print();
        std::cout << std::endl;
    }
};
class DivIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    int val;
    bool constFirst = false;
    DivIIR(Value* v1,Value* v2,int val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    DivIIR(Value* v1,int val,Value* v2){
        constFirst = true;
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = DivI ";
        if (!constFirst) {
            v2->print();
            std::cout << " int " << val;
            std::cout << std::endl;
        }else {
            std::cout << " int "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class DivFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    float val;
    bool constFirst = false;
    DivFIR(Value* v1,Value* v2,float val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    DivFIR(Value* v1,float val,Value* v2){
        constFirst = true;
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = DivF ";
        if (!constFirst) {
            v2->print();
            std::cout << " float " << val;
            std::cout << std::endl;
        }else {
            std::cout << " float "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class ModIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    ModIR(Value* v1,Value* v2,Value* v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    void print() override final{
        v1->print();
        std::cout << " = Mod ";
        v2->print();
        std::cout << " ";
        v3->print();
        std::cout << std::endl;
    }
};
class ModIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    int val;
    bool constFirst = false;
    ModIIR(Value* v1,Value* v2,int val){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    ModIIR(Value* v1,int val,Value* v2){
        constFirst = true;
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
    }
    void print() override final{
        v1->print();
        std::cout << " = ModI ";
        if (!constFirst) {
            v2->print();
            std::cout << " int " << val;
            std::cout << std::endl;
        }else {
            std::cout << " int "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class UnaryIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    OP op;
    UnaryIR(Value* v1,Value* v2,OP op){
        this->v1 = v1;
        this->v2 = v2;
        this->op = op;
    }
    void print() override final{
        v1->print();
        std::cout << " = ";
        switch (op) {
            case OP::POS:
                std::cout << "POS ";break;
            case OP::NEG:
                std::cout << "NEG ";break;
            case OP::NOT:
                std::cout << "NOT ";break;
        }
        v2->print();
        std::cout << std::endl;
    }
};
class RelIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    OP op;
    int val;
    bool constFirst = false;
    RelIIR(Value* v1,Value* v2,int val,OP op){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
        this->op = op;
    }
    RelIIR(Value* v1,int val,Value* v2,OP op){
        constFirst = true;
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
        this->op = op;
    }
    void print() override final{
        v1->print();
        switch (op) {
            case OP::LT:
                std::cout << " = LT ";
                break;
            case OP::GT:
                std::cout << " = GT ";
                break;
            case OP::LE:
                std::cout << " = LE ";
                break;
            case OP::GE:
                std::cout << " = GE ";
                break;
        }
        if (!constFirst) {
            v2->print();
            std::cout << " int " << val;
            std::cout << std::endl;
        }else {
            std::cout << " int "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class RelFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    OP op;
    float val;
    bool constFirst = false;
    RelFIR(Value* v1,Value* v2,float val,OP op){
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
        this->op = op;
    }
    RelFIR(Value* v1,float val,Value* v2,OP op){
        constFirst = true;
        this->v1 = v1;
        this->v2 = v2;
        this->val = val;
        this->op = op;
    }
    void print() override final{
        v1->print();
        switch (op) {
            case OP::LT:
                std::cout << " = LT ";
                break;
            case OP::GT:
                std::cout << " = GT ";
                break;
            case OP::LE:
                std::cout << " = LE ";
                break;
            case OP::GE:
                std::cout << " = GE ";
                break;
        }
        if (!constFirst) {
            v2->print();
            std::cout << " float " << val;
            std::cout << std::endl;
        }else {
            std::cout << " float "<<val;
            v2->print();
            std::cout << std::endl;
        }
    }
};
class RelIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    OP op;
    RelIR(Value* v1,Value* v2,Value* v3,OP op){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->op = op;
    }
    void print() override final{
        v1->print();
        switch (op) {
            case OP::LT:
                std::cout << " = LT ";
                break;
            case OP::GT:
                std::cout << " = GT ";
                break;
            case OP::LE:
                std::cout << " = LE ";
                break;
            case OP::GE:
                std::cout << " = GE ";
                break;
        }
        v2->print();
        std::cout << " ";
        v3->print();
        std::cout << std::endl;
    }
};
class BreakIR:public Instruction{
public:
    BreakIR(){};
    void print() override final{
        std::cout << "break" << std::endl;
    }
};
class ContinueIR:public Instruction{
public:
    ContinueIR(){};
    void print() override final{
        std::cout << "continue" << std::endl;
    }
};
class ReturnIR:public Instruction{
public:
    Value* v = nullptr;
    int retInt;
    float retFloat;
    bool useInt = false;
    bool useFloat = false;
    ReturnIR(Value* v){
        this->v = v;
    }
    ReturnIR(int val) {
        retInt = val;
        useInt = true;
    }
    ReturnIR(float val){
        retFloat = val;
        useFloat = true;
    }
    void print() override final{
        std::cout << "ret ";
        if (v) {
            v->print();
        }else if (useInt) {
            std::cout << "int " << retInt;
        }else if (useFloat){
            std::cout << "float " << retFloat;
        }
        std::cout << "\n";
    }
};
#include "BasicBlock.hh"
class JumpIR:public Instruction{
public:
    BasicBlock* target;
    JumpIR(BasicBlock* target) : target(target){}
    void print() override final{
        std::cout << "goto ";
        std::cout<<target->name;
        std::cout << "\n";
    }
};
class BranchIR:public Instruction{
public:
    BasicBlock* trueTarget;
    BasicBlock* falseTarget;
    Value* cond;
    BranchIR(BasicBlock* trueTarget,BasicBlock* falseTarget,Value* cond) :
    trueTarget(trueTarget),falseTarget(falseTarget),cond(cond) {}
    void print() override final{
        std::cout << "goto ";
        cond->print();
        std::cout << " ？ ";
        std::cout<<trueTarget->name;
        std::cout << " : ";
        std::cout<<falseTarget->name;
        std::cout << "\n";
    }
};
class GEPIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    int arrayLen;
    GEPIR(Value* v1,Value* v2,int arrayLen){
        this->v1 = v1;
        this->v2 = v2;
        this->arrayLen = arrayLen;
    }
    void print() override final{
        v1->print();
        std::cout << " = GEP ";
        v2->print();
        std::cout << " " << arrayLen << std::endl;
    };
};
#include "Function.hh"
class CallIR:public Instruction{
public:
    Function* func;
    std::vector<Value*> args;
    Value* returnVal = nullptr;
    CallIR(Function* func,std::vector<Value*> args) {
        this->func = func;
        this->args = args;
    }
    CallIR(Function* func,std::vector<Value*> args, Value* v){
        this->func = func;
        this->args = args;
        this->returnVal = v;
    }
    void print() override final{
        if (returnVal) {
            returnVal->print();
            std::cout << " = ";
        }
        std::cout << "call " << func->name << "(";
        for (size_t i = 0; i < args.size(); ++i) {
            args[i]->print();
            if (i < args.size() - 1) {
                std::cout << " , ";
            }else {
                std::cout << ")\n";
            }
        }
    }
};

#endif //SYSY2022_BJTU_INSTRUCTION_HH
