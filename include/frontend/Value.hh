//
// Created by hangshu on 22-4-26.
//

#ifndef SYSY2022_BJTU_VALUE_HH
#define SYSY2022_BJTU_VALUE_HH
#include <string>
#include <vector>
enum TYPE{
    INT,
    FLOAT,
    VOID,
    BOOL,
};
class Value{
public:
    bool isGlobal;
    bool isConst;
    bool isInit;
    bool isArray;
    bool isTrue;
    std::string name;
    TYPE type;
    int initIntVal;
    float initFloatVal;
    std::vector<int> dims;
    std::vector<Value*> initVals;
    Value(std::string name,TYPE type,bool isArray) {
        this->name = name;
        this->type = type;
        this->isArray = isArray;
    }
    Value(std::string name,TYPE type,bool isInit,bool isConst,int initIntVal,float initFloatVal) {
        this->name = name;
        this->type = type;
        this->isInit = isInit;
        this->isConst = isConst;
        this->initIntVal = initIntVal;
        this->initFloatVal = initFloatVal;
    }
    Value(Value *v) {
        isGlobal = v->isGlobal;
        isConst = v->isConst;
        isInit = v->isInit;
        isArray = v->isArray;
        name = v->name;
        type = v->type;
        initIntVal = v->initIntVal;
        initFloatVal = v->initFloatVal;
        dims.swap(v->dims);
        initVals.swap(v->initVals);
    }
};

#endif //SYSY2022_BJTU_VALUE_HH
