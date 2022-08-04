//
// Created by hangshu on 22-7-4.
//

#ifndef SYSY2022_BJTU_REG_HH
#define SYSY2022_BJTU_REG_HH
const std::string gReg_name[] = {"r0",  "r1", "r2", "r3", "r4",  "r5",
                                 "r6",  "r7", "r8", "r9", "r10", "r11",
                                 "r12", "sp", "lr", "pc"};
const std::string fReg_name[] = {"s0","s1","s2","s3","s4","s5",
                                 "s6","s7","s8","s9","s10","s11",
                                 "s12","s13","s14","s15","s16","s17",
                                 "s18","s19","s20","s21","s22","s23","s24","s25",
                                 "s26","s27","s28","s29","s30","s31"};
const int max_gReg_id = 15;
const int max_fReg_id = 31;
class GR{
public:
    static int reg_num;
    GR() {}
    GR(int nu) {id = nu;}
    std::string getName() {
        if (id <= 15) {
            return gReg_name[id];
        }
        return "r" + std::to_string(id);
    }
    int getID() {return id;}
    bool isVirtual() {return id > max_gReg_id;}
    static GR allocateReg() {GR gr(reg_num++);return gr;}
    const bool operator<(const GR& gr) const {return this->id < gr.id;}
    const bool operator==(const GR& gr) const {return this->id == gr.id;}
    const bool operator!=(const GR& gr) const {return this->id != gr.id;}
    const bool operator>(const GR& gr) const {return this->id > gr.id;}
private:
    int id;
};
class FR{
public:
    static int reg_num;
    FR() {}
    FR(int nu) {id = nu;}
    std::string getName() {
        if (id <= 31) {
            return fReg_name[id];
        }
        return "s" + std::to_string(id);
    }
    int getID() {return id;}
    bool isVirtual() {return id > max_fReg_id;}
    static FR allocateReg() {FR fr(reg_num++);return fr;}
    const bool operator<(const FR& fr) const {return this->id < fr.id;}
    const bool operator==(const FR& fr) const {return this->id == fr.id;}
    const bool operator!=(const FR& fr) const {return this->id != fr.id;}
    const bool operator>(const FR& fr) const {return this->id > fr.id;}
private:
    int id;
};
class StackObj {
public:
    int addr;
    StackObj(int addr):addr(addr){}
};
#endif //SYSY2022_BJTU_REG_HH
