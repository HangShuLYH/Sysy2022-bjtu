//
// Created by hangshu on 22-7-5.
//

#ifndef SYSY2022_BJTU_INSTR_HH
#define SYSY2022_BJTU_INSTR_HH
#include "reg.hh"
enum COND {
    NOTHING,
    LT,
    GT,
    LE,
    GE,
    EQU,
    NE
};
class Instr {
public:
    virtual void print(std::ostream& out) = 0;
};
class GRegRegInstr: public Instr {
public:
    enum Type {Add,Sub,Mul,Div} op;
    GR dst, src1, src2;
    GRegRegInstr(Type op,GR dst, GR src1,GR src2): dst(dst),src1(src1),src2(src2){}
    void print(std::ostream& out) override final{
        switch (op) {
            case Add:
                out << "add ";
                break;
            case Sub:
                out << "sub ";
                break;
            case Mul:
                out << "mul ";
                break;
            case Div:
                out << "sdiv ";
                break;
        }
        out << dst.getName() << "," << src1.getName() << "," << src2.getName() << "\n";
    }
};
class VRegRegInstr: public Instr {
public:
    enum Type {VAdd,VSub,VMul,VDiv} op;
    FR dst, src1, src2;
    VRegRegInstr(Type op,FR dst, FR src1,FR src2): dst(dst),src1(src1),src2(src2){}
    void print(std::ostream& out) override final{
        switch (op) {
            case VAdd:
                out << "vadd ";
                break;
            case VSub:
                out << "vsub ";
                break;
            case VMul:
                out << "vmul ";
                break;
            case VDiv:
                out << "vdiv ";
                break;
        }
        out << dst.getName() << "," << src1.getName() << "," << src2.getName() << "\n";
    }
};
class GRegImmInstr: public Instr{
public:
    enum Type {Add,Sub} op;
    GR dst, src1;
    int src2;
    GRegImmInstr(Type op,GR dst,GR src1,int src2): dst(dst),src1(src1),src2(src2){}
    void print(std::ostream& out) override final{
        switch (op) {
            case Add:
                out << "add ";
                break;
            case Sub:
                out << "sub ";
                break;
        }
        out << dst.getName() << "," << src1.getName() << ", #" << src2 << "\n";
    }
};
/*
class LoadFromSymbol: public Instr {
public:
    GR dst;
    std::string symbol;
    LoadFromSymbol(GR dst, std::string symbol): dst(dst),symbol(symbol){}
};
class VLoadFromSymbol: public Instr{
public:
    FR dst;
    std::string symbol;
    VLoadFromSymbol(FR dst, std::string symbol): dst(dst),symbol(symbol){}
};
 */
