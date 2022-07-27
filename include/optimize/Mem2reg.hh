//
// Created by hanyangchen on 22-6-30.
//

#include "IrVisitor.hh"
#include "Instruction.hh"
#include <map>
#include <stack>

class Mem2reg {
private:
    IrVisitor* irVisitor;
    Function* function;
    std::map<Value*, std::set<BasicBlock*>> defsites;
    std::map<BasicBlock*, std::set<Value*>> bbPhis;
    // std::map<Value*, int> counts;
    // std::map<Value*, std::stack<int>> stacks;
    // std::set<BasicBlock*> visitedBB;

    std::map<Value*, std::stack<Value*>> stk;
    std::map<Value*, Value*> count;
public:
    Mem2reg(IrVisitor* irVisitor) : irVisitor(irVisitor) {;}
    void execute();
    void rename(BasicBlock* bb);
    void getOriginVals();
    void placePhi();

    // void genDefUse();
    // void addPhiDefUse(BasicBlock* bb, Use* use);
    // void removeRedundantPhi();
    // void rename();
    // void addStartDefUse(BasicBlock* bb, Value* val, std::vector<Use*>* vec);
    // void broadcast(std::vector<Use*>* vec);
    // void removeAlloca();
    // void phiParamsBroadcast();
};

void Mem2reg::execute()
{
    std::vector<Function*> functions = irVisitor->getFunctions();
    for(Function* func : functions) {
        if(func->getBB().size() == 0) continue;

        this->function = func;
        defsites.clear();
        bbPhis.clear();
        // counts.clear();
        // stacks.clear();

        stk.clear();
        count.clear();

        // genDefUse();
        getOriginVals();
        placePhi();
        rename(func->basicBlocks[0]);
        // removeAlloca();
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
                if(function->allocaVars.count(operands[1]->getVal())) {
                    bb->originVals.insert(operands[1]->getVal());
                }
            }
        }
    }
}

// void Mem2reg::genDefUse() {
//     for(auto bb : function->getBB()) {
//         auto& irs = bb->getIr();
//         for(int i(0); i < irs.size(); i++) {
//             // auto type = typeid(*irs[i]);
//             if(typeid(*irs[i]) != typeid(BreakIR) && typeid(*irs[i]) != typeid(ContinueIR) && typeid(*irs[i]) != typeid(JumpIR)) {
//                 if((typeid(*irs[i]) == typeid(AllocIIR) || typeid(*irs[i]) == typeid(AllocFIR)) && !irs[i]->is_Array()) {
//                     auto operands = irs[i]->getOperands();
//                     std::vector<Use*>* vec = new std::vector<Use*>(1, operands[0]);
//                     std::pair<Value*, std::vector<Use*>*> p(operands[0]->getVal(), vec);
//                     bb->defuse[operands[0]->getVal()].push_back(p);
//                     function->allocaVars.insert(operands[0]->getVal());
//                 }
//                 else if(typeid(*irs[i]) == typeid(StoreIIR) || typeid(*irs[i]) == typeid(StoreFIR)) {
//                     auto operands = irs[i]->getOperands();
//                     if(function->allocaVars.count(operands[0]->getVal())) {
//                         // 为了将Alloca和Store进行合并
//                         if(bb->defuse[operands[0]->getVal()].size() == 1 && \
//                             (typeid(*((*(bb->defuse[operands[0]->getVal()][0].second))[0]->getUser())) == typeid(AllocFIR) || \
//                             typeid(*((*(bb->defuse[operands[0]->getVal()][0].second))[0]->getUser())) == typeid(AllocIIR))) {
//                                 bb->defuse[operands[0]->getVal()][0].second->push_back(operands[0]);
//                         }
//                         else {
//                             std::vector<Use*>* vec = new std::vector<Use*>(1, operands[0]);
//                             std::pair<Value*, std::vector<Use*>*> p(operands[0]->getVal(), vec);
//                             bb->defuse[operands[0]->getVal()].push_back(p);
//                         }
//                     }
//                 }
//                 else {
//                     auto operands = irs[i]->getOperands();
//                     for(auto operand : operands) {
//                         if(bb->defuse.count(operand->getVal())) {
//                             auto top = bb->defuse[operand->getVal()].rbegin();
//                             top->second->push_back(operand);
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }

// void Mem2reg::addStartDefUse(BasicBlock* bb, Value* val, std::vector<Use*>* vec) {
//     if(visitedBB.count(bb)) return;
//     else visitedBB.insert(bb);

