//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_INSTRUCTION_HH
#define SYSY2022_BJTU_INSTRUCTION_HH
#include <string>
#include <iostream>
#include "Value.hh"
enum class OP{
    ADDI,
    ADDF,
    SUBI,
    SUBF,
    MULI,
    MULF,
    DIVI,
    DIVF,
    MOD,
    POS,
    NEG,
    NOT,
    GOTO,
    ORI,
    ANDI,
    ORF,
    ANDF,
    CMPLTI,
    CMPGTI,
    CMPLEI,
    CMPGEI,
    CMPEQI,
    CMPNEI,
    CMPLTF,
    CMPGTF,
    CMPLEF,
    CMPGEF,
    CMPEQF,
    CMPNEF,
};
class Instruction{
public:
    virtual void print() = 0;
    virtual ~Instruction(){}
};
class AllocIIR:public Instruction{
public:
    Value* v;
    AllocIIR(Value* v){
        this->v = v;
    }
    void print() override final{
        v->print();
        std::cout << " = AllocaI" << std::endl;
    }
};
class AllocFIR:public Instruction{
public:
    Value* v;
    AllocFIR(Value* v){
        this->v = v;
    }
    void print() override final{
        v->print();
        std::cout << " = AllocaF" << std::endl;
    }
};
class LoadIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    LoadIIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print() override final{
        v1->print();
        std::cout << " = LoadI ";
        v2->print();
        std::cout << std::endl;
    }
};
class LoadFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    LoadFIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print() override final{
        v1->print();
        std::cout << " = LoadF ";
        v2->print();
        std::cout << std::endl;
    }
};
class StoreIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
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
    void print() override final{
        std::cout << "StoreI ";
        if (useConst) {
            std::cout << "int " << val << " ";
        }else {
            v2->print();
            std::cout << " ";
        }
        v1->print();
        std::cout << std::endl;
    }
};
class StoreFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
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
    void print() override final{
        std::cout << "StoreF ";
        if (useConst) {
            std::cout << "float " << val << " ";
        }else {
            v2->print();
            std::cout << " ";
        }
        v1->print();
        std::cout << std::endl;
    }
};
class CastInt2FloatIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastInt2FloatIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print() override final{
        v1->print();
        std::cout << " = CastInt2Float ";
        v2->print();
        std::cout << std::endl;
    }
};
class CastFloat2IntIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastFloat2IntIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print() override final{
        v1->print();
        std::cout << " = CastFloat2Int ";
        v2->print();
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

#endif //SYSY2022_BJTU_INSTRUCTION_HH
