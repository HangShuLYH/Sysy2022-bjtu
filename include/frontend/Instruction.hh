//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_INSTRUCTION_HH
#define SYSY2022_BJTU_INSTRUCTION_HH
#include <string>
#include <iostream>
#include <map>
#include "Value.hh"

enum class OP{
    NEG,
    NOT,
};
class Instruction : public User {
public:
    bool deleted = false;
    Instruction() {}
    virtual void print(std::ostream& out) = 0;
    virtual ~Instruction(){}
    void deleteIR() { deleted = true; }
    bool isDeleted() { return deleted; }
};
class AllocIR: public Instruction {
public:
    bool isArray = false;
    int arrayLen = 1;
    Value* v;
    AllocIR(Value* v):v(v){
        Use* use = new Use(v, this, 0);
        // v->addUse(use);
        this->Operands.push_back(use);
    }
    AllocIR(Value* v, int arrayLen):v(v),arrayLen(arrayLen) {
        this->isArray = true;

        Use* use = new Use(v, this, 0);
        // v->addUse(use);
        this->Operands.push_back(use);
    }
    virtual void print(std::ostream& out) = 0;
};
class AllocIIR:public AllocIR{
public:
    AllocIIR(Value* v): AllocIR(v){}
    AllocIIR(Value* v, int arrayLen): AllocIR(v,arrayLen){}
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
    AllocFIR(Value* v): AllocIR(v){}
    AllocFIR(Value* v, int arrayLen): AllocIR(v,arrayLen){}
    void print(std::ostream& out) override final{
        v->print(out);
        out << " = AllocaF";
        if(isArray)
            out << "(" << arrayLen << ")";
        out << std::endl;
    }
};
class LoadIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    LoadIR(Value* v1,Value* v2):v1(v1),v2(v2){
        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        // v1->addUse(use1);
        // v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    virtual void print(std::ostream& out) = 0;
};
class LoadIIR:public LoadIR{
public:
    LoadIIR(Value* v1,Value* v2): LoadIR(v1,v2){}
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = LoadI ";
        v2->print(out);
        out << std::endl;
    }
};
class LoadFIR:public LoadIR{
public:
    LoadFIR(Value* v1,Value* v2): LoadIR(v1,v2){}
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = LoadF ";
        v2->print(out);
        out << std::endl;
    }
};
class StoreIR:public Instruction{
public:
    Value* dst;
    TempVal src;
    StoreIR(Value* dst,TempVal src):dst(dst),src(src){
        Use* use2 = new Use(dst, this, 0);
        Use* use3 = new Use(&this->src, this, 1);
        // dst->addUse(use2);
        // this->src.addUse(use3);
        // this->Operands.push_back(use1);
        this->Operands.push_back(use2);
        this->Operands.push_back(use3);
    }
    virtual void print(std::ostream& out) = 0;
};
class StoreIIR:public StoreIR{
public:
    StoreIIR(Value* dst,TempVal src): StoreIR(dst,src){
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
    StoreFIR(Value* dst,TempVal src): StoreIR(dst,src){
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
class CastInt2FloatIR:public Instruction{
public:
    Value* v1;
    Value* v2;
    CastInt2FloatIR(Value* v1,Value* v2){
        this->v1 = v1;
        this->v2 = v2;

        Use* use1 = new Use(v1, this, 0);
        Use* use2 = new Use(v2, this, 1);
        // v1->addUse(use1);
        // v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = CastInt2Float ";
        v2->print(out);
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
        // v1->addUse(use1);
        // v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        v1->print(out);
        out << " = CastFloat2Int ";
        v2->print(out);
        out << std::endl;
    }
};
class ArithmeticIR :public Instruction{
public:
    TempVal res;
    TempVal left;
    TempVal right;
    std::string op;
    virtual ~ArithmeticIR(){}
    virtual void print(std::ostream& out) = 0;
    ArithmeticIR(TempVal res,TempVal left,TempVal right): res(res),left(left),right(right) {
        Use* use1 = new Use(&this->res, this, 0);
        Use* use2 = new Use(&this->left, this, 1);
        Use* use3 = new Use(&this->right, this, 2);
        // this->res.addUse(use1);
        // this->left.addUse(use2);
        // this->right.addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
        this->Operands.push_back(use3);
    }
};
class AddIIR:public ArithmeticIR{
public:
    AddIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "+"; }
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
    AddFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "+";
    }
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
    SubIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "-"; }
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
    SubFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "-";
    }
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
    MulIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "*"; }
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
    MulFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "*";
    }
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
    DivIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "/"; }
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
    DivFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "/";
    }
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
    ModIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "%"; }
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
    UnaryIR(TempVal res,TempVal v,OP op): res(res), v(v), op(op){
        Use* use1 = new Use(&this->res, this, 0);
        Use* use2 = new Use(&this->v, this, 1);
        // this->res.addUse(use1);
        // this->v.addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        res.print(out);
        out << " = ";
        if (res.isInt()) {
            switch (op) {
                case OP::NEG:
                    out << "NEGF ";
                    break;
                case OP::NOT:
                    out << "NOTF ";
                    break;
            }
        } else {
            switch (op) {
                case OP::NEG:
                    out << "NEGF ";
                    break;
                case OP::NOT:
                    out << "NOTF ";
                    break;
            }
        }
        v.print(out);
        out << std::endl;
    }
};
class LTIIR:public ArithmeticIR{
public:
    LTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){this->op = "<";}
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
    LTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "<";
    }
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
    LEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "<="; }
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
    LEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "<=";
    }
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
    GTIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = ">"; }
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
    GTFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = ">";
    }
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
    GEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = ">="; }
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
    GEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = ">=";
    }
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
    EQUIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "=="; }
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
    EQUFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "==";
    }
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
    NEIIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){ this->op = "!="; }
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
    NEFIR(TempVal res,TempVal left,TempVal right) : ArithmeticIR(res,left,right){
        if (!left.getVal() && left.isInt()) {
            this->left.setType(new Type(TypeID::FLOAT));
            this->left.setFloat(left.getInt());
        }
        if (!right.getVal() && right.isInt()) {
            this->right.setType(new Type(TypeID::FLOAT));
            this->right.setFloat(right.getInt());
        }

        this->op = "!=";
    }
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

        Use* use1 = new Use(nullptr, this, 0);
        Use* use2 = new Use(v, this, 0);
        // v->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    ReturnIR(int val) {
        retInt = val;
        useInt = true;

        Use* use1 = new Use(nullptr, this, 0);
        Use* use2 = new Use(v, this, 0);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    ReturnIR(float val){
        retFloat = val;
        useFloat = true;

        Use* use1 = new Use(nullptr, this, 0);
        Use* use2 = new Use(v, this, 0);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
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
class BasicBlock;
class JumpIR:public Instruction{
public:
    BasicBlock* target;
    JumpIR(BasicBlock* target) : target(target){}
    void print(std::ostream& out) override final{
        out << "goto ";
        //out << target->name;
        out << "\n";
    }
};
class BranchIR:public Instruction{
public:
    BasicBlock* trueTarget;
    BasicBlock* falseTarget;
    Value* cond;
    BranchIR(BasicBlock* trueTarget,BasicBlock* falseTarget,Value* cond) :
            trueTarget(trueTarget),falseTarget(falseTarget),cond(cond) {
        Use* use1 = new Use(nullptr, this, 0);
        Use* use2 = new Use(cond, this, 0);
        // cond->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
    }
    void print(std::ostream& out) override final{
        out << "goto ";
        cond->print(out);
        out << " ？ ";
        if(trueTarget) {
            //out << trueTarget->name;
        }
        out << " : ";
        if(falseTarget) {
            //out << falseTarget->name;
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
        // v1->addUse(use1);
        // v2->addUse(use2);
        // v3->addUse(use3);
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
        // v1->addUse(use1);
        // v2->addUse(use2);
        this->Operands.push_back(use1);
        this->Operands.push_back(use2);
        this->Operands.push_back(use3);

        v1->setArray(true);
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
class Function;
class CallIR:public Instruction{
public:
    Function* func;
    std::vector<TempVal> args;
    Value* returnVal = nullptr;
    CallIR(Function* func,std::vector<TempVal> args) {
        this->func = func;
        this->args = args;

        Use* use = new Use(returnVal, this, 0);
        this->Operands.push_back(use);

        for(int i(0); i < args.size(); i++) {
            Use* use = new Use(&this->args[i], this, i + 1);
            // this->args[i].addUse(use);
            this->Operands.push_back(use);
        }
    }
    CallIR(Function* func,std::vector<TempVal> args, Value* v){
        this->func = func;
        this->args = args;
        this->returnVal = v;

        Use* use = new Use(returnVal, this, 0);
        // returnVal->addUse(use);
        this->Operands.push_back(use);

        for(int i(0); i < args.size(); i++) {
            Use* use = new Use(&this->args[i], this, i + 1);
            // this->args[i].addUse(use);
            this->Operands.push_back(use);
        }
    }
    void print(std::ostream& out) override final{
        if (returnVal) {
            returnVal->print(out);
            out << " = ";
        }
        out << "call " /*<< func->name*/ << "(";
        for (size_t i = 0; i < args.size(); ++i) {
            if(args[i].getVal()) {
                args[i].getVal()->print(out);
            }else {
                if(args[i].isInt()) {
                    out << args[i].getInt();
                }else if (args[i].isFloat()){
                    out << args[i].getFloat();
                } else {
                    out << args[i].getString();
                }
            }
            if (i < args.size() - 1) {
                out << " , ";
            }
        }
        out << ")\n";
    }
};

class PhiIR : public Instruction {
public:
    Value* dst;
    std::map<BasicBlock*, Value*> params;
    PhiIR(std::vector<BasicBlock*> bbs, Value* var) {
        for(auto& bb : bbs) {
            params[bb] = var;
        }
        dst = var;

        Use* use = new Use(dst, this, 0);
        // dst->addUse(use);
        this->Operands.push_back(use);
    }
    void print(std::ostream& out) override final{
        Operands[0]->getVal()->print(out);
        out << " = Phi(";
        for(auto iter(params.begin()); iter != params.end(); iter++) {
            // out << iter->first->name << " ";
            if(!iter->second) {
                out << "nullptr";
            }
            else iter->second->print(out);
            out << ", ";
        }
        out << "\b\b)" << std::endl;
    }
};

#endif //SYSY2022_BJTU_INSTRUCTION_HH

