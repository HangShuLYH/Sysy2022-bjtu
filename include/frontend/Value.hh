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
};
class Value{
public:
    bool isGlobal;
    bool isConst;
    bool isInit;
    bool isArray;
    std::string name;
    TYPE type;
    int initIntVal;
    float initFloatVal;
    std::vector<int> dims;
    std::vector<int> initIntVals;
    std::vector<float> initFloatVals;
    Value(std::string,TYPE type) {
        this->name = name;
        this->type = type;
    }
    Value(std::string name, TYPE type,
          bool isGlobal, bool isConst, bool isArray){
        this->name = name;
        this->type = type;
        this->isGlobal = isGlobal;
        this->isConst = isConst;
        this->isInit = isInit;
        this->isArray = isArray;
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
        initIntVals.swap(v->initIntVals);
        initFloatVals.swap(v->initFloatVals);
    }
};

#endif //SYSY2022_BJTU_VALUE_HH
