//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_VALUE_HH
#define SYSY2022_BJTU_VALUE_HH
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "syntax_tree.hh"

class Value;
class Use;
class User;

enum TypeID {
    INT,
    FLOAT,
    STRING,
    VOID,
    POINTER,
};
class Type{
public:
    Type(TypeID tid) : tid(tid) {}
    Type(TypeID tid,Type* contained) : tid(tid),contained(contained){}
    bool isInt() {
        return tid == INT;
    }
    bool isFloat() {
        return tid == FLOAT;
    }
    bool isString() {
        return tid == STRING;
    }
    bool isVoid(){
        return tid == VOID;
    }
    bool isPointer(){
        return tid == POINTER;
    }
    bool isIntPointer(){
        return tid == POINTER && contained->isInt();
    }
    bool isFloatPointer(){
        return tid == POINTER && contained->isFloat();
    }
    Type* getContained() {
        return contained;
    }
    void print(std::ostream& out) {
        switch (tid) {
            case INT:
                out << "int";
                break;
            case FLOAT:
                out << "float";
                break;
            case VOID:
                out << "void";
                break;
            case STRING:
                out << "string";
                break;
            case POINTER:
                contained->print(out);
                out << "*";
        }
    }
private:
    TypeID tid;
    Type* contained;
};

class BasicBlock;
class Use {
private:
    Value* Val;
    User *U;
    int arg;
    BasicBlock* bb;
public:
    Value* getVal() { return Val; }
    User* getUser() { return U; }
    int getArg() { return arg; }
    BasicBlock* getBB() { return bb; }
    void setVal(Value* Val) { this->Val = Val; }
    Use(Value* Val, User* U, int arg);
    Use(Value* Val, User* U, BasicBlock* bb);
    Use();
};

