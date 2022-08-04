//
// Created by hangshu on 22-6-23.
//

#ifndef SYSY2022_BJTU_IRMANAGER_HH
#define SYSY2022_BJTU_IRMANAGER_HH

#include "Instruction.hh"

class AllocIRManager {
public:
    static Instruction *getIR(Value *v) {
        if (v->getType()->isIntPointer() || v->getType()->getContained()->isIntPointer()) {
            return new AllocIIR(v);
        } else {
            return new AllocFIR(v);
        }
    }

    static Instruction *getIR(Value *v, int arrayLen) {
        if (v->getType()->isIntPointer()) {
            return new AllocIIR(v, arrayLen);
        } else {
            return new AllocFIR(v, arrayLen);
        }
    }
};

class LoadIRManager {
public:
    static Instruction *getIR(Value *v, Value *t) {
        if (v->getType()->isInt() || v->getType()->isIntPointer() ||
            v->getType()->isPointer()) {
            return new LoadIIR(v, t);
        } else {
            return new LoadFIR(v, t);
        }
    }
};

class StoreIRManager {
public:
    static Instruction *getIR(Value *dst, TempVal src) {
        if (dst->getType()->isIntPointer() ||
            dst->getType()->getContained()->isIntPointer()) {
            return new StoreIIR(dst, src);
        } else {
            return new StoreFIR(dst, src);
        }
    }
    static Instruction *getIR(Value *dst, Value* src) {
        TempVal t;
        t.setVal(src);
        t.setType(src->getType());
        if (dst->getType()->isIntPointer() ||
            dst->getType()->getContained()->isIntPointer() ||
            src->getType()->isPointer()) {
            return new StoreIIR(dst, t);
        } else {
            return new StoreFIR(dst, t);
        }
    }
    static Instruction *getIR(Value *dst, int src, Type* type) {
        TempVal t;
        t.setVal(nullptr);
        t.setType(type);
        t.setInt(src);
        if (dst->getType()->isIntPointer()) {
            return new StoreIIR(dst, t);
        } else {
            return new StoreFIR(dst, t);
        }
    }
    static Instruction *getIR(Value *dst, float src, Type* type) {
        TempVal t;
        t.setVal(nullptr);
        t.setType(type);
        t.setFloat(src);
        if (dst->getType()->isIntPointer()) {
            return new StoreIIR(dst, t);
        } else {
            return new StoreFIR(dst, t);
        }
    }
};

class CastIRManager {
public:
    static Instruction *getIR(Value *dst, TempVal src) {
        if (dst->getType()->isInt()) {
            return new CastFloat2IntIR(dst, src.getVal());
        } else {
            return new CastInt2FloatIR(dst, src.getVal());
        }
    }
};

class ArithmeticIRManager {
public:
    //v1.type should equals to v2.type
    static Instruction *getIR(TempVal res, TempVal v1, TempVal v2, char op) {
        if (res.isInt()) {
            switch (op) {
                case '+':
                    return new AddIIR(res, v1, v2);
                case '-':
                    return new SubIIR(res, v1, v2);
                case '*':
                    return new MulIIR(res, v1, v2);
                case '/':
                    return new DivIIR(res, v1, v2);
                case '%':
                    return new ModIR(res, v1, v2);

            }
        } else {
            switch (op) {
                case '+':
                    return new AddFIR(res, v1, v2);
                case '-':
                    return new SubFIR(res, v1, v2);
                case '*':
                    return new MulFIR(res, v1, v2);
                case '/':
                    return new DivFIR(res, v1, v2);
            }
        }
    }
};

class UnaryIRManager {
public:
    static Instruction *getIR(TempVal res, TempVal v, char op) {
        switch (op) {
            case '-':
                return new UnaryIR(res, v, OP::NEG);
            case '!':
                return new UnaryIR(res, v, OP::NOT);
        }
    }
};

class LogicalIRManager {
public:
    static Instruction *getIR(TempVal res, TempVal v1, TempVal v2, relop op) {
        if (v1.isInt()) {
            switch (op) {
                case relop::OP_NE:
                    return new NEIIR(res, v1, v2);
                case relop::OP_EQU:
                    return new EQUIIR(res, v1, v2);
                case relop::OP_LT:
                    return new LTIIR(res, v1, v2);
                case relop::OP_GT:
                    return new GTIIR(res, v1, v2);
                case relop::OP_LE:
                    return new LEIIR(res, v1, v2);
                case relop::OP_GE:
                    return new GEIIR(res, v1, v2);
            }
        } else {
            switch (op) {
                case relop::OP_NE:
                    return new NEFIR(res, v1, v2);
                case relop::OP_EQU:
                    return new EQUFIR(res, v1, v2);
                case relop::OP_LT:
                    return new LTFIR(res, v1, v2);
                case relop::OP_GT:
                    return new GTFIR(res, v1, v2);
                case relop::OP_LE:
                    return new LEFIR(res, v1, v2);
                case relop::OP_GE:
                    return new GEFIR(res, v1, v2);
            }
        }
    }
};

#endif //SYSY2022_BJTU_IRMANAGER_HH