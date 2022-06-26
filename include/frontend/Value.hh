//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_VALUE_HH
#define SYSY2022_BJTU_VALUE_HH
#include <string>
#include <iostream>
#include <vector>
#include "syntax_tree.hh"
enum TypeID {
    INT,
    FLOAT,
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
    void print() {
        switch (tid) {
            case INT:
                std::cout << "int";
                break;
            case FLOAT:
                std::cout << "float";
                break;
            case VOID:
                std::cout << "void";
                break;
            case POINTER:
                contained->print();
                std::cout << "*";
        }
    }
private:
    TypeID tid;
    Type* contained;
};

class Value{
public:
    Value(){}
    virtual ~Value(){}
    virtual void print() = 0;
    bool is_Array() {return isArray;}
    void setArray(bool flag) {isArray = flag;}
    void setArrayDims(std::vector<int> arrDims) {arrayDims = arrDims;}
    void setArrayLen(int arrayLen) {this->arrayLen = arrayLen;}
    void setGlobal(bool g) {isGlobal = g;}
    void pushDim(int dim) {arrayDims.push_back(dim);}
    int getArrayLen() {return arrayLen;}
    bool is_Global() {return isGlobal;}
    std::string getName() {return name;}
    std::vector<int> getArrayDims() {return arrayDims;}
    Type* getType() {return type;}
protected:
    int num;
    std::string name;
    Type* type;
    bool isGlobal = false;
    bool isArray = false;
    std::vector<int> arrayDims;
    int arrayLen = 0;

};
class VarValue: public Value{
public:
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
    void print() override final {
        if (isGlobal){
            type->print();
            std::cout << " @" << name;
        }else {
            type->print();
            std::cout << " @" << num;
        }
    }
    void push() {
        if(isArray) this->arrayLen++;
    }
};
struct TempVal {
private:
    int valInt;
    float valFloat;
    Value* val;
    Type* type;
public:
    void print() {
        if (val) {
            val->print();
        } else {
            std::cout << getConst();
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
    Type* getType() {return type;}
    void setInt(int x) {valInt = x;}
    void setFloat(float x) {valFloat = x;}
    void setVal(Value* v) {val = v;}
    void setType(Type* t) {type = t;}
    Value* getVal() {return val;}
    static TempVal calConstArithmetic(TempVal v1, TempVal v2, char op) {
        TempVal res;
        if (v1.isFloat()) {
            res.setType(v1.getType());
        }else {
            res.setType(v2.getType());
        }
        switch (op) {
            case '+':
                res.setConst(v1.getConst() + v2.getConst());
                break;
            case '-':
                res.setConst(v1.getConst() - v2.getConst());
                break;
            case '*':
                res.setConst(v1.getConst() * v2.getConst());
                break;
            case '/':
                res.setConst(v1.getConst() / v2.getConst());
                break;
            case '%':
                res.setConst((int)v1.getConst() % (int)v2.getConst());
                break;
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
    void print() override final {
        if(!isArray)
        {
            std::cout << "const ";
            type->print();
            std::cout << " @" <<name;
            if (type->isInt()) {
                std::cout << " = " <<intVal;
            }else{
                std::cout << " = " << floatVal;
            }
        }
        else
        {
            if (isGlobal){
                std::cout << "const ";
                type->print();
                std::cout << " @" << name;
            }else {
                std::cout << "const ";
                type->print();
                std::cout << " @" << num;
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

#endif