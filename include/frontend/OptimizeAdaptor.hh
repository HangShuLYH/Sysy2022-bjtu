#include "Instruction.hh"
#include "IrVisitor.hh"

void optimizeAdaptor(IrVisitor* iv) {
    for(auto func : iv->getFunctions()) {
        for(auto bb : func->getBB()) {
            auto& irs = bb->getIr();
            for(auto iter(irs.begin()); iter < irs.end();) {
                if((*iter)->isDeleted()) {
                    irs.erase(iter);
                }
                else iter++;
            }
        }
    }
}

void moveBackOperand(IrVisitor* iv) {
    for(auto func : iv->getFunctions()) {
        for(auto bb : func->getBB()) {
            for(auto ir : bb->getIr()) {
                if(dynamic_cast<AllocIR*>(ir)) {
                    AllocIR* allocIr = dynamic_cast<AllocIR*>(ir);
                    allocIr->v = allocIr->getOperands()[0]->getVal();
                }
                else if(dynamic_cast<LoadIR*>(ir)) {
                    LoadIR* loadIr = dynamic_cast<LoadIR*>(ir);
                    loadIr->v1 = loadIr->getOperands()[0]->getVal();
                    loadIr->v2 = loadIr->getOperands()[1]->getVal();
                }
                else if(dynamic_cast<StoreIR*>(ir)) {
                    StoreIR* storeIr = dynamic_cast<StoreIR*>(ir);
                    storeIr->dst = storeIr->getOperands()[0]->getVal();
                    storeIr->src = *(dynamic_cast<TempVal*>(storeIr->getOperands()[1]->getVal()));
                }
                else if(dynamic_cast<CastInt2FloatIR*>(ir)) {
                    CastInt2FloatIR* i2fIr = dynamic_cast<CastInt2FloatIR*>(ir);
                    i2fIr->v1 = i2fIr->getOperands()[0]->getVal();
                    i2fIr->v2 = i2fIr->getOperands()[1]->getVal();
                }
                else if(dynamic_cast<CastFloat2IntIR*>(ir)) {
                    CastFloat2IntIR* f2iIr = dynamic_cast<CastFloat2IntIR*>(ir);
                    f2iIr->v1 = f2iIr->getOperands()[0]->getVal();
                    f2iIr->v2 = f2iIr->getOperands()[1]->getVal();
                }
                else if(dynamic_cast<ArithmeticIR*>(ir)) {
                    ArithmeticIR* arIr = dynamic_cast<ArithmeticIR*>(ir);
                    arIr->res = *(dynamic_cast<TempVal*>(arIr->getOperands()[0]->getVal()));
                    arIr->left = *(dynamic_cast<TempVal*>(arIr->getOperands()[1]->getVal()));
                    arIr->right = *(dynamic_cast<TempVal*>(arIr->getOperands()[2]->getVal()));
                }
                else if(dynamic_cast<UnaryIR*>(ir)) {
                    UnaryIR* unIr = dynamic_cast<UnaryIR*>(ir);
                    unIr->res = *(dynamic_cast<TempVal*>(unIr->getOperands()[0]->getVal()));
                    unIr->v = *(dynamic_cast<TempVal*>(unIr->getOperands()[1]->getVal()));
                }
                else if(dynamic_cast<ReturnIR*>(ir)) {
                    ReturnIR* reIr = dynamic_cast<ReturnIR*>(ir);
                    reIr->v = reIr->getOperands()[1]->getVal();
                }
                else if(dynamic_cast<BranchIR*>(ir)) {
                    BranchIR* brIr = dynamic_cast<BranchIR*>(ir);
                    brIr->cond = brIr->getOperands()[1]->getVal();
                }
                else if(dynamic_cast<GEPIR*>(ir)) {
                    GEPIR* gepIr = dynamic_cast<GEPIR*>(ir);
                    gepIr->v1 = gepIr->getOperands()[0]->getVal();
                    gepIr->v2 = gepIr->getOperands()[1]->getVal();
                    gepIr->v3 = gepIr->getOperands()[2]->getVal();
                }
                else if(dynamic_cast<CallIR*>(ir)) {
                    CallIR* callIr = dynamic_cast<CallIR*>(ir);
                    auto& operands = callIr->getOperands();
                    callIr->returnVal = operands[0]->getVal();
                    for(int i(1); i < operands.size(); i++) {
                        callIr->args[i - 1] = *(dynamic_cast<TempVal*>(callIr->getOperands()[i]->getVal()));
                    }
                }
            }
        }
    }
}