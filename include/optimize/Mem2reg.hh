//
// Created by hanyangchen on 22-6-30.
//

#include "IrVisitor.hh"
#include "Instruction.hh"
#include "IRManager.hh"
#include <map>
#include <stack>
#include <algorithm>

class Mem2reg {
private:
    IrVisitor* irVisitor;
    Function* function;
    std::map<Value*, std::set<BasicBlock*>> defsites;
    std::map<BasicBlock*, std::set<Value*>> bbPhis;
    std::map<Value*, std::stack<Value*>> stk;
    std::map<Value*, Value*> count;
public:
    Mem2reg(IrVisitor* irVisitor) : irVisitor(irVisitor) {;}
    void execute();
    void rename(BasicBlock* bb);
    void getOriginVals();
    void placePhi();
    void constValBroadcast();
};

void Mem2reg::execute()
{
    std::vector<Function*> functions = irVisitor->getFunctions();
    for(Function* func : functions) {
        if(func->getBB().size() == 0) continue;

        this->function = func;
        defsites.clear();
        bbPhis.clear();
        stk.clear();
        count.clear();

        getOriginVals();
        placePhi();
        rename(func->basicBlocks[0]);
        constValBroadcast();
    }
}

void Mem2reg::getOriginVals() {
    for(auto bb : function->getBB()) {
        for(auto ir : bb->getIr()) {
            if((typeid(*ir) == typeid(AllocIIR) || typeid(*ir) == typeid(AllocFIR)) && !ir->is_Array()) {
                auto operands = ir->getOperands();
                bb->originVals.insert(operands[0]->getVal());
                function->allocaVars.insert(operands[0]->getVal());
            }
            else if(typeid(*ir) == typeid(StoreIIR) || typeid(*ir) == typeid(StoreFIR)) {
                auto operands = ir->getOperands();
                if(function->allocaVars.count(operands[0]->getVal())) {
                    bb->originVals.insert(operands[0]->getVal());
                }
            }
        }
    }
}

void Mem2reg::placePhi() {
    for(BasicBlock* bb : function->getBB()) {
        for(auto val : bb->originVals) {
            defsites[val].insert(bb);
        }
    }

    for(auto& defsite : defsites) {
        std::set<BasicBlock*> W(defsite.second);
        while(!W.empty()) {
            BasicBlock* bb(*W.begin());
            W.erase(W.begin());
            for(auto& dfBB : bb->getDomFrontier()) {
                if(!bbPhis[dfBB].count(defsite.first)) {
                    PhiIR* phiIr = new PhiIR(dfBB->getPre(), defsite.first);
                    dfBB->ir.insert(dfBB->ir.begin(), phiIr);
                    bbPhis[dfBB].insert(defsite.first);

                    if(!bb->originVals.count(defsite.first)) {
                        W.insert(dfBB);
                    }
                }
            }
        }
    }
}

