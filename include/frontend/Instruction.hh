//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_INSTRUCTION_HH
#define SYSY2022_BJTU_INSTRUCTION_HH
#include <string>
#include "Value.hh"
enum class OP{
    ALLOCI,
    ALLOCF,
    LOAD,
    CASTINT2FLOAT,
    CASTFLOAT2INT,
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
};
class Instruction {
public:
    OP op;
    Value* v1;
    Value* v2;
    Value* result;
    bool isInit;
    int initInt;
    float initFloat;
    static Value* CreateAllocIIR(std::string str,bool isInit,int val,Instruction* ir) {
        Value* t = new Value(str,TYPE::INT);
        ir->isInit = isInit;
        ir->initInt = val;
        ir->op = OP::ALLOCI;
        ir->result = t;
        return t;
    }
    static Value* CreateAllocFIR(std::string str,bool isInit,float val,Instruction* ir){
        Value* t = new Value(str,TYPE::FLOAT);
        ir->isInit = isInit;
        ir->initFloat = val;
        ir->op = OP::ALLOCF;
        ir->result = t;
        return t;
    }
    static Value* CreateLoadIR(Value *v1,Value *v2,Instruction* ir){
        ir->op = OP::LOAD;
        ir->v1 = v2;
        ir->result = v1;
        return v1;
    }
    static Value* CreateCastInt2FloatIR(Value *v,Instruction* ir) {
        Value* t = new Value(v);
        t->type = TYPE::FLOAT;
        ir->op = OP::CASTINT2FLOAT;
        ir->v1 = v;
        ir->result = t;
        return t;
    }
    static Value* CreateCastFloat2IntIR(Value *v,Instruction* ir){
        Value* t = new Value(v);
        t->type = TYPE::INT;
        ir->op = OP::CASTFLOAT2INT;
        ir->v1 = v;
        ir->result = t;
        return t;
    }
    static Value* CreateADDIIR(Value *v1,Value *v2,Instruction *ir) {
        Value* t = new Value(v1);
        ir->op = OP::ADDI;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateADDFIR(Value *v1,Value *v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::ADDF;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateSUBIIR(Value *v1,Value *v2,Instruction *ir) {
        Value* t = new Value(v1);
        ir->op = OP::SUBI;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateSUBFIR(Value *v1,Value *v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::SUBF;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateMULIIR(Value *v1,Value * v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::MULI;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateMULFIR(Value *v1,Value *v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::MULF;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateDIVIIR(Value *v1,Value * v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::DIVI;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateDIVFIR(Value *v1,Value * v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::DIVF;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateMODIR(Value *v1,Value * v2,Instruction* ir){
        Value* t = new Value(v1);
        ir->op = OP::MOD;
        ir->v1 = v1;
        ir->v2 = v2;
        ir->result = t;
        return t;
    }
    static Value* CreateUnaryPOSIR(Value* v,Instruction* ir){
        Value* t = new Value(v);
        ir->op = OP::POS;
        ir->v1 = v;
        ir->result = t;
        return t;
    }
    static Value* CreateUnaryNEGIR(Value* v,Instruction* ir){
        Value* t = new Value(v);
        ir->op = OP::NEG;
        ir->v1 = v;
        ir->result = t;
        return t;
    }
    static Value* CreateUnaryNOTIR(Value* v,Instruction* ir){
        Value* t = new Value(v);
        ir->op = OP::NOT;
        ir->v1 = v;
        ir->result = t;
        return t;
    }
};
#endif //SYSY2022_BJTU_INSTRUCTION_HH