class Load: public Instr {
public:
    GR dst;
    GR base;
    int offset;
    Load(GR dst,GR base,int offset): dst(dst),base(base), offset(offset){}
    void print(std::ostream& out) override final{
        out << "ldr " << dst.getName() << ",["<<base.getName() << ",#"<<offset << "\n";
    }
};
class VLoad: public Instr {
public:
    FR dst;
    GR base;
    int offset;
    VLoad(FR dst,GR base,int offset): dst(dst), base(base), offset(offset){}
    void print(std::ostream& out) override final{
        out << "vldr " << dst.getName() << ",["<<base.getName() << ",#"<<offset << "\n";
    }
};
//class StoreToSymbol: public Instr{
//public:
//    GR src;
//    std::string symbol;
//};
class Store: public Instr{
public:
    GR src;
    GR base;
    int offset;
    Store(GR src,GR base,int offset): src(src), base(base),offset(offset){}
    void print(std::ostream& out) override final{
        out << "str " << src.getName() << ",["<<base.getName() << ",#"<<offset << "\n";
    }
};
class VStore: public Instr{
public:
    FR src;
    GR base;
    int offset;
    VStore(FR src,GR base,int offset): src(src), base(base),offset(offset){}
    void print(std::ostream& out) override final{
        out << "vsdr " << src.getName() << ",["<<base.getName() << ",#"<<offset << "\n";
    }
};
class MovImm: public Instr {
public:
    GR dst;
    int imm;
    COND cond = NOTHING;
    MovImm(GR dst,int imm): dst(dst),imm(imm) {}
    MovImm(GR dst,int imm,COND cond): dst(dst),imm(imm),cond(cond) {}
    void print(std::ostream& out) override final{
        out << "mov " << dst.getName() << ",#" << imm << "\n";
    }
};
class VMovGF: public Instr {
public:
    GR dst;
    FR src;
    VMovGF(GR dst,FR src): dst(dst),src(src) {}
    void print(std::ostream& out) override final{
        out << "vmov " << dst.getName() << src.getName() << "\n";
    }
};
class VMovFG: public Instr{
public:
    FR dst;
    GR src;
    VMovFG(FR dst,GR src): dst(dst),src(src) {}
    void print(std::ostream& out) override final{
        out << "vmov " << dst.getName() << "," <<src.getName() << "\n";
    }
};
class VMovImm: public Instr{
public:
    FR dst;
    float imm;
    VMovImm(FR dst,float imm): dst(dst),imm(imm) {}
    void print(std::ostream& out) override final{
        out << "vmov " << dst.getName() << ",#" << imm << "\n";
    }
};
// top half word of dst = 0
// bottom half word of dst = src
// precondition: 0 <= src < 65536
class MoveW: public Instr{
public:
    GR dst;
    int src;
    MoveW(GR dst, int src):dst(dst),src(src) {}
    void print(std::ostream& out) override final{

    }
};
// top half word of dst = src
// bottom half word of dst remains
// precondition: 0 <= src < 65536
class MoveT: public Instr{
public:
    GR dst;
    int src;
    MoveT(GR dst, int src):dst(dst),src(src) {}
    void print(std::ostream& out) override final{

    }
};
// top half word of dst = 0
// bottom half word of dst = src
// precondition: 0 <= src < 65536
class MoveWFromSymbol: public Instr{
public:
    GR dst;
    std::string symbol;
    MoveWFromSymbol(GR dst, std::string symbol):dst(dst),symbol(symbol) {}
    void print(std::ostream& out) override final{
        out << "movw " << dst.getName() << ",#:lower16:" << symbol;
    }
};
// top half word of dst = src
// bottom half word of dst remains
// precondition: 0 <= src < 65536
class MoveTFromSymbol: public Instr{
public:
    GR dst;
    std::string symbol;
    MoveTFromSymbol(GR dst, std::string symbol):dst(dst),symbol(symbol) {}
    void print(std::ostream& out) override final{
        out << "movt " << dst.getName() << ",#:upper16:" << symbol;
    }
};
class MLA: public Instr{
public:
    GR dst;
    GR mul1,mul2;
    GR add;
    MLA(GR dst,GR mul1,GR mul2,GR add): dst(dst),mul1(mul1),mul2(mul2),add(add){}
    void print(std::ostream& out) override final{
        out << "mla " << dst.getName() << "," << mul1.getName() << "," << mul2.getName() << "," << add.getName() << "\n";
    }
};
class VcvtSF: public Instr{
public:
    FR dst;
    FR src;
    VcvtSF(FR dst,FR src):dst(dst),src(src){}
    void print(std::ostream& out) override final{
        out << "vcvt.s16.f16 " << dst.getName() << "," <<src.getName() << "\n";
    }
};
class VcvtFS: public Instr{
public:
    FR dst;
    FR src;
    VcvtFS(FR dst,FR src):dst(dst),src(src){}
    void print(std::ostream& out) override final{
        out << "vcvt.f16.s16 " << dst.getName() << "," <<src.getName() << "\n";
    }
};
class Cmp:public Instr{
public:
    GR src1;
    GR src2;
    Cmp(GR src1, GR src2): src1(src1),src2(src2){}
    void print(std::ostream& out) override final{
        out << "cmp " << src1.getName() << "," << src2.getName() << "\n";
    }
};
class CmpImm:public Instr{
public:
    GR src1;
    int imm;
    CmpImm(GR src1,int imm):src1(src1),imm(imm){}
    void print(std::ostream& out) override final{
        out << "cmp " << src1.getName() << ",#" << imm << "\n";
    }
};
class VCmpe:public Instr{
public:
    FR src1;
    FR src2;
    VCmpe(FR src1,FR src2): src1(src1),src2(src2) {}
    void print(std::ostream& out) override final{
        out << "vcmpe " << src1.getName() << "," << src2.getName() << "\n";
    }
};
class VMrs: public Instr{
public:
    //vmrs APSR_nzcv, FPSCR
    VMrs(){}
    void print(std::ostream& out) override final{
        out << "vmrs APSR_nzcv, FPSCR\n";
    }
};
class B: public Instr{
public:
    std::string target;
    COND cond = NOTHING;
    B(std::string target):target(target){}
    B(std::string target,COND cond):target(target),cond(cond){}
    void print(std::ostream& out) override final{
        out << "b";
        switch (cond) {
            case NOTHING:
                break;
            case LT:
                out << "lt";
                break;
            case LE:
                out << "le";
                break;
            case GT:
                out << "gt";
                break;
            case GE:
                out << "ge";
                break;
            case EQU:
                out << "equ";
                break;
            case NE:
                out << "ne";
                break;
        }
        out << " " << target << "\n";
    }
};
class Bl: public Instr{
public:
    std::string target;
    Bl(std::string target):target(target){}
    void print(std::ostream& out) override final{
        out << "bl " << target << "\n";
    }
};
class Bx: public Instr{
public:
    //bx lr
    Bx(){}
    void print(std::ostream& out) override final{
        out << "bx lr\n";
    }
};
class MoveReg: public Instr{
public:
    GR dst;
    GR src;
    MoveReg(GR dst,GR src):dst(dst),src(src){}
    void print(std::ostream& out) override final{
        out << "mov " << dst.getName() << "," << src.getName() << "\n";
    }
};
class VMoveReg: public Instr{
public:
    FR dst;
    FR src;
    VMoveReg(FR dst,FR src):dst(dst),src(src){}
    void print(std::ostream& out) override final{
        out << "vmov " << dst.getName() << "," << src.getName() << "\n";
    }
};
#endif //SYSY2022_BJTU_INSTR_HH