void Mem2reg::rename(BasicBlock* bb) {
    std::map<Value*, int> valCnt;

    for(auto ir : bb->getIr()) {
        auto& operands = ir->getOperands();
        if(operands.size() <= 0) continue;
        if(typeid(*ir) != typeid(PhiIR)) {
            for(int i(1); i < operands.size(); i++) {
                if(operands[i]->getVal() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), operands[i]->getVal()) == end(irVisitor->globalVars)) {
                    if(typeid(*(operands[i]->getVal())) != typeid(TempVal)) {
                        if(stk[operands[i]->getVal()].size() != 0) {
                            Value* newVal = stk[operands[i]->getVal()].top();
                            if(typeid(*newVal) == typeid(TempVal)) {
                                TempVal* temp = dynamic_cast<TempVal*>(newVal);
                                operands[i]->setVal(temp->getVal());

                                Use* use = new Use(temp->getVal(), ir, i);
                                temp->getVal()->addUse(use);
                            }
                            else {
                                operands[i]->setVal(newVal);

                                Use* use = new Use(newVal, ir, i);
                                newVal->addUse(use);
                            }
                        } else {
                            stk[operands[i]->getVal()].push(operands[i]->getVal());
                        }
                    } else {
                        TempVal* temp = dynamic_cast<TempVal*>((operands[i]->getVal()));
                        if(temp->getVal()) {
                            if(stk[temp->getVal()].size() != 0) {
                                Value* newVal = stk[temp->getVal()].top();
                                if(typeid(*newVal) == typeid(TempVal)) {
                                    operands[i]->setVal(newVal);
                                    
                                    Use* use = new Use(newVal, ir, i);
                                    dynamic_cast<TempVal*>(newVal)->getVal()->addUse(use);
                                } else {
                                    TempVal* newTempVal = new TempVal();
                                    newTempVal->setVal(newVal);
                                    operands[i]->setVal(newTempVal);

                                    Use* use = new Use(newTempVal, ir, i);
                                    newVal->addUse(use);
                                }
                            } else {
                                stk[temp->getVal()].push(temp);
                            }
                        }
                    }
                }
            }
        }
        
        if(operands.size() > 0 && operands[0]->getVal() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), operands[0]->getVal()) == end(irVisitor->globalVars)) {
            Value* val = operands[0]->getVal(), *newVal = nullptr;
            if(typeid(*(val)) == typeid(VarValue)) {
                newVal = new VarValue(*dynamic_cast<VarValue*>(val));
                newVal->clearUses();
                newVal->setNum(function->varCnt++);
            }
            else if(typeid(*val) == typeid(ConstValue)) {
                newVal = new ConstValue(*dynamic_cast<ConstValue*>(val));
                newVal->clearUses();
                newVal->setNum(function->varCnt++);
            }
            else if(typeid(*val) == typeid(TempVal) && dynamic_cast<TempVal*>(val)->getVal()) {
                val = dynamic_cast<TempVal*>(val)->getVal();
                Value* tempNewVal = nullptr;
                if(typeid(*(val)) == typeid(VarValue)) {
                    tempNewVal = new VarValue(*dynamic_cast<VarValue*>(val));
                }
                else if(typeid(*val) == typeid(ConstValue)) {
                    tempNewVal = new ConstValue(*dynamic_cast<ConstValue*>(val));
                }
                tempNewVal->clearUses();
                tempNewVal->setNum(function->varCnt++);
                newVal = new TempVal();
                dynamic_cast<TempVal*>(newVal)->setVal(tempNewVal);
            }
            else continue;

            count[val] = newVal;
            stk[val].push(newVal);
            operands[0]->setVal(newVal);

            valCnt[val]++;
        }
    }

    for(auto succBB : bb->getSucc()) {
        for(auto ir : succBB->getIr()) {
            if(typeid(*ir) == typeid(PhiIR)) {
                PhiIR* phiIr = dynamic_cast<PhiIR*>(ir);
                auto iter = find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), phiIr->params[bb]);
                if(iter == end(irVisitor->globalVars)) {
                    if(stk[phiIr->params[bb]].size() != 0) {
                        phiIr->params[bb] = stk[phiIr->params[bb]].top();
                        if(typeid(*(phiIr->params[bb])) == typeid(TempVal)) {
                            TempVal* temp = dynamic_cast<TempVal*>(phiIr->params[bb]);
                            if(temp->getVal()) {
                                Use* use = new Use(temp, phiIr, bb);
                                temp->getVal()->addUse(use);
                            }
                        } else {
                            Use* use = new Use(phiIr->params[bb], phiIr, bb);
                            phiIr->params[bb]->addUse(use);
                        }
                    } else {
                        stk[phiIr->params[bb]].push(phiIr->params[bb]);
                    }
                }
            } else break;
        }
    }

    for(auto domTreeSuccNode : bb->getDomTreeSuccNode()) {
        rename(domTreeSuccNode);
    }

    for(auto valCntPair : valCnt) {
        for(; valCntPair.second > 0; valCntPair.second--) {
            stk[valCntPair.first].pop();
        }
    }
}