//     auto& irs = bb->getIr();
//     for(int i(0); i < irs.size(); i++) {
//         // auto type = typeid(*irs[i]);
//         if(typeid(*irs[i]) != typeid(BreakIR) && typeid(*irs[i]) != typeid(ContinueIR) && typeid(*irs[i]) != typeid(JumpIR)) {
//             if((typeid(*irs[i]) == typeid(AllocIIR) || typeid(*irs[i]) == typeid(AllocFIR)) && !irs[i]->is_Array()) {
//                 continue;
//             }
//             else if(typeid(*irs[i]) == typeid(StoreIIR) || typeid(*irs[i]) == typeid(StoreFIR) || typeid(*irs[i]) == typeid(PhiIR)) {
//                 auto operands = irs[i]->getOperands();
//                 if(val == operands[0]->getVal()) {
//                     return;
//                 }
//             }
//             else {
//                 auto operands = irs[i]->getOperands();
//                 for(auto operand : operands) {
//                     if(val == operand->getVal()) {
//                         vec->push_back(operand);
//                     }
//                 }
//             }
//         }
//     }
    
//     for(auto succBB : bb->getSucc()) {
//         addStartDefUse(succBB, val, vec);
//     }
// }

// void Mem2reg::addPhiDefUse(BasicBlock* bb, Use* use) {
//     std::vector<Use*>* vec = new std::vector<Use*>(1, use);
//     std::pair<Value*, std::vector<Use*>*> p(use->getVal(), vec);

//     for(auto ir : bb->getIr()) {
//         if((typeid(*ir) == typeid(StoreIIR) || typeid(*ir) == typeid(StoreFIR) || typeid(*ir) == typeid(PhiIR)) && ir->getOperands()[0]->getVal() == use->getVal()) {
//             break;
//         }
//         else {
//             auto operands = ir->getOperands();
//             for(auto operand : operands) {
//                 if(operand->getVal() == use->getVal()) {
//                     p.second->push_back(operand);
//                 }
//             }
//         }
//     }

//     bb->defuse[use->getVal()].insert(bb->defuse[use->getVal()].begin(), p);
// }

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
                    // this->addPhiDefUse(dfBB, phiIr->getOperands()[0]);
                    dfBB->ir.insert(dfBB->ir.begin(), phiIr);
                    bbPhis[dfBB].insert(defsite.first);

                    // // 将Phi结点中所需的参数加入对应use
                    // auto preBBs = dfBB->getPre();
                    // for(int i(0); i < preBBs.size(); i++) {
                    //     if(preBBs[i]->defuse.count(defsite.first)) {
                    //         Use* use = new Use(defsite.first, phiIr, i);
                    //         preBBs[i]->defuse[defsite.first].rbegin()->second->push_back(use);
                    //     }
                    // }

                    if(!bb->originVals.count(defsite.first)) {
                        W.insert(dfBB);
                    }

                    // // 查找是否存在相同的变量，bb的var可改进为set
                    // bool flag(false);
                    // for(auto& def : bb->defuse) {
                    //     if(def.first == defsite.first) {
                    //         flag = true;
                    //         break;
                    //     }
                    // }
                    // if(!flag) {
                    //     W.insert(dfBB);
                    // }
                    // if(bb->getVar().(defsite.first))
                }
            }
        }
    }

    // for(BasicBlock* bb : function->getBB()) {
    //     visitedBB.clear();

    //     for(auto& defuse : bb->defuse) {
    //         for(auto succBB : bb->getSucc()) {
    //             addStartDefUse(succBB, defuse.first, defuse.second[defuse.second.size() - 1].second);
    //         }
    //     }
    // }
}

