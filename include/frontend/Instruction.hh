//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_INSTRUCTION_HH
#define SYSY2022_BJTU_INSTRUCTION_HH
#include <string>
#include "Value.hh"
#include "BasicBlock.hh"
class BasicBlock;
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
    virtual ~Instruction(){}
};
class AllocIIR:public Instruction{
public:
    Value* v;
    AllocIIR(Value* v,BasicBlock* bb){
        this->v = v;
        bb->pushIr(this);
    }
};
class AllocFIR:public Instruction{
public:
    Value* v;
    AllocFIR(Value* v,BasicBlock* bb){
        this->v = v;
        bb->pushIr(this);
    }
};
class LoadIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    LoadIR(Value* v1,Value* v2,BasicBlock* bb){
        this->v1 = v1;
        this->v2 = v2;
        bb->pushIr(this);
    }
};
class StoreIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    bool useInt;
    int valInt;
    float valFloat;
    StoreIR(Value* v1,Value* v2,BasicBlock* bb){
        this->v1 = v1;
        this->v2 = v2;
        bb->pushIr(this);
    }
    StoreIR(Value* v1,int val,BasicBlock* bb){
        this->v1 = v1;
        useInt = true;
        valInt = val;
        bb->pushIr(this);
    }
    StoreIR(Value* v1,float val,BasicBlock* bb){
        this->v1 = v1;
        useInt = false;
        valFloat = val;
        bb->pushIr(this);
    }
};
class CastInt2FloatIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastInt2FloatIR(Value* v1,Value* v2,BasicBlock* bb){
        this->v1 = v1;
        this->v2 = v2;
        bb->pushIr(this);
    }
};
class CastFloat2IntIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastFloat2IntIR(Value* v1,Value* v2,BasicBlock* bb){
        this->v1 = v1;
        this->v2 = v2;
        bb->pushIr(this);
    }
};
class BinaryIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3;
    OP op;
    BinaryIR(Value* v1,Value* v2,Value* v3,OP op,BasicBlock* bb){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->op = op;
        bb->pushIr(this);
    }
};
class UnaryIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    OP op;
    UnaryIR(Value* v1,Value* v2,OP op,BasicBlock* bb){
        this->v1 = v1;
        this->v2 = v2;
        this->op = op;
        bb->pushIr(this);
    }
};

//class Instruction {
//public:
//    OP op;
//    Value* v1;
//    Value* v2;
//    Value* result;
//    bool isInit;
//    int initInt;
//    float initFloat;
//    BasicBlock* bb;
//    static Value* CreateAllocIIR(std::string str,bool isInit,bool isConst,int val,Instruction* ir) {
//        Value* t = new Value(str,TYPE::INT,isInit,isConst,val,0);
//        ir->isInit = isInit;
//        ir->initInt = val;
//        ir->op = OP::ALLOCI;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateAllocFIR(std::string str,bool isInit,bool isConst,float val,Instruction* ir){
//        Value* t = new Value(str,TYPE::FLOAT,isInit,isConst,0,val);
//        ir->isInit = isInit;
//        ir->initFloat = val;
//        ir->op = OP::ALLOCF;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateLoadIR(Value *v,Instruction* ir){
//        Value* t = new Value(v);
//        ir->op = OP::LOAD;
//        ir->v1 = v;
//        ir->result = t;
//        return t;
//    }
//    static void CreateStoreIR(Value* v1, Value* v2,Instruction* ir){
//        ir->isInit = false;
//        ir->op = OP::STORE;
//        ir->v1 = v2;
//        ir->result = v1;
//        return;
//    }
//    static void CreateStoreIR(Value* v1,int val,Instruction* ir){
//        ir->op = OP::STORE;
//        ir->isInit = true;
//        if (v1->type == TYPE::FLOAT) {
//            ir->initFloat = val;
//        }else if (v1->type == TYPE::INT) {
//            ir->initInt = val;
//        }
//        ir->result = v1;
//        return;
//    }
//    static void CreateStoreIR(Value* v1,float val,Instruction* ir){
//        ir->op = OP::STORE;
//        ir->isInit = true;
//        if (v1->type == TYPE::FLOAT) {
//            ir->initFloat = val;
//        }else if (v1->type == TYPE::INT) {
//            ir->initInt = val;
//        }
//        ir->result = v1;
//        return;
//    }
//    static Value* CreateCastInt2FloatIR(Value *v,Instruction* ir) {
//        Value* t = new Value(v);
//        t->type = TYPE::FLOAT;
//        ir->op = OP::CASTINT2FLOAT;
//        ir->v1 = v;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCastFloat2IntIR(Value *v,Instruction* ir){
//        Value* t = new Value(v);
//        t->type = TYPE::INT;
//        ir->op = OP::CASTFLOAT2INT;
//        ir->v1 = v;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateADDIIR(Value *v1,Value *v2,Instruction *ir) {
//        Value* t = new Value(v1);
//        ir->op = OP::ADDI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateADDFIR(Value *v1,Value *v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::ADDF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateSUBIIR(Value *v1,Value *v2,Instruction *ir) {
//        Value* t = new Value(v1);
//        ir->op = OP::SUBI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateSUBFIR(Value *v1,Value *v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::SUBF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateMULIIR(Value *v1,Value * v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::MULI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateMULFIR(Value *v1,Value *v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::MULF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateDIVIIR(Value *v1,Value * v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::DIVI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateDIVFIR(Value *v1,Value * v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::DIVF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateMODIR(Value *v1,Value * v2,Instruction* ir){
//        Value* t = new Value(v1);
//        ir->op = OP::MOD;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateUnaryPOSIR(Value* v,Instruction* ir){
//        Value* t = new Value(v);
//        ir->op = OP::POS;
//        ir->v1 = v;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateUnaryNEGIR(Value* v,Instruction* ir){
//        Value* t = new Value(v);
//        ir->op = OP::NEG;
//        ir->v1 = v;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateUnaryNOTIR(Value* v,Instruction* ir){
//        Value* t = new Value(v);
//        ir->op = OP::NOT;
//        ir->v1 = v;
//        ir->result = t;
//        return t;
//    }
//    static void CreateGotoIR(Instruction* ir,BasicBlock* bb) {
//        ir->op = OP::GOTO;
//        ir->bb = bb;
//    }
//    static Value* CreateOrIIR(Value* v1, Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::ORI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateOrFIR(Value* v1, Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::ORF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateAndIIR(Value* v1, Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::ANDI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateAndFIR(Value* v1, Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::ANDF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpLtIIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPLTI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpLtFIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPLTF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpGtIIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPGTI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpGtFIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPGTF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpLeIIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPLEI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpLeFIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPLEF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpGeIIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPGEI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpGeFIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPGEF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpEqIIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPEQI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpEqFIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPEQF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpNeIIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPNEI;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//    static Value* CreateCmpNeFIR(Value* v1,Value* v2, Instruction* ir){
//        Value* t = new Value(v1);
//        t->type = TYPE::INT;
//        ir->op = OP::CMPNEF;
//        ir->v1 = v1;
//        ir->v2 = v2;
//        ir->result = t;
//        return t;
//    }
//};
#endif //SYSY2022_BJTU_INSTRUCTION_HH
