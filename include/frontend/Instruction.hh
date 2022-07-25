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

class Instruction : public User{
public:
    Instruction() {}
    virtual void print(std::ostream& out) = 0;
    virtual ~Instruction() {}
};

class AllocIIR:public Instruction{
public:
    // bool isArray = false;
    int arrayLen;
    Value* v;
    AllocIIR(Value* v){
        this->v = v;

        Use* use = new Use(v, this, 0);
        v->addUse(use);
        this->Operands.push_back(use);
    }
    AllocIIR(Value* v, int arrayLen) {
        this->isArray = true;
        this->arrayLen = arrayLen;
        this->v = v;

        Use* use = new Use(v, this, 0);
        v->addUse(use);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = AllocaI";
        if(isArray)
            out << "(" << arrayLen << ")";
        out << std::endl;
    }
};
class AllocFIR:public Instruction{
public:
    // bool isArray = false;
    int arrayLen;
    Value* v;
    AllocFIR(Value* v){
        this->v = v;

        Use* use = new Use(v, this, 0);
        v->addUse(use);
        this->Operands.push_back(use);
    }
    AllocFIR(Value* v, int arrayLen) {
        this->isArray = true;
        this->arrayLen = arrayLen;
        this->v = v;

        Use* use = new Use(v, this, 0);
        v->addUse(use);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = AllocaF";
        if(isArray)
            out << "(" << arrayLen << ")";
        out << std::endl;
    }
};

class LoadIIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    LoadIIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;

        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        v1->addUse(use1);
        v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = LoadI ";
        Operands[1]->getVal()->print(out);
        out << std::endl;
    }
};
class LoadFIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    LoadFIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        v1->addUse(use1);
        v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = LoadI ";
        Operands[1]->getVal()->print(out);
        out << std::endl;
    }
};
class StoreIIR:public Instruction{
public:
    //storeI v2 v1
    Value* dst;
    TempVal src;
    StoreIIR(Value* dst,TempVal src):dst(dst),src(src){
        if (!src.getVal() && src.isFloat()) {
            this->src.setType(dst->getType()->getContained());
            this->src.setInt(src.getFloat());
        }

        Use* use1 = new Use(dst, this, 0);
        Use* use2 = new Use(&this->src, this, 1);
        dst->addUse(use1);
        this->src.addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        out << "StoreI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        Operands[0]->getVal()->print(out);
        out << std::endl;
    }
};
class StoreFIR:public Instruction{
public:
    //storeI v2 v1
    Value* dst;
    TempVal src;
    StoreFIR(Value* dst,TempVal src):dst(dst),src(src){
        if (!src.getVal() && src.isInt()) {
            src.setType(dst->getType()->getContained());
            src.setFloat(src.getFloat());
        }
        Use* use1 = new Use(dst, this, 0);
        Use* use2 = new Use(&this->src, this, 1);
        dst->addUse(use1);
        this->src.addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        out << "StoreF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        Operands[0]->getVal()->print(out);
        out << std::endl;
    }
};
class CastInt2FloatIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastInt2FloatIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        v1->addUse(use1);
        v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = CastInt2Float ";
        Operands[1]->getVal()->print(out);
        out << std::endl;
    }
};
class CastFloat2IntIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastFloat2IntIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        v1->addUse(use1);
        v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = CastFloat2Int ";
        Operands[1]->getVal()->print(out);
        out << std::endl;
    }
};
class ArithmeticIR:public Instruction{
public:
    TempVal res;
    TempVal left;
    TempVal right;
    ArithmeticIR(TempVal res,TempVal left,TempVal right) : res(res),left(left),right(right) {
        Use* use1 = new Use(&this->res, this, 0);
        Use* use2 = new Use(&this->left, this, 1);
        Use* use3 = new Use(&this->right, this, 2);
        this->res.addUse(use1);
        this->left.addUse(use2);
        this->right.addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
        this->Operands.push_back(use3);
    }
    virtual void print(std::ostream& out) = 0;
    virtual ~ArithmeticIR(){}
};
class AddIIR:public ArithmeticIR{
public:
    AddIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = AddI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class AddFIR:public ArithmeticIR{
public:
    AddFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = AddF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};

class SubIIR:public ArithmeticIR{
public:
    SubIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = SubI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class SubFIR:public ArithmeticIR{
public:
    SubFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = SubF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class MulIIR:public ArithmeticIR{
public:
    MulIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = MulI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class MulFIR:public ArithmeticIR{
public:
    MulFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = MulF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class DivIIR:public ArithmeticIR{
public:
    DivIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = DivI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class DivFIR:public ArithmeticIR{
public:
    DivFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = DivF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class ModIR:public ArithmeticIR{
public:
    ModIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = Mod ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class UnaryIR:public Instruction{
public:
    TempVal res;
    TempVal v;
    OP op;
    UnaryIR(TempVal res,TempVal v,OP op): res(res), v(v), op(op) {
        Use* use1 = new Use(&this->res, this, 0);
        Use* use2 = new Use(&this->v, this, 1);
        this->res.addUse(use1);
        this->v.addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = ";
        switch (op) {
            case OP::NEG:
                out << "NEG ";break;
            case OP::NOT:
                out << "NOT ";break;
        }
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << std::endl;
    }
};
class LTIIR:public ArithmeticIR{
public:
    LTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = LTI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class LTFIR:public ArithmeticIR{
public:
    LTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = LTF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class LEIIR:public ArithmeticIR{
public:
    LEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = LEI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class LEFIR:public ArithmeticIR{
public:
    LEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = LEF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class GTIIR:public ArithmeticIR{
public:
    GTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = GTI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class GTFIR:public ArithmeticIR{
public:
    GTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = GTF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class GEIIR:public ArithmeticIR{
public:
    GEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = GEI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class GEFIR:public ArithmeticIR{
public:
    GEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = GEF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class EQUIIR:public ArithmeticIR{
public:
    EQUIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = EQUI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class EQUFIR:public ArithmeticIR{
public:
    EQUFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = EQUF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class NEIIR:public ArithmeticIR{
public:
    NEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = NEI ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class NEFIR:public ArithmeticIR{
public:
    NEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        dynamic_cast<TempVal*>(Operands[0]->getVal())->print(out);
        out << " = NEF ";
        dynamic_cast<TempVal*>(Operands[1]->getVal())->print(out);
        out << " ";
        dynamic_cast<TempVal*>(Operands[2]->getVal())->print(out);
        out << std::endl;
    }
};
class BreakIR:public Instruction{
public:
    BreakIR(){};
    void print(std::ostream& out) override final{
        out << "break" << std::endl;
    }
};
class ContinueIR:public Instruction{
public:
    ContinueIR(){};
    void print(std::ostream& out) override final{
        out << "continue" << std::endl;
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

        Use* use = new Use(v, this, 0);
        v->addUse(use);
        this->Operands.push_back(use);
    }
    ReturnIR(int val) {
        retInt = val;
        useInt = true;

        Use* use = new Use(v, this, 0);
        this->Operands.push_back(use);
    }
    ReturnIR(float val){
        retFloat = val;
        useFloat = true;

        Use* use = new Use(v, this, 0);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        out << "ret ";
        if (Operands[0]->getVal()) {
            Operands[0]->getVal()->print(out);
        }else if (useInt) {
            out << "int " << retInt;
        }else if (useFloat){
            out << "float " << retFloat;
        }
        out << "\n";
    }
};
#include "BasicBlock.hh"
class JumpIR:public Instruction{
public:
    BasicBlock* target;
    JumpIR(BasicBlock* target) : target(target){}
    void print(std::ostream& out) override final{
        out << "goto ";
        out << target->name;
        out << "\n";
    }
};
class BranchIR:public Instruction{
public:
    BasicBlock* trueTarget;
    BasicBlock* falseTarget;
    Value* cond;
    BranchIR(BasicBlock* trueTarget,BasicBlock* falseTarget,Value* cond) : trueTarget(trueTarget),falseTarget(falseTarget),cond(cond) {
        Use* use = new Use(cond, this, 0);
        cond->addUse(use);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        out << "goto ";
        Operands[0]->getVal()->print(out);
        out << " ？ ";
        if(trueTarget) {
            out << trueTarget->name;
        }
        out << " : ";
        if(falseTarget) {
            out << falseTarget->name;
        }
        out << "\n";
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

        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        Use* use3 = new Use(v3, this, 2);
        v1->addUse(use1);
        v2->addUse(use2);
        v3->addUse(use3);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
        this->Operands.push_back(use3);
    }
    GEPIR(Value* v1,Value* v2,int arrayLen){
        this->v1 = v1;
        this->v2 = v2;
        this->arrayLen = arrayLen;

        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        Use* use3 = new Use(v3, this, 2);
        v1->addUse(use1);
        v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
        this->Operands.push_back(use3);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = GEP ";
        Operands[1]->getVal()->print(out);
        if(Operands[2]->getVal()) {
            out << " ";
            Operands[2]->getVal()->print(out);
            out << std::endl;
        }else {
            out << " " << arrayLen << std::endl;
        }
    }
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

        int i(0);
        for(; i < args.size(); i++) {
            Use* use = new Use(&this->args[i], this, i);
            this->args[i].addUse(use);
            this->Operands.push_back(use);
        }

        Use* use = new Use(returnVal, this, i);
        this->Operands.push_back(use);
    }
    CallIR(Function* func,std::vector<TempVal> args, Value* v){
        this->func = func;
        this->args = args;
        this->returnVal = v;

        int i(0);
        for(; i < args.size(); i++) {
            Use* use = new Use(&this->args[i], this, i);
            this->args[i].addUse(use);
            this->Operands.push_back(use);
        }
        Use* use = new Use(returnVal, this, i);
        returnVal->addUse(use);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        if (Operands[Operands.size() - 1]->getVal()) {
            Operands[Operands.size() - 1]->getVal()->print(out);
            out << " = ";
        }
        out << "call " << func->name << "(";
        for (size_t i = 0; i < Operands.size() - 1; ++i) {
            if(dynamic_cast<TempVal*>(Operands[i]->getVal())) {
                dynamic_cast<TempVal*>(Operands[i]->getVal())->print(out);
            }else {
                if(dynamic_cast<TempVal*>(Operands[i]->getVal())->isInt()) {
                    out << dynamic_cast<TempVal*>(Operands[i]->getVal())->getInt();
                }else {
                    out << dynamic_cast<TempVal*>(Operands[i]->getVal())->getFloat();
                }
            }
            if (i < Operands.size() - 2) {
                out << " , ";
            }else {
                out << ")\n";
            }
        }
    }
};

class PhiIR : public Instruction {
public:
    Value* dst;
    std::map<BasicBlock*, Value*> params;
    bool deleted = false;
    PhiIR(std::vector<BasicBlock*> bbs, Value* var) {
        for(auto& bb : bbs) {
            params[bb] = var;
        }
        dst = var;
        
        Use* use = new Use(dst, this, 0);
        dst->addUse(use);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        if(!deleted)
        {
            Operands[0]->getVal()->print(out);
            out << " = Phi(";
            for(auto iter(params.begin()); iter != params.end(); iter++) {
                out << iter->first->name << " ";
                if(!iter->second) {
                    out << "nullptr";
                }
                else iter->second->print(out);
                out << ", ";
            }
            out << "\b\b)" << std::endl;
        }
        else out << "\r";
    }
    void deletePhiIR() { deleted = true; }
};

#endif //SYSY2022_BJTU_INSTRUCTION_HH