// void Mem2reg::rename() {
//     for(auto bb : function->getBB()) {
//         for(auto& defuse : bb->defuse) {
//             for(int i(0); i < defuse.second.size(); i++) {
//                 std::vector<Use*>* vec(defuse.second[i].second);
//
//                 if(i == 0 && vec->size() >= 1 && (typeid(*(((*vec)[0])->getUser())) == typeid(AllocIIR) || typeid(*(((*vec)[0])->getUser())) == typeid(AllocFIR)))
//                     continue;
//
//                 Value* val;
//                 if(typeid(*(defuse.second[i].first)) == typeid(VarValue)) {
//                     val = new VarValue(*(dynamic_cast<VarValue*>(defuse.second[i].first)));
//                 } else if(typeid(*(defuse.second[i].first)) == typeid(TempVal)) {
//                     val = new TempVal(*(dynamic_cast<TempVal*>(defuse.second[i].first)));
//                 } else if(typeid(*(defuse.second[i].first)) == typeid(ConstValue)) {
//                     val = new ConstValue(*(dynamic_cast<ConstValue*>(defuse.second[i].first)));
//                 }
//                 val->setNum(function->varCnt++);
//
//                 for(int i(0); i < vec->size(); i++) {
//                     // Instruction* inst = dynamic_cast<Instruction*>((*vec)[i]->getUser());
//                     (*vec)[i]->setVal(val);
//                 }
//
//                 std::pair<Value*, std::vector<Use*>*> p(val, vec);
//                 defuse.second[i].swap(p);
//             }
//         }
//     }
//
//     // phiParamsBroadcast();
//
//     for(auto bb : function->getBB()) {
//         for(auto& defuse : bb->defuse) {
//             for(auto iter(defuse.second.begin()); iter != defuse.second.end();) {
//                 std::vector<Use*>* vec(iter->second);
//                 if(vec && vec->size() > 0 && typeid(*(*vec)[0]->getUser()) == typeid(PhiIR)) {
//                     if(vec->size() == 1) {
//                         PhiIR* phiIR = dynamic_cast<PhiIR*>((*vec)[0]->getUser());
//                         phiIR->deleteIR();
//
//                         for(auto& param : phiIR->params) {
//                             if(param.first->defuse.count(param.second)) {                                    
//                                 std::vector<Use*>* paramVec = param.first->defuse[param.second].rbegin()->second;
//                                 paramVec->pop_back();
//                             }
//                         }
//
//                         defuse.second.erase(iter);
//                     }
//                     else {
//                         PhiIR* phiIR = dynamic_cast<PhiIR*>((*vec)[0]->getUser());
//                         for(auto& param : phiIR->params) {
//                             if(param.first->defuse.count(param.second)) {                                    
//                                 param.second = param.first->defuse[param.second].rbegin()->first;
//                                 // std::vector<Use*>* paramVec = param.first->defuse[param.second].rbegin()->second;
//                                 // // 替换定值变量
//                                 // int i(0);
//                                 // if(typeid(*(((*paramVec)[i])->getUser())) == typeid(AllocIIR) || typeid(*(((*paramVec)[i])->getUser())) == typeid(AllocFIR)) i++;
//                            
//                                 // Value* val = param.first->defuse[param.second].rbegin()->first;
//                                 // if(paramVec->size() > i && (typeid(*(((*paramVec)[i])->getUser())) == typeid(StoreIIR) || typeid(*(((*paramVec)[i])->getUser())) == typeid(StoreFIR))) {
//                                 //     TempVal* src = dynamic_cast<TempVal*>(((*paramVec)[i])->getUser()->getOperands()[1]->getVal());
//                                 //     if(!src->getVal()) {
//                                 //         paramVec->pop_back();
//                                 //         val = src;
//                                 //     }
//                                 // }
//                                 // param.second = val;
//                             } else {
//                                 param.second = nullptr;
//                             }
//                         }
//                         iter++;
//                     }
//                 }
//                 else iter++;
//             }
//         }
//     }
// }

void Mem2reg::rename(BasicBlock* bb) {
    std::map<Value*, int> valCnt;

    for(auto ir : bb->getIr()) {
        auto& operands = ir->getOperands();
        if(typeid(*ir) != typeid(PhiIR)) {
            for(int i(1); i < operands.size(); i++) {
                if(operands[i]->getVal()) {
                    if(typeid(*(operands[i]->getVal())) != typeid(TempVal)) {
                        if(stk[operands[i]->getVal()].size() != 0) {
                            Value* newVal = stk[operands[i]->getVal()].top();
                            operands[i]->setVal(newVal);
                        } else {
                            stk[operands[i]->getVal()].push(operands[i]->getVal());
                        }
                    } else {
                        TempVal* temp = dynamic_cast<TempVal*>((operands[i]->getVal()));
                        if(temp->getVal()) {
                            if(stk[temp->getVal()].size() != 0) {
                                Value* newVal = stk[temp->getVal()].top();
                                TempVal* newTempVal = new TempVal();
                                newTempVal->setVal(newVal);
                                operands[i]->setVal(newTempVal);
                            } else {
                                stk[temp->getVal()].push(temp);
                            }
                        }
                    }
                }
            }
        }
        
        if(operands.size() > 0 && operands[0]->getVal()) {
            Value* val = operands[0]->getVal(), *newVal = nullptr;
            if(typeid(*(val)) == typeid(VarValue)) {
                newVal = new VarValue(*dynamic_cast<VarValue*>(val));
                newVal->setNum(function->varCnt++);
            }
            else if(typeid(*val) == typeid(ConstValue)) {
                newVal = new ConstValue(*dynamic_cast<ConstValue*>(val));
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
                if(stk[phiIr->params[bb]].size() != 0) {
                    phiIr->params[bb] = stk[phiIr->params[bb]].top();
                } else {
                    stk[phiIr->params[bb]].push(phiIr->params[bb]);
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

// void Mem2reg::removeAlloca() {
//     for(auto& bb : function->getBB()) {
//         for(auto& defuse : bb->defuse) {
//             for(auto iter(defuse.second.begin()); iter != defuse.second.end();) {
//                 std::vector<Use*>* vec(iter->second);
//                 if(vec->size() == 1) {
//                     dynamic_cast<Instruction*>(((*vec)[0])->getUser())->deleteIR();
//                     defuse.second.erase(iter);
//                 } else if(vec->size() == 2 && (typeid(*(((*vec)[0])->getUser())) == typeid(AllocIIR) || typeid((*((*vec)[0])->getUser())) == typeid(AllocFIR))){
//                     dynamic_cast<Instruction*>(((*vec)[0])->getUser())->deleteIR();
//                     dynamic_cast<Instruction*>(((*vec)[1])->getUser())->deleteIR();
//                     defuse.second.erase(iter);
//                 }
//                 else iter++;
//             }
//         }
//     }
// }
