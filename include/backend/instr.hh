//
// Created by hangshu on 22-7-5.
//

#ifndef SYSY2022_BJTU_INSTR_HH
#define SYSY2022_BJTU_INSTR_HH
#include "reg.hh"
#include <map>
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
    virtual std::vector<GR> getUseG() = 0;
    virtual std::vector<FR> getUseF() = 0;
    virtual std::vector<GR> getDefG() = 0;
    virtual std::vector<FR> getDefF() = 0;
    virtual void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) = 0;
    virtual void replaceBBName(std::map<std::string, std::string> mapping) {}
    virtual void setNewGR(GR old_gr, GR new_gr, bool use) {}
    virtual void setNewFR(FR old_fr, FR new_fr, bool use) {}
};
class GRegRegInstr: public Instr {
public:
    enum Type {Add,Sub,Mul,Div,RSUB} op;
    enum Shift {Nothing,LSL,LSR} shift = Nothing;
    int shiftNum;
    GR dst, src1, src2;
    GRegRegInstr(Type op,GR dst, GR src1,GR src2): dst(dst),src1(src1),src2(src2),op(op){}
    GRegRegInstr(Type op,GR dst, GR src1,GR src2, Shift shift, int shiftNum): dst(dst),src1(src1),src2(src2),op(op),shift(shift),shiftNum(shiftNum){}
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src1 == old_gr) src1 = new_gr;
            if (src2 == old_gr) src2 = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        src1 = GR(grMapping[src1]);
        src2 = GR(grMapping[src2]);
    }
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
            case RSUB:
                out << "rsb ";
                break;
            default:
                out << "wrongInstr ";
                break;
        }
        out << dst.getName() << "," << src1.getName() << "," << src2.getName();
        if (shift == LSL) {
            out << ",LSL #" << shiftNum;
        } else if (shift == LSR){
            out << ",LSR #" << shiftNum;
        }
        out << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src1,src2};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class LSImmInstr: public Instr {
public:
    enum Type {LSL,LSR} op;
    int shiftNum;
    GR dst, src;
    LSImmInstr(Type op,GR dst, GR src,int shiftNum): dst(dst),src(src),op(op),shiftNum(shiftNum){}
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src == old_gr) src = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        src = GR(grMapping[src]);
    }
    void print(std::ostream& out) override final{
        switch (op) {
            case LSL:
                out << "lsl ";
                break;
            case LSR:
                out << "lsr ";
                break;
            default:
                out << "wrongInstr ";
                break;
        }
        out << dst.getName() << "," << src.getName() << ",#" << shiftNum << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VRegRegInstr: public Instr {
public:
    enum Type {VAdd,VSub,VMul,VDiv} op;
    FR dst, src1, src2;
    VRegRegInstr(Type op,FR dst, FR src1,FR src2): dst(dst),src1(src1),src2(src2),op(op){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        src1 = FR(frMapping[src1]);
        src2 = FR(frMapping[src2]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src1 == old_fr) src1 = new_fr;
            if (src2 == old_fr) src2 = new_fr;
        } else {
            if (dst == old_fr) dst = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        switch (op) {
            case VAdd:
                out << "vadd.f32 ";
                break;
            case VSub:
                out << "vsub.f32 ";
                break;
            case VMul:
                out << "vmul.f32 ";
                break;
            case VDiv:
                out << "vdiv.f32 ";
                break;
        }
        out << dst.getName() << "," << src1.getName() << "," << src2.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src1,src2};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class GRegImmInstr: public Instr{
public:
    enum Type {Add,Sub,RSUB} op;
    GR dst, src1;
    int src2;
    COND cond = NOTHING;
    GRegImmInstr(Type op,GR dst,GR src1,int src2): dst(dst),src1(src1),src2(src2),op(op){}
    GRegImmInstr(Type op,GR dst,GR src1,int src2,COND cond): dst(dst),src1(src1),src2(src2),op(op),cond(cond){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        src1 = GR(grMapping[src1]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src1 == old_gr) src1 = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        switch (op) {
            case Add:
                out << "add";
                break;
            case Sub:
                out << "sub";
                break;
            case RSUB:
                out << "rsb";
                break;
        }
        switch (cond) {
            case LT:
                out << "lt ";
                break;
            default:
                out << " ";
        }
        out << dst.getName() << "," << src1.getName() << ", #" << src2 << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src1};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
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
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        base = GR(grMapping[base]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (base == old_gr) base = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "ldr " << dst.getName() << ",["<<base.getName() << ",#"<<offset << "]\n";
    }
    std::vector<GR> getUseG() override final{
        return {base};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VLoad: public Instr {
public:
    FR dst;
    GR base;
    int offset;
    VLoad(FR dst,GR base,int offset): dst(dst), base(base), offset(offset){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        base = GR(grMapping[base]);
    }
    void print(std::ostream& out) override final{
        out << "vldr.32 " << dst.getName() << ",["<<base.getName() << ",#"<<offset << "]\n";
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (base == old_gr) base = new_gr;
        }
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (!use) {
            if (dst == old_fr) dst = new_fr;
        }
    }
    std::vector<GR> getUseG() override final{
        return {base};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class VLoadFromSymbol: public Instr {
public:
    FR dst;
    std::string symbol;
    VLoadFromSymbol(FR dst,std::string symbol): dst(dst),symbol(symbol){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
    }
    void print(std::ostream& out) override final{
        out << "vldr.32 " << dst.getName() << ", " << symbol << "\n";
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {}
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (!use) {
            if (dst == old_fr) dst = new_fr;
        }
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
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
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        src = GR(grMapping[src]);
        base = GR(grMapping[base]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (base == old_gr) base = new_gr;
            if (src == old_gr) src = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "str " << src.getName() << ",["<<base.getName() << ",#"<<offset << "]\n";
    }
    std::vector<GR> getUseG() override final{
        return {src,base};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VStore: public Instr{
public:
    FR src;
    GR base;
    int offset;
    VStore(FR src,GR base,int offset): src(src), base(base),offset(offset){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        src = FR(frMapping[src]);
        base = GR(grMapping[base]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (base == old_gr) base = new_gr;
        }
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src == old_fr) src = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vstr.32 " << src.getName() << ",["<<base.getName() << ",#"<<offset << "]\n";
    }
    std::vector<GR> getUseG() override final{
        return {base};
    }
    std::vector<FR> getUseF() override final{
        return {src};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class MovImm: public Instr {
public:
    GR dst;
    int imm;
    COND cond = NOTHING;
    MovImm(GR dst,int imm): dst(dst),imm(imm) {}
    MovImm(GR dst,int imm,COND cond): dst(dst),imm(imm),cond(cond) {}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "mov";
        switch (cond) {
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
                out << "eq";
                break;
            case NE:
                out << "ne";
                break;
        }
        out << " "<< dst.getName() << ",#" << imm << "\n";
    }
    std::vector<GR> getUseG() override final{
        if (cond != NOTHING) {
            return {dst};
        }
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VMovGF: public Instr {
public:
    GR dst;
    FR src;
    VMovGF(GR dst,FR src): dst(dst),src(src) {}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        src = FR(frMapping[src]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src == old_fr) src = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vmov " << dst.getName() << ","<< src.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VMovFG: public Instr{
public:
    FR dst;
    GR src;
    VMovFG(FR dst,GR src): dst(dst),src(src) {}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        src = GR(grMapping[src]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src == old_gr) src = new_gr;
        }
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (!use) {
            if (dst == old_fr) dst = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vmov " << dst.getName() << "," <<src.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class VMovImm: public Instr{
public:
    FR dst;
    float imm;
    VMovImm(FR dst,float imm): dst(dst),imm(imm) {}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (!use) {
            if (dst == old_fr) dst = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vmov.f32 " << dst.getName() << ",#" << imm << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
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
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "movw " << dst.getName() << ",#" << src << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
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
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "movt " << dst.getName() << ",#" << src << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
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
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "movw " << dst.getName() << ",#:lower16:" << symbol << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
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
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "movt " << dst.getName() << ",#:upper16:" << symbol << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class MLA: public Instr{
public:
    GR dst;
    GR mul1,mul2;
    GR add;
    MLA(GR dst,GR mul1,GR mul2,GR add): dst(dst),mul1(mul1),mul2(mul2),add(add){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        mul1 = GR(grMapping[mul1]);
        mul2 = GR(grMapping[mul2]);
        add = GR(grMapping[add]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (mul1 == old_gr) mul1 = new_gr;
            if (mul2 == old_gr) mul2 = new_gr;
            if (add == old_gr) add = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "mla " << dst.getName() << "," << mul1.getName() << "," << mul2.getName() << "," << add.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {mul1,mul2,add};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VcvtSF: public Instr{
public:
    FR dst;
    FR src;
    VcvtSF(FR dst,FR src):dst(dst),src(src){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        src = FR(frMapping[src]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src == old_fr) src = new_fr;
        } else {
            if (dst == old_fr) dst = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vcvt.s32.f32 " << dst.getName() << "," <<src.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class VcvtFS: public Instr{
public:
    FR dst;
    FR src;
    VcvtFS(FR dst,FR src):dst(dst),src(src){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        src = FR(frMapping[src]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src == old_fr) src = new_fr;
        } else {
            if (dst == old_fr) dst = old_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vcvt.f32.s32 " << dst.getName() << "," <<src.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class Cmp:public Instr{
public:
    GR src1;
    GR src2;
    Cmp(GR src1, GR src2): src1(src1),src2(src2){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        src1 = GR(grMapping[src1]);
        src2 = GR(grMapping[src2]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src1 == old_gr) src1 = new_gr;
            if (src2 == old_gr) src2 = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "cmp " << src1.getName() << "," << src2.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src1,src2};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class CmpImm:public Instr{
public:
    GR src1;
    int imm;
    CmpImm(GR src1,int imm):src1(src1),imm(imm){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        src1 = GR(grMapping[src1]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src1 == old_gr) src1 = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "cmp " << src1.getName() << ",#" << imm << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src1};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VCmpe:public Instr{
public:
    FR src1;
    FR src2;
    VCmpe(FR src1,FR src2): src1(src1),src2(src2) {}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        src1 = FR(frMapping[src1]);
        src2 = FR(frMapping[src2]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src1 == old_fr) src1 = new_fr;
            if (src2 == old_fr) src2 = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vcmpe.f32 " << src1.getName() << "," << src2.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src1,src2};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VMrs: public Instr{
public:
    //vmrs APSR_nzcv, FPSCR
    VMrs(){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "vmrs APSR_nzcv, FPSCR\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class B: public Instr{
public:
    std::string target;
    COND cond = NOTHING;
    B(std::string target):target(target){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    virtual void replaceBBName(std::map<std::string, std::string> mapping) override{
        target = mapping[target];
    }
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
                out << "eq";
                break;
            case NE:
                out << "ne";
                break;
        }
        out << " " << target << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class Bl: public Instr{
public:
    std::string target;
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
//    virtual void replaceBBName(std::map<std::string, std::string> mapping) override{
//        target = mapping[target];
//    }
    Bl(std::string target):target(target){}
    void print(std::ostream& out) override final{
        out << "bl " << target << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {GR(0),GR(1),GR(2),GR(3),GR(12)};
    }
    std::vector<FR> getDefF() override final{
        return {FR(0)};
    }
};
class Ret: public Instr{
public:
    //bx lr
    Ret(){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "bx lr\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class MoveReg: public Instr{
public:
    GR dst;
    GR src;
    int asr = -1;
    MoveReg(GR dst,GR src):dst(dst),src(src){}
    MoveReg(GR dst,GR src,int asr):dst(dst),src(src),asr(asr){}
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src == old_gr) src = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        src = GR(grMapping[src]);
    }
    void print(std::ostream& out) override final{
        out << "mov " << dst.getName() << "," << src.getName();
        if (asr != -1) {
            out << ",asr #" <<asr;
        }
        out << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VMoveReg: public Instr{
public:
    FR dst;
    FR src;
    VMoveReg(FR dst,FR src):dst(dst),src(src){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        src = FR(frMapping[src]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src == old_fr) src = new_fr;
        } else {
            if (dst == old_fr) dst = new_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vmov.32 " << dst.getName() << "," << src.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class MvnImm:public Instr{
public:
    GR dst;
    int imm;
    MvnImm(GR dst,int imm):dst(dst),imm(imm){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (!use) {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "mvn " << dst.getName() << ",#" << imm << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
//dst = src2 - src1;
class RsubImm: public Instr {
public:
    GR dst;
    GR src1;
    int src2;
    RsubImm(GR dst,GR src1,int src2):dst(dst),src1(src1),src2(src2){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = GR(grMapping[dst]);
        src1 = GR(grMapping[src1]);
    }
    void setNewGR(GR old_gr, GR new_gr, bool use) {
        if (use) {
            if (src1 == old_gr) src1 = new_gr;
        } else {
            if (dst == old_gr) dst = new_gr;
        }
    }
    void print(std::ostream& out) override final{
        out << "rsb " << dst.getName() << "," << src1.getName() << ",#" << src2 << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {src1};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {dst};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class VNeg: public Instr{
public:
    FR dst;
    FR src;
    VNeg(FR dst,FR src):dst(dst),src(src){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {
        dst = FR(frMapping[dst]);
        src = FR(frMapping[src]);
    }
    void setNewFR(FR old_fr, FR new_fr, bool use) {
        if (use) {
            if (src == old_fr) src = new_fr;
        } else {
            if (dst == old_fr) dst = old_fr;
        }
    }
    void print(std::ostream& out) override final{
        out << "vneg.f32 " << dst.getName() << "," << src.getName() << "\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {src};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {dst};
    }
};
class Push: public Instr {
public:
    std::set<GR> regs;
    Push(std::set<GR> regs):regs(regs){}
    void addRegs(std::set<GR> regs){this->regs = regs;}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "push {";
        bool first = true;
        for (GR gr: regs) {
            if (first) {
                first = false;
            } else {
                out << ",";
            }
            out << gr.getName();
        }
        out << "}\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class Vpush: public Instr {
public:
    std::set<FR> regs;
    Vpush(std::set<FR> regs):regs(regs){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "vpush {";
        bool first = true;
        for (FR fr: regs) {
            if (first) {
                first = false;
            } else {
                out << ",";
            }
            out << fr.getName();
        }
        out << "}\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class Pop: public Instr {
public:
    std::set<GR> regs;
    Pop(std::set<GR> regs):regs(regs){}
    void addRegs(std::set<GR> regs){this->regs = regs;}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "pop {";
        bool first = true;
        for (GR gr: regs) {
            if (first) {
                first = false;
            } else {
                out << ",";
            }
            out << gr.getName();
        }
        out << "}\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class Vpop: public Instr {
public:
    std::set<FR> regs;
    Vpop(std::set<FR> regs):regs(regs){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "vpop {";
        bool first = true;
        for (FR fr: regs) {
            if (first) {
                first = false;
            } else {
                out << ",";
            }
            out << fr.getName();
        }
        out << "}\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
class Bx: public Instr {
public:
    Bx(){}
    void replace(std::map<GR, int> grMapping, std::map<FR, int> frMapping) {}
    void print(std::ostream& out) override final{
        out << "bx lr\n";
    }
    std::vector<GR> getUseG() override final{
        return {};
    }
    std::vector<FR> getUseF() override final{
        return {};
    }
    std::vector<GR> getDefG() override final{
        return {};
    }
    std::vector<FR> getDefF() override final{
        return {};
    }
};
#endif //SYSY2022_BJTU_INSTR_HH
