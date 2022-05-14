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
    int arrayLen = 0;
    Value(){}
    virtual ~Value(){}
    virtual void print() = 0;
    void push() {
        if(isArray) this->arrayLen++;
    }
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
    std::vector<int> intValList;
    std::vector<float> floatValList;
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
    void push(int val) {
        if(isArray) intValList.push_back(val);
    }
    void push(float val) {
        if(isArray) floatValList.push_back(val);
    }
};
#endif