void Mem2reg::constValBroadcast() {
    for(auto bb : function->getBB()) {
        auto W = bb->getIr();
        while(!W.empty()) {
            auto inst = *W.rbegin();
            W.pop_back();
            if(typeid(*inst) == typeid(PhiIR)) {
                PhiIR* phiIr = dynamic_cast<PhiIR*>(inst);
                std::set<float> constFloatSet;
                std::set<int> constIntSet;
                bool flag = true;
                for(auto param : phiIr->params) {
                    if(!param.second) {
                        flag = false;
                        break;
                    }
                    if(typeid(*(param.second)) == typeid(TempVal) && !dynamic_cast<TempVal*>(param.second)->getVal()) {
                        TempVal* temp = dynamic_cast<TempVal*>(param.second);
                        if(temp->getType()->isInt()) {
                            constIntSet.insert(temp->getInt());
                        }
                        else if(temp->getType()->isFloat()) {
                            constFloatSet.insert(temp->getFloat());
                        }
                    } else {
                        flag = false;
                        break;
                    }
                    if(constFloatSet.size() + constIntSet.size() > 1) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    phiIr->deleteIR();
                    if(constFloatSet.size() == 1 && constIntSet.size() == 0) {
                        TempVal temp;
                        temp.setFloat(*constFloatSet.begin());
                        temp.setType(new Type(TypeID::FLOAT));
                        auto& irs = bb->getIr();
                        auto newIr = StoreIRManager::getIR(phiIr->getOperands()[0]->getVal(), temp);
                        auto iter = find(irs.begin(), irs.end(), phiIr);
                        if(iter != irs.end()) {
                            *iter = newIr;
                        }
                    } else if(constIntSet.size() == 1 && constFloatSet.size() == 0) {
                        TempVal temp;
                        temp.setInt(*constIntSet.begin());
                        temp.setType(new Type(TypeID::INT));
                        auto& irs = bb->getIr();
                        auto newIr = StoreIRManager::getIR(phiIr->getOperands()[0]->getVal(), temp);
                        auto iter = find(irs.begin(), irs.end(), phiIr);
                        if(iter != irs.end()) {
                            *iter = newIr;
                        }
                    }
                }
            }

            if(typeid(*inst) == typeid(StoreIIR) && !inst->getOperands()[0]->getVal()->is_Array()) {
                StoreIIR* sir = dynamic_cast<StoreIIR*>(inst);
                TempVal* temp = dynamic_cast<TempVal*>(sir->getOperands()[1]->getVal());
                if(!temp->getVal() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), sir->getOperands()[0]->getVal()) == end(irVisitor->globalVars)) {
                    // if(temp->getType()->isInt()) {
                        sir->deleteIR();
                        Value* dst = sir->getOperands()[0]->getVal();
                        for(auto use : dst->getUses()) {
                            User* user = use->getUser();
                            if(typeid(*user) == typeid(PhiIR)) {
                                dynamic_cast<PhiIR*>(user)->params[use->getBB()] = temp;
                            } else {
                                std::vector<Use *> operands = user->getOperands();
                                operands[use->getArg()]->setVal(temp);
                            }
                            W.push_back(dynamic_cast<Instruction*>(user));
                        }
                    // }
                }
            } else if(typeid(*inst) == typeid(StoreFIR) && !inst->getOperands()[0]->getVal()->is_Array()) {
                StoreFIR* sir = dynamic_cast<StoreFIR*>(inst);
                TempVal* temp = dynamic_cast<TempVal*>(sir->getOperands()[1]->getVal());
                if(!temp->getVal() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), temp->getVal()) == end(irVisitor->globalVars)) {
                    // if(temp->getType()->isInt()) {
                        sir->deleteIR();
                        Value* dst = sir->getOperands()[0]->getVal();
                        for(auto use : dst->getUses()) {
                            User* user = use->getUser();
                            if(typeid(*user) == typeid(PhiIR)) {
                                dynamic_cast<PhiIR*>(user)->params[use->getBB()] = temp;
                            } else {
                                std::vector<Use *> operands = user->getOperands();
                                operands[use->getArg()]->setVal(temp);
                            }
                            W.push_back(dynamic_cast<Instruction*>(user));
                        }
                    // }
                }
            } else if(typeid(*inst) == typeid(LoadIIR)) {
                LoadIIR* lir = dynamic_cast<LoadIIR*>(inst);
                if(typeid(*(lir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                    lir->deleteIR();
                    TempVal* temp = dynamic_cast<TempVal*>(lir->getOperands()[1]->getVal());
                    Value* val = lir->getOperands()[0]->getVal();
                    for(auto use : val->getUses()) {
                        User* user = use->getUser();
                        if(typeid(*user) == typeid(PhiIR)) {
                            dynamic_cast<PhiIR*>(user)->params[use->getBB()] = temp;
                        } else {
                            std::vector<Use*> operands = user->getOperands();
                            operands[use->getArg()]->setVal(temp);
                        }
                        W.push_back(dynamic_cast<Instruction*>(user));
                    }
                }
            } else if(typeid(*inst) == typeid(LoadFIR)) {
                LoadFIR* lir = dynamic_cast<LoadFIR*>(inst);
                if(typeid(*(lir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                    lir->deleteIR();
                    TempVal* temp = dynamic_cast<TempVal*>(lir->getOperands()[1]->getVal());
                    Value* val = lir->getOperands()[0]->getVal();
                    for(auto use : val->getUses()) {
                        User* user = use->getUser();
                        if(typeid(*user) == typeid(PhiIR)) {
                            dynamic_cast<PhiIR*>(user)->params[use->getBB()] = temp;
                        } else {
                            std::vector<Use*> operands = user->getOperands();
                            operands[use->getArg()]->setVal(temp);
                        }
                        W.push_back(dynamic_cast<Instruction*>(user));
                    }
                }
            } else if(typeid(*inst) == typeid(CastInt2FloatIR)) {
                CastInt2FloatIR* i2fir = dynamic_cast<CastInt2FloatIR*>(inst);
                if(typeid(*(i2fir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                    i2fir->deleteIR();
                    TempVal* temp = dynamic_cast<TempVal*>(i2fir->getOperands()[1]->getVal());
                    TempVal* newTemp = new TempVal(*temp);
                    newTemp->setFloat(newTemp->getInt());
                    newTemp->setType(new Type(TypeID::FLOAT));

                    Value* val = i2fir->getOperands()[0]->getVal();
                    for(auto use : val->getUses()) {
                        User* user = use->getUser();
                        if(typeid(*user) == typeid(PhiIR)) {
                            dynamic_cast<PhiIR*>(user)->params[use->getBB()] = newTemp;
                        } else {
                            std::vector<Use*> operands = user->getOperands();
                            operands[use->getArg()]->setVal(newTemp);
                        }
                        W.push_back(dynamic_cast<Instruction*>(user));
                    }
                }
            } else if(typeid(*inst) == typeid(CastFloat2IntIR)) {
                CastFloat2IntIR* f2iir = dynamic_cast<CastFloat2IntIR*>(inst);
                if(typeid(*(f2iir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                    f2iir->deleteIR();
                    TempVal* temp = dynamic_cast<TempVal*>(f2iir->getOperands()[1]->getVal());
                    TempVal* newTemp = new TempVal(*temp);
                    newTemp->setInt(newTemp->getFloat());
                    newTemp->setType(new Type(TypeID::INT));

                    Value* val = f2iir->getOperands()[0]->getVal();
                    for(auto use : val->getUses()) {
                        User* user = use->getUser();
                        if(typeid(*user) == typeid(PhiIR)) {
                            dynamic_cast<PhiIR*>(user)->params[use->getBB()] = newTemp;
                        } else {
                            std::vector<Use*> operands = user->getOperands();
                            operands[use->getArg()]->setVal(newTemp);
                        }
                        W.push_back(dynamic_cast<Instruction*>(user));
                    }
                }
            } else if(typeid(*inst) == typeid(GEPIR)) {
                GEPIR* gepir = dynamic_cast<GEPIR*>(inst);
                if(gepir->getOperands()[2]->getVal() && typeid(*(gepir->getOperands()[2]->getVal())) == typeid(TempVal)) {
                    TempVal* temp = dynamic_cast<TempVal*>(gepir->getOperands()[2]->getVal());
                    gepir->v3 = nullptr;
                    gepir->arrayLen = temp->getConst();
                }
            }
        }
    }
}