//
// Created by lin on 2022/7/3.
//

#ifndef SYSY2022_BJTU_MIRBUILDER_HH
#define SYSY2022_BJTU_MIRBUILDER_HH

#endif //SYSY2022_BJTU_MIRBUILDER_HH

#include <map>
#include "IrVisitor.hh"
class ReturnOfRelated{
public:
    int type = 0;
    int index = 0;
    ReturnOfRelated(int t, int i){
        type = t;
        index = i;
    }
};

class MIRBuilder{
public:
    MIRBuilder(IrVisitor& iv){irVisitor = iv;}
    NormalBlock* toNormal(BasicBlock* bb);
    std::vector<BasicBlock*> refresh(std::vector<BasicBlock*> bbs, BasicBlock* nextAB);
    void getPreAndSucc();
    BasicBlock* frontOfNextBB(BasicBlock* bb);
    ReturnOfRelated* relatedIR(std::vector<Instruction*> ir);
    std::vector<BasicBlock*> relatedContinueBreak(std::vector<BasicBlock*> bbs, BasicBlock* firstCond, BasicBlock* nextAB);
    std::vector<BasicBlock*> relatedCond(std::vector<BasicBlock*> bbs, BasicBlock* firstBB, BasicBlock* nextAB);
    void print(std::ostream& out);
    NormalBlock* getCondToNormal(CondBlock* cb);
    void putCondToNormal(CondBlock* cb, NormalBlock* nb);
    void removeDuplicate();
private:
    IrVisitor irVisitor;
    std::map<CondBlock*, NormalBlock*> condToNormal;
    std::map<CondBlock*, std::vector<NormalBlock*>> reversedSucc;
};