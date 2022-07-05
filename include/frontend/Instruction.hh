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
    virtual std::vector<Value*> getUseList() = 0;
    virtual Value* getDef() = 0;
    virtual void print(std::ostream& out) = 0;
    virtual ~Instruction(){}
};
class AllocIR : public Instruction {
public:
    bool isArray = false;
    int arrayLen;
    Value* v;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
    virtual void print(std::ostream& out) = 0;
};
class AllocIIR:public AllocIR{
public:
    AllocIIR(Value* v){
        this->v = v;
    }
    AllocIIR(Value* v, int arrayLen) {
        this->isArray = true;
        this->arrayLen = arrayLen;
        this->v = v;
    }
    void print(std::ostream& out) override final{
        v->print(out);
        out << " = AllocaI";
        if(isArray)
            out << "(" << arrayLen << ")";
        out << std::endl;
    }
};
class AllocFIR:public AllocIR{
public:
    AllocFIR(Value* v){
        this->v = v;
    }
    AllocFIR(Value* v, int arrayLen) {
        this->isArray = true;
        this->arrayLen = arrayLen;
        this->v = v;
    }
    void print(std::ostream& out) override final{
        v->print(out);
        out << " = AllocaF";
        if(isArray)
            out << "(" << arrayLen << ")";
        out << std::endl;
    }
};
class LoadIR : public Instruction {
public:
    Value* v1;
    Value* v2;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return v1;
    }
};
class LoadIIR:public LoadIR{
public:
    LoadIIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = LoadI ";
        v2->print(out);
        out << std::endl;
    }
};
class LoadFIR:public LoadIR{
public:
    LoadFIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = LoadI ";
        v2->print(out);
        out << std::endl;
    }
};
class StoreIR: public Instruction {
public:
    //storeI v2 v1
    Value* dst;
    TempVal src;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        if (src.getVal()) {
            vec.push_back(src.getVal());
        }
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
};
class StoreIIR:public StoreIR{
public:
    StoreIIR(Value* dst,TempVal src){
        this->dst = dst;
        this->src = src;
        if (!src.getVal() && src.isFloat()) {
            this->src.setType(dst->getType()->getContained());
            this->src.setInt(src.getFloat());
        }
    }
    void print(std::ostream& out) override final{
        out << "StoreI ";
        src.print(out);
        out << " ";
        dst->print(out);
        out << std::endl;
    }
};
class StoreFIR:public StoreIR{
public:
    StoreFIR(Value* dst,TempVal src){
        this->dst = dst;
        this->src = src;
        if (!src.getVal() && src.isInt()) {
            src.setType(dst->getType()->getContained());
            src.setFloat(src.getFloat());
        }
    }
    void print(std::ostream& out) override final{
        out << "StoreF ";
        src.print(out);
        out << " ";
        dst->print(out);
        out << std::endl;
    }
};
class CastIR: public Instruction {
public:
    Value* v1;
    Value* v2;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        vec.push_back(v2);
        return vec;
    }
    Value* getDef() {
        return v1;
    }
};
class CastInt2FloatIR:public CastIR{
public:

