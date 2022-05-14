//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_VALUE_HH
#define SYSY2022_BJTU_VALUE_HH
#include <string>
#include <iostream>
#include <vector>

enum class TYPE{
    INT,
    FLOAT,
    VOID,
    INTPOINTER,
    FLOATPOINTER
};
inline std::ostream& operator << (std::ostream& out,TYPE tp) {
    switch (tp) {
        case TYPE::INT:
            out << "int";break;
        case TYPE::FLOAT:
            out << "float";break;
        case TYPE::VOID:
            out << "void";break;
        case TYPE::INTPOINTER:
            out << "int*";break;
        case TYPE::FLOATPOINTER:
            out << "float*";break;
    }
    return out;
}
class Value{
public:
    int num;
    std::string name;
    TYPE type;
    bool isGlobal = false;
    bool isArray = false;
    Value(){}
    virtual ~Value(){}
    virtual void print() = 0;
};
class VarValue:public Value{
public:
    VarValue(int num,std::string name,TYPE type) {
        this->num = num;
        this->name = name;
        this->type = type;
    }
    void print() override final {
        if (isGlobal){
            std::cout << type << " @" << name;
        }else {
            std::cout << type << " @" << num;
        }
    }
};
class ConstValue:public Value{
public:
    int intVal;
    float floatVal;
    void setInt(int val) {intVal = val;}
    void setFloat(float val) {floatVal = val;}
    ConstValue(int num,std::string name,TYPE type){
        this->num = num;
        this->name = name;
        this->type = type;
    }
    void print() override final {
        std::cout <<"const "<< type << " @" << name;
        if (type == TYPE::INT) {
            std::cout << " = " <<intVal;
        }else{
            std::cout << " = " << floatVal;
        }
    }
};
class ArrayValue:public Value{
public:
    int *intList;
    float *floatList;
    int arrayLen;
    int cur;
    ArrayValue(int num, int arrayLen, std::string name, TYPE type) {
        this->num = num;
        if(type == TYPE::INTPOINTER)
            this->intList = new int[arrayLen];
        else if(type == TYPE::FLOATPOINTER)
            this->floatList = new float[arrayLen];
        this->arrayLen = arrayLen;
        this->name = name;
        this->type = type;
        this->cur = 0;
        this->isArray = true;
    }
    void pushBackInt(int val)
    {
        intList[this->cur++] = val;
    }
    void pushBackFloat(float val)
    {
        floatList[this->cur++] = val;
    }
    void print() override final {
        if (isGlobal){
            std::cout << type << " @" << name << "[" << arrayLen << "]";
        } else {
            std::cout << type << " @" << num << "[" << arrayLen << "]";
        }
    }
};
#endif //SYSY2022_BJTU_VALUE_HH
