//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_VALUE_HH
#define SYSY2022_BJTU_VALUE_HH
#include <string>
#include <iostream>
#include <vector>
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
    int num;
    std::string name;
    Type* type;
    bool isGlobal = false;
    bool isArray = false;
    std::vector<int> arrayDims;
    int arrayLen = 0;
    Value(){}
    virtual ~Value(){}
    virtual void print() = 0;
};
class VarValue:public Value{
public:
    VarValue(int num,std::string name,Type* type) {
        this->num = num;
        this->name = name;
        this->type = type;
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
class ConstValue:public Value{
public:
    int intVal;
    float floatVal;
    std::vector<int> intValList;
    std::vector<float> floatValList;
    void setInt(int val) {intVal = val;}
    void setFloat(float val) {floatVal = val;}
    ConstValue(int num,std::string name,Type* type){
        this->num = num;
        this->name = name;
        this->type = type;
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
                std::cout << " " << num;
            }
        }

    }
    void push(int val) {
        if(isArray) intValList.push_back(val);
    }
    void push(float val) {
        if(isArray) floatValList.push_back(val);
    }
};
#endif