    CastInt2FloatIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = CastInt2Float ";
        v2->print(out);
        out << std::endl;
    }
};
class CastFloat2IntIR:public CastIR{
public:
    CastFloat2IntIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;
    }
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = CastFloat2Int ";
        v2->print(out);
        out << std::endl;
    }
};
class ArithmeticIR:public Instruction{
public:
    TempVal res;
    TempVal left;
    TempVal right;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        if (left.getVal()) {
            vec.push_back(left.getVal());
        }
        if (right.getVal()) {
            vec.push_back(right.getVal());
        }
        return vec;
    }
    Value* getDef() {
        return res.getVal();
    }
    ArithmeticIR(TempVal res,TempVal left,TempVal right) : res(res),left(left),right(right){}
    virtual void print(std::ostream& out) = 0;
    virtual ~ArithmeticIR(){}
};
class AddIIR:public ArithmeticIR{
public:
    AddIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = AddI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class AddFIR:public ArithmeticIR{
public:
    AddFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = AddF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};

class SubIIR:public ArithmeticIR{
public:
    SubIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = SubI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class SubFIR:public ArithmeticIR{
public:
    SubFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = SubF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class MulIIR:public ArithmeticIR{
public:
    MulIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = MulI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class MulFIR:public ArithmeticIR{
public:
    MulFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = MulF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class DivIIR:public ArithmeticIR{
public:
    DivIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = DivI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class DivFIR:public ArithmeticIR{
public:
    DivFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = DivF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class ModIR:public ArithmeticIR{
public:
    ModIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = Mod ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class UnaryIR:public Instruction{
public:
    TempVal res;
    TempVal v;
    OP op;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        vec.push_back(v.getVal());
        return vec;
    }
    Value* getDef() {
        return res.getVal();
    }
    UnaryIR(TempVal res,TempVal v,OP op): res(res), v(v), op(op){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = ";
        switch (op) {
            case OP::NEG:
                out << "NEG ";break;
            case OP::NOT:
                out << "NOT ";break;
        }
        v.print(out);
        out << std::endl;
    }
};
class LTIIR:public ArithmeticIR{
public:
    LTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = LTI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class LTFIR:public ArithmeticIR{
public:
    LTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = LTF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class LEIIR:public ArithmeticIR{
public:
    LEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = LEI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class LEFIR:public ArithmeticIR{
public:
    LEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = LEF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class GTIIR:public ArithmeticIR{
public:
    GTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = GTI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class GTFIR:public ArithmeticIR{
public:
    GTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = GTF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class GEIIR:public ArithmeticIR{
public:
    GEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = GEI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class GEFIR:public ArithmeticIR{
public:
    GEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = GEF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class EQUIIR:public ArithmeticIR{
public:
    EQUIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = EQUI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class EQUFIR:public ArithmeticIR{
public:
    EQUFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = EQUF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class NEIIR:public ArithmeticIR{
public:
    NEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = NEI ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class NEFIR:public ArithmeticIR{
public:
    NEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){}
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = NEF ";
        left.print(out);
        out << " ";
        right.print(out);
        out << std::endl;
    }
};
class BreakIR:public Instruction{
public:
    BreakIR(){};
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
    void print(std::ostream& out) override final{
        out << "break" << std::endl;
    }
};
class ContinueIR:public Instruction{
public:
    ContinueIR(){};
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
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
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        if (v) {
            vec.push_back(v);
        }
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
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
    void print(std::ostream& out) override final{
        out << "ret ";
        if (v) {
            v->print(out);
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
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
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
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
    BranchIR(BasicBlock* trueTarget,BasicBlock* falseTarget,Value* cond) :
    trueTarget(trueTarget),falseTarget(falseTarget),cond(cond) {}
    void print(std::ostream& out) override final{
        out << "goto ";
        cond->print(out);
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
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        if(v3) {
            vec.push_back(v3);
        }
        return vec;
    }
    Value* getDef() {
        return v1;
    }
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
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = GEP ";
        v2->print(out);
        if(v3) {
            out << " ";
            v3->print(out);
            out << std::endl;
        }else {
            out << " " << arrayLen << std::endl;
        }
    };
};
#include "Function.hh"
class CallIR:public Instruction{
public:
    Function* func;
    std::vector<TempVal> args;
    Value* returnVal = nullptr;
    std::vector<Value*> getUseList() {
        std::vector<Value*> vec;
        return vec;
    }
    Value* getDef() {
        return nullptr;
    }
    CallIR(Function* func,std::vector<TempVal> args) {
        this->func = func;
        this->args = args;
    }
    CallIR(Function* func,std::vector<TempVal> args, Value* v){
        this->func = func;
        this->args = args;
        this->returnVal = v;
    }
    void print(std::ostream& out) override final{
        if (returnVal) {
            returnVal->print(out);
            out << " = ";
        }
        out << "call " << func->name << "(";
        for (size_t i = 0; i < args.size(); ++i) {
            if(args[i].getVal()) {
                args[i].getVal()->print(out);
            }else {
                if(args[i].isInt()) {
                    out << args[i].getInt();
                }else {
                    out << args[i].getFloat();
                }
            }
            if (i < args.size() - 1) {
                out << " , ";
            }else {
                out << ")\n";
            }
        }
    }
};

#endif //SYSY2022_BJTU_INSTRUCTION_HH
