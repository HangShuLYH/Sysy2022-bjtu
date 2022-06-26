//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_INSTRUCTION_HH
#define SYSY2022_BJTU_INSTRUCTION_HH
#include <string>
#include <iostream>
#include "Value.hh"
enum class OP{
    NEG,
    NOT,
};
class Instruction{
public:
    Instruction() {}
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
        std::cout << " = LoadI ";
        v2->print();
        std::cout << std::endl;
    }
};
class StoreIIR:public Instruction{
public:
    //storeI v2 v1
    Value* dst;
    TempVal src;
    StoreIIR(Value* dst,TempVal src):dst(dst),src(src){}
    void print() override final{
        std::cout << "StoreI ";
        src.print();
        std::cout << " ";
        dst->print();
        std::cout << std::endl;
    }
};
class StoreFIR:public Instruction{
public:
    //storeI v2 v1
    Value* dst;
    TempVal src;
    StoreFIR(Value* dst,TempVal src):dst(dst),src(src){}
    void print() override final{
        std::cout << "StoreF ";
        src.print();
        std::cout << " ";
        dst->print();
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
class ArithmeticIR:public Instruction{
public:
    TempVal res;
    TempVal left;
    TempVal right;
    ArithmeticIR(TempVal res,TempVal left,TempVal right) : res(res),left(left),right(right){}
    virtual void print() = 0;
    virtual ~ArithmeticIR(){}
};
class AddIIR:public ArithmeticIR{
public:
    AddIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = AddI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class AddFIR:public ArithmeticIR{
public:
    AddFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = AddF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};

class SubIIR:public ArithmeticIR{
public:
    SubIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = SubI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class SubFIR:public ArithmeticIR{
public:
    SubFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = SubF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class MulIIR:public ArithmeticIR{
public:
    MulIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = MulI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class MulFIR:public ArithmeticIR{
public:
    MulFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = MulF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class DivIIR:public ArithmeticIR{
public:
    DivIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = DivI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class DivFIR:public ArithmeticIR{
public:
    DivFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = DivF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class ModIR:public ArithmeticIR{
public:
    ModIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = Mod ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class UnaryIR:public Instruction{
public:
    TempVal res;
    TempVal v;
    OP op;
    UnaryIR(TempVal res,TempVal v,OP op): res(res), v(v), op(op){}
    void print() override final{
        res.print();
        std::cout << " = ";
        switch (op) {
            case OP::NEG:
                std::cout << "NEG ";break;
            case OP::NOT:
                std::cout << "NOT ";break;
        }
        v.print();
        std::cout << std::endl;
    }
};
class LTIIR:public ArithmeticIR{
public:
    LTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = LTI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class LTFIR:public ArithmeticIR{
public:
    LTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = LTF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class LEIIR:public ArithmeticIR{
public:
    LEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = LEI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class LEFIR:public ArithmeticIR{
public:
    LEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = LEF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class GTIIR:public ArithmeticIR{
public:
    GTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = GTI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class GTFIR:public ArithmeticIR{
public:
    GTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = GTF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class GEIIR:public ArithmeticIR{
public:
    GEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = GEI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class GEFIR:public ArithmeticIR{
public:
    GEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = GEF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class EQUIIR:public ArithmeticIR{
public:
    EQUIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = EQUI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class EQUFIR:public ArithmeticIR{
public:
    EQUFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = EQUF ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class NEIIR:public ArithmeticIR{
public:
    NEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = NEI ";
        left.print();
        std::cout << " ";
        right.print();
        std::cout << std::endl;
    }
};
class NEFIR:public ArithmeticIR{
public:
    NEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print() override final{
        res.print();
        std::cout << " = NEF ";
        left.print();
        std::cout << " ";
        right.print();
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
        std::cout << target->name;
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
        if(trueTarget) {
            std::cout << trueTarget->name;
        }
        std::cout << " : ";
        if(falseTarget) {
            std::cout << falseTarget->name;
        }
        std::cout << "\n";
    }
};
class GEPIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    Value* v3 = nullptr;
    int arrayLen;
    GEPIR(Value* v1,Value* v2, Value* v3){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }
    GEPIR(Value* v1,Value* v2,int arrayLen){
        this->v1 = v1;
        this->v2 = v2;
        this->arrayLen = arrayLen;
    }
    void print() override final{
        v1->print();
        std::cout << " = GEP ";
        v2->print();
        if(v3) {
            std::cout << " ";
            v3->print();
            std::cout << std::endl;
        }else {
            std::cout << " " << arrayLen << std::endl;
        }
    };
};
#include "Function.hh"
class CallIR:public Instruction{
public:
    Function* func;
    std::vector<TempVal> args;
    Value* returnVal = nullptr;
    CallIR(Function* func,std::vector<TempVal> args) {
        this->func = func;
        this->args = args;
    }
    CallIR(Function* func,std::vector<TempVal> args, Value* v){
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
            if(args[i].getVal()) {
                args[i].getVal()->print();
            }else {
                if(args[i].isInt()) {
                    std::cout << args[i].getInt();
                }else {
                    std::cout << args[i].getFloat();
                }
            }
            if (i < args.size() - 1) {
                std::cout << " , ";
            }else {
                std::cout << ")\n";
            }
        }
    }
};

#endif //SYSY2022_BJTU_INSTRUCTION_HH