class Value{
public:
    Value(){}
    virtual ~Value(){}
    virtual void print(std::ostream& out) = 0;
    bool is_Array() {return isArray;}
    void setArray(bool flag) {isArray = flag;}
    void setArrayDims(std::vector<int> arrDims) {arrayDims = arrDims;}
    void setArrayLen(int arrayLen) {this->arrayLen = arrayLen;}
    void setGlobal(bool g) {isGlobal = g;}
    void pushDim(int dim) {arrayDims.push_back(dim);}
    int getArrayLen() {
        if (arrayLen == 0) {
            arrayLen = 1;
            for (int i = 0; i < arrayDims.size(); ++i) {
                arrayLen *= arrayDims[i];
            }
        }
        return arrayLen;
    }
    bool is_Global() {return isGlobal;}
    std::string getName() {return name;}
    int getNum() {return num;}
    std::vector<int> getArrayDims() {return arrayDims;}
    Type* getType() {return type;}
    void addUse(Use* U) {
        this->Uses.insert(U);
    }
    void killUse(Use* U) { this->Uses.erase(U); }
    void clearUses() { this->Uses.clear(); }
    std::set<Use*> getUses() { return Uses; }
    void setNum(int num) { this->num = num; }
    void setType(Type* type) { this->type = type; }
protected:
    int num;
    std::string name;
    Type* type;
    bool isGlobal = false;
    bool isArray = false;
    std::vector<int> arrayDims;
    int arrayLen = 0;
    std::set<Use*> Uses;
};
class VarValue: public Value{
public:
    VarValue(){}
    VarValue(std::string name,Type* type,bool isGlobal,int func_cnt) {
        this->num = isGlobal?0:func_cnt;
        this->name = name;
        this->type = type;
        this->isGlobal = isGlobal;
    }
    //flag: distinguish from the constructor above
    VarValue(std::string name,Type* type,bool isGlobal,int func_cnt,bool flag) {
        this->num = func_cnt;
        this->name = name;
        this->type = type;
        this->isGlobal = isGlobal;
    }
    void print(std::ostream& out = std::cout) override final {
        if (isGlobal){
            type->print(out);
            out << " @" << name;
        }else {
            type->print(out);
            out << " @" << num;
        }
    }
    void push() {
        if(isArray) this->arrayLen++;
    }
};
struct TempVal : public Value{
private:
    int valInt;
    float valFloat;
    Value* val;
    Type* type;
    std::string stringConst;
public:
    TempVal() {
        this->valInt = 0;
        this->valFloat = 0.0;
        this->val = nullptr;
        this->type = nullptr;
        this->stringConst = "";
    }
    void print(std::ostream& out) {
        if (val) {
            val->print(out);
        } else if (type->isString()) {
            out << stringConst;
        }else {
            out << getConst();
        }
    }
    bool isInt() {return type->isInt();}
    bool isFloat() {return type->isFloat();}
    int getInt() {return valInt;}
    float getFloat() {return valFloat;}
    float getConst() {
        if (type->isInt()) {
            return valInt;
        } else {
            return valFloat;
        }
    }
    void setConst(float val) {
        if (type->isInt()) {
            setInt(val);
        } else {
            setFloat(val);
        }
    }
    std::string getString() {return stringConst;}
    Type* getType() {return type;}
    void setInt(int x) {valInt = x;}
    void setFloat(float x) {valFloat = x;}
    void setVal(Value* v) {val = v;}
    void setType(Type* t) {type = t;}
    void setString(std::string s) {stringConst = s;}
    Value* getVal() {return val;}
    static TempVal calConstArithmetic(TempVal v1, TempVal v2, char op) {
        TempVal res;
        if (v1.isFloat()) {
            res.setType(v1.getType());
        }else {
            res.setType(v2.getType());
        }
        static int xi;
        static int yi;
        static float xf;
        static float yf;
        if (res.isInt()) {
            xi = v1.getInt();
            yi = v2.getInt();
        }
        if (res.isFloat()) {
            if (v1.isInt()) {
                xf = v1.getInt();
            } else {
                xf = v1.getFloat();
            }
            if (v2.isInt()) {
                yf = v2.getInt();
            } else {
                yf = v2.getFloat();
            }
        }
        if (res.isInt()) {
            switch (op) {
                case '+':
                    res.setInt(xi + yi);
                    break;
                case '-':
                    res.setInt(xi - yi);
                    break;
                case '*':
                    res.setInt(xi * yi);
                    break;
                case '/':
                    res.setInt(xi / yi);
                    break;
                case '%':
                    res.setInt(xi % yi);
                    break;
            }
        } else {
            switch (op) {
                case '+':
                    res.setFloat(xf + yf);
                    break;
                case '-':
                    res.setFloat(xf - yf);
                    break;
                case '*':
                    res.setFloat(xf * yf);
                    break;
                case '/':
                    res.setFloat(xf / yf);
                    break;
            }
        }
        return res;
    }
    static TempVal calConstLogical(TempVal v1,TempVal v2,relop op,Type* t) {
        TempVal res;
        res.setType(t);
        switch (op) {
            case relop::OP_NE:
                res.setConst(v1.getConst() != v2.getConst());
                break;
            case relop::OP_EQU:
                res.setConst(v1.getConst() == v2.getConst());
                break;
            case relop::OP_LT:
                res.setConst(v1.getConst() < v2.getConst());
                break;
            case relop::OP_LE:
                res.setConst(v1.getConst() <= v2.getConst());
                break;
            case relop::OP_GT:
                res.setConst(v1.getConst() > v2.getConst());
                break;
            case relop::OP_GE:
                res.setConst(v1.getConst() >= v2.getConst());
                break;
        }
        return res;
    }
};
class ConstValue:public Value{
public:
    int getIntVal() {return intVal;}
    float getFloatVal() {return floatVal;}
    std::vector<int> getIntValList() {return intValList;}
    std::vector<float> getFloatValList() {return floatValList;}
    void setInt(int val) {intVal = val;}
    void setFloat(float val) {floatVal = val;}
    float getArrayVal(int index) {
        if (!intValList.empty()) {
            return intValList[index];
        }else {
            return floatValList[index];
        }
    }
    ConstValue(std::string name,Type* type,TempVal tempVal, bool isGlobal,int func_cnt){
        this->num = isGlobal?0:func_cnt++;
        this->name = name;
        this->type = type;
        this->isGlobal = isGlobal;
        if (type->isInt()) {
            if (tempVal.isInt()) {
                setInt(tempVal.getInt());
            } else {
                setInt(tempVal.getFloat());
            }
        } else {
            if (tempVal.isInt()) {
                setFloat(tempVal.getInt());
            }else {
                setFloat(tempVal.getFloat());
            }
        }
    }
    ConstValue(std::string name,Type* type,bool isGlobal, int func_cnt){
        this->num = isGlobal?0:func_cnt;
        this->name = name;
        this->type = type;
        this->isGlobal = isGlobal;
    }
    void print(std::ostream& out) override final {
        if(!isArray)
        {
            out << "const ";
            type->print(out);
            std::cout << " @" <<name;
            if (type->isInt()) {
                out << " = " <<intVal;
            }else{
                out << " = " << floatVal;
            }
        }
        else
        {
            if (isGlobal){
                out << "const ";
                type->print(out);
                out << " @" << name;
            }else {
                out << "const ";
                type->print(out);
                out << " @" << num;
            }
        }

    }
    void push(int val) {
        if(isArray) intValList.push_back(val);
    }
    void push(float val) {
        if(isArray) floatValList.push_back(val);
    }
private:
    int intVal;
    float floatVal;
    std::vector<int> intValList;
    std::vector<float> floatValList;

};

class User : public Value {
protected:
    std::vector<Use*> Operands;
public:
    User() {;}
    void addOperand(Use* Operand) { Operands.push_back(Operand); }
    std::vector<Use*>& getOperands() { return this->Operands; }
};

#endif