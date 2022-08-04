//
// Created by hanyangchen on 22-6-30.
//

#ifndef SYSY2022_BJTU_MEM2REG_HH
#define SYSY2022_BJTU_MEM2REG_HH

#include "IrVisitor.hh"
#include "Instruction.hh"
#include "IRManager.hh"
#include <map>
#include <stack>
// #include <algorithm>

class Mem2reg {
private:
    IrVisitor* irVisitor;
    Function* function;
    std::map<Value*, std::set<BasicBlock*>> defsites;
    std::map<BasicBlock*, std::set<Value*>> bbPhis;
    std::map<Value*, std::stack<Value*>> stk;
    std::map<Value*, Value*> count;
    std::map<Value*, Instruction*> allVars;
public:
    Mem2reg(IrVisitor* irVisitor) : irVisitor(irVisitor) {;}
    void execute();
    void rename(BasicBlock* bb);
    void getOriginVals();
    void placePhi();
    void constValBroadcast();
    void removeDeadcode();
    void publicExp();
    void copyBroadcast();
    std::vector<std::vector<Instruction*>::iterator>* findPublicExp(std::vector<Instruction*>::iterator iter, std::vector<Instruction*>::iterator end);
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
    removeDeadcode();

    allVars.clear();
    for(Function* func : functions) {
        if(func->getBB().size() == 0) continue;
        this->function = func;

        copyBroadcast();
        // publicExp();
    }
    // removeDeadcode();
}

void Mem2reg::getOriginVals() {
    for(auto bb : function->getBB()) {
        for(auto ir : bb->getIr()) {
            if(!ir->isDeleted()) {
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
        if(ir->isDeleted() || operands.size() <= 0) continue;
        if(typeid(*ir) != typeid(PhiIR)) {
            for(int i(1); i < operands.size(); i++) {
                if(operands[i]->getVal() && !operands[i]->getVal()->is_Array() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), operands[i]->getVal()) == end(irVisitor->globalVars)) {
                    if(typeid(*(operands[i]->getVal())) != typeid(TempVal)) {
                        if(stk[operands[i]->getVal()].size() != 0) {
                            Value* newVal = stk[operands[i]->getVal()].top();
                            if(typeid(*newVal) == typeid(TempVal)) {
                                TempVal* temp = dynamic_cast<TempVal*>(newVal);
                                // operands[i]->setVal(temp->getVal());

                                Use* use = new Use(temp->getVal(), ir, i);
                                operands[i] = use;
                                temp->getVal()->addUse(use);
                            }
                            else {
                                // operands[i]->setVal(newVal);

                                Use* use = new Use(newVal, ir, i);
                                operands[i] = use;
                                newVal->addUse(use);
                            }
                        } else {
                            stk[operands[i]->getVal()].push(operands[i]->getVal());

                            Use* use = new Use(operands[i]->getVal(), ir, i);
                            operands[i] = use;
                            operands[i]->getVal()->addUse(use);
                        }
                    } else {
                        TempVal* temp = dynamic_cast<TempVal*>((operands[i]->getVal()));
                        if(temp->getVal()) {
                            if(stk[temp->getVal()].size() != 0) {
                                Value* newVal = stk[temp->getVal()].top();
                                if(typeid(*newVal) == typeid(TempVal)) {
                                    // operands[i]->setVal(newVal);
                                    
                                    Use* use = new Use(newVal, ir, i);
                                    operands[i] = use;
                                    dynamic_cast<TempVal*>(newVal)->getVal()->addUse(use);
                                } else {
                                    TempVal* newTempVal = new TempVal();
                                    newTempVal->setVal(newVal);
                                    // operands[i]->setVal(newTempVal);

                                    Use* use = new Use(newTempVal, ir, i);
                                    operands[i] = use;
                                    newVal->addUse(use);
                                }
                            } else {
                                stk[temp->getVal()].push(temp);
                                
                                Use* use = new Use(temp, ir, i);
                                operands[i] = use;
                                temp->getVal()->addUse(use);
                            }
                        }
                    }
                }
            }
        }
        
        if(operands.size() > 0 && operands[0]->getVal() && !operands[0]->getVal()->is_Array() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), operands[0]->getVal()) == end(irVisitor->globalVars)) {
            Value* val = operands[0]->getVal(), *newVal = nullptr;
            if(typeid(*(val)) == typeid(VarValue)) {
                newVal = new VarValue(*dynamic_cast<VarValue*>(val));
                newVal->clearUses();
                newVal->setNum(function->varCnt++);

                allVars[newVal] = ir;
            }
            else if(typeid(*val) == typeid(ConstValue)) {
                newVal = new ConstValue(*dynamic_cast<ConstValue*>(val));
                newVal->clearUses();
                newVal->setNum(function->varCnt++);

                allVars[newVal] = ir;
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

                allVars[tempNewVal] = ir;
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
            if(ir->isDeleted()) continue;
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
                                phiIr->addOperand(use);
                            }
                        } else {
                            Use* use = new Use(phiIr->params[bb], phiIr, bb);
                            phiIr->params[bb]->addUse(use);
                            phiIr->addOperand(use);
                        }
                    } else {
                        stk[phiIr->params[bb]].push(phiIr->params[bb]);

                        Use* use = new Use(phiIr->params[bb], phiIr, bb);
                        phiIr->params[bb]->addUse(use);
                        phiIr->addOperand(use);
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

            if(!inst->isDeleted()) {
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
                                allVars[phiIr->getOperands()[0]->getVal()] = newIr;
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
                                allVars[phiIr->getOperands()[0]->getVal()] = newIr;
                            }
                        }
                    }

                    
                }

                if(typeid(*inst) == typeid(StoreIIR) && !inst->getOperands()[0]->getVal()->is_Array()) {
                    StoreIIR* sir = dynamic_cast<StoreIIR*>(inst);
                    TempVal* temp = dynamic_cast<TempVal*>(sir->getOperands()[1]->getVal());
                    if(find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), sir->getOperands()[0]->getVal()) == end(irVisitor->globalVars)) {
                        if(!temp->getVal()) {
                            // if(temp->getType()->isInt()) {
                            sir->deleteIR();

                            Value* dst = sir->getOperands()[0]->getVal();
                            for(auto use : dst->getUses()) {
                                if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                    use->getVal()->killUse(use);
                                }

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
                        
                        // 此处混杂了拷贝传播
                        else if(temp->getVal()) {
                            // sir->deleteIR();

                            Value* dst = sir->getOperands()[0]->getVal();
                            for(auto use : dst->getUses()) {
                                User* user = use->getUser();
                                if(typeid(*user) == typeid(PhiIR)) {
                                    if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                        use->getVal()->killUse(use);
                                    }
                                    Use* newUse = new Use(temp->getVal(), user, use->getBB());
                                    temp->getVal()->addUse(newUse);
                                    dynamic_cast<PhiIR*>(user)->params[use->getBB()] = temp;
                                }
                            }
                        }
                    }
                } else if(typeid(*inst) == typeid(StoreFIR) && !inst->getOperands()[0]->getVal()->is_Array()) {
                    StoreFIR* sir = dynamic_cast<StoreFIR*>(inst);
                    TempVal* temp = dynamic_cast<TempVal*>(sir->getOperands()[1]->getVal());
                    if(find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), sir->getOperands()[0]->getVal()) == end(irVisitor->globalVars)) {
                        if(!temp->getVal()) {
                            // if(temp->getType()->isInt()) {
                            sir->deleteIR();

                            Value* dst = sir->getOperands()[0]->getVal();
                            for(auto use : dst->getUses()) {
                                if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                    use->getVal()->killUse(use);
                                }

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
                        else if(temp->getVal()) {
                            // sir->deleteIR();

                            Value* dst = sir->getOperands()[0]->getVal();
                            for(auto use : dst->getUses()) {
                                User* user = use->getUser();
                                if(typeid(*user) == typeid(PhiIR)) {
                                    if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                        use->getVal()->killUse(use);
                                    }
                                    Use* newUse = new Use(temp->getVal(), user, use->getBB());
                                    temp->getVal()->addUse(newUse);
                                    dynamic_cast<PhiIR*>(user)->params[use->getBB()] = temp;
                                }
                            }
                        }
                    }
                } else if(typeid(*inst) == typeid(LoadIIR)) {
                    LoadIIR* lir = dynamic_cast<LoadIIR*>(inst);
                    if(typeid(*(lir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                        lir->deleteIR();

                        TempVal* temp = dynamic_cast<TempVal*>(lir->getOperands()[1]->getVal());
                        Value* val = lir->getOperands()[0]->getVal();
                        for(auto use : val->getUses()) {
                            if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                use->getVal()->killUse(use);
                            }

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
                            if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                use->getVal()->killUse(use);
                            }

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
                            if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                use->getVal()->killUse(use);
                            }

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
                            if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                use->getVal()->killUse(use);
                            }

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
                } else if(typeid(*inst) == typeid(AddIIR) || typeid(*inst) == typeid(SubIIR) || typeid(*inst) == typeid(MulIIR) \
                        || typeid(*inst) == typeid(DivIIR) || typeid(*inst) == typeid(ModIR) || typeid(*inst) == typeid(LTIIR) \
                        || typeid(*inst) == typeid(LEIIR) || typeid(*inst) == typeid(GTIIR) || typeid(*inst) == typeid(GEIIR) \
                        || typeid(*inst) == typeid(EQUIIR) || typeid(*inst) == typeid(NEIIR)) {
                    auto operands = inst->getOperands();
                    TempVal* res = dynamic_cast<TempVal*>(operands[0]->getVal()), *left = dynamic_cast<TempVal*>(operands[1]->getVal()), *right = dynamic_cast<TempVal*>(operands[2]->getVal());
                    if(!left->getVal() && !right->getVal()) {
                        inst->deleteIR();
                        int leftInt = left->getConst(), rightInt = right->getConst(), resultInt = 0;
                        std::string op = dynamic_cast<ArithmeticIR*>(inst)->op;

                        if(op == "+") {
                            resultInt = leftInt + rightInt;
                        } else if(op == "-") {
                            resultInt = leftInt - rightInt;
                        } else if(op == "*") {
                            resultInt = leftInt * rightInt;
                        } else if(op == "/") {
                            resultInt = leftInt / rightInt;
                        } else if(op == "%") {
                            resultInt = leftInt % rightInt;
                        } else if(op == "<") {
                            resultInt = leftInt < rightInt;
                        } else if(op == "<=") {
                            resultInt = leftInt <= rightInt;
                        } else if(op == ">") {
                            resultInt = leftInt > rightInt;
                        } else if(op == ">=") {
                            resultInt = leftInt >= rightInt;
                        } else if(op == "==") {
                            resultInt = leftInt == rightInt;
                        } else if(op == "!=") {
                            resultInt = leftInt != rightInt;
                        }

                        TempVal* newTemp = new TempVal();
                        newTemp->setInt(resultInt);
                        newTemp->setType(new Type(TypeID::INT));
                        
                        Value* val = res->getVal();
                        for(auto use : val->getUses()) {
                            if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                use->getVal()->killUse(use);
                            }

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
                } else if(typeid(*inst) == typeid(AddFIR) || typeid(*inst) == typeid(SubFIR) || typeid(*inst) == typeid(MulFIR) \
                        || typeid(*inst) == typeid(DivFIR) || typeid(*inst) == typeid(LTFIR) || typeid(*inst) == typeid(LEFIR) \
                        || typeid(*inst) == typeid(GTFIR) || typeid(*inst) == typeid(GEFIR) || typeid(*inst) == typeid(EQUFIR) \
                        || typeid(*inst) == typeid(NEFIR)) {
                    auto operands = inst->getOperands();
                    TempVal* res = dynamic_cast<TempVal*>(operands[0]->getVal()), *left = dynamic_cast<TempVal*>(operands[1]->getVal()), *right = dynamic_cast<TempVal*>(operands[2]->getVal());
                    if(!left->getVal() && !right->getVal()) {
                        inst->deleteIR();
                        float leftFloat = left->getConst(), rightFloat = right->getConst(), resultFloat = 0;
                        std::string op = dynamic_cast<ArithmeticIR*>(inst)->op;

                        if(op == "+") {
                            resultFloat = leftFloat + rightFloat;
                        } else if(op == "-") {
                            resultFloat = leftFloat - rightFloat;
                        } else if(op == "*") {
                            resultFloat = leftFloat * rightFloat;
                        } else if(op == "/") {
                            resultFloat = leftFloat / rightFloat;
                        } else if(op == "<") {
                            resultFloat = leftFloat < rightFloat;
                        } else if(op == "<=") {
                            resultFloat = leftFloat <= rightFloat;
                        } else if(op == ">") {
                            resultFloat = leftFloat > rightFloat;
                        } else if(op == ">=") {
                            resultFloat = leftFloat >= rightFloat;
                        } else if(op == "==") {
                            resultFloat = leftFloat == rightFloat;
                        } else if(op == "!=") {
                            resultFloat = leftFloat != rightFloat;
                        }

                        TempVal* newTemp = new TempVal();
                        newTemp->setFloat(resultFloat);
                        newTemp->setType(new Type(TypeID::FLOAT));
                        
                        Value* val = res->getVal();
                        for(auto use : val->getUses()) {
                            if(typeid(*(use->getVal())) != typeid(TempVal)) {
                                use->getVal()->killUse(use);
                            }

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
                } else if(typeid(*inst) == typeid(ReturnIR)) {
                    ReturnIR* rir = dynamic_cast<ReturnIR*>(inst);
                    if(rir->getOperands()[1]->getVal() && typeid(*(rir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                        TempVal* temp = dynamic_cast<TempVal*>(rir->getOperands()[1]->getVal());
                        if(temp->getType()->isInt()) {
                            rir->retInt = temp->getInt();
                            rir->useInt = true;
                            rir->v = nullptr;
                        } else if(temp->getType()->isFloat()) {
                            rir->retFloat = temp->getFloat();
                            rir->useFloat = true;
                            rir->v = nullptr;
                        }
                    }
                } else if(typeid(*inst) == typeid(BranchIR)) {
                    BranchIR* bir = dynamic_cast<BranchIR*>(inst);
                    if(bir->getOperands()[1]->getVal() && typeid(*(bir->getOperands()[1]->getVal())) == typeid(TempVal)) {
                        int cond = dynamic_cast<TempVal*>(bir->getOperands()[1]->getVal())->getConst();
                        auto& irs = bb->getIr();
                        Instruction* newIr = nullptr;
                        auto irIter = find(irs.begin(), irs.end(), bir);
                        auto bbIter = find(function->basicBlocks.begin(), function->basicBlocks.end(), bb);
                        if(irIter != irs.end() && cond) {
                            if(*(bbIter + 1) == bir->trueTarget) {
                                bir->deleteIR();
                            } else {
                                newIr = new JumpIR(bir->trueTarget);
                                *irIter = newIr;
                            }
                        } else if(irIter != irs.end() && !cond) {
                            if(*(bbIter + 1) == bir->falseTarget) {
                                bir->deleteIR();
                            } else {
                                newIr = new JumpIR(bir->falseTarget);
                                *irIter = newIr;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Mem2reg::removeDeadcode() {
    auto W = allVars;
    while(!W.empty()) {
        Value* var = W.begin()->first;
        Instruction* inst = W.begin()->second;
        W.erase(var);

        if(var->getUses().empty() && !inst->isDeleted()) {
            inst->deleteIR();
            auto operands = inst->getOperands();
            for(int i(1); i < operands.size(); i++) {
                Value* useVal = operands[i]->getVal();
                if(typeid(*useVal) == typeid(TempVal)) {
                    useVal = dynamic_cast<TempVal*>(useVal)->getVal();
                }
                if(useVal) {
                    useVal->killUse(operands[i]);
                    if(allVars.count(useVal)) W[useVal] = allVars[useVal];
                }
            }
        }
    }
}

// 有问题
std::vector<std::vector<Instruction*>::iterator>* Mem2reg::findPublicExp(std::vector<Instruction*>::iterator iter, std::vector<Instruction*>::iterator end) {
    ArithmeticIR* inst = dynamic_cast<ArithmeticIR*>(*(iter++));
    TempVal* left = dynamic_cast<TempVal*>(inst->getOperands()[1]->getVal()), *right = dynamic_cast<TempVal*>(inst->getOperands()[2]->getVal());
    std::vector<std::vector<Instruction*>::iterator>* vec = new std::vector<std::vector<Instruction*>::iterator>();

    for(; iter != end; iter++) {
        if(dynamic_cast<ArithmeticIR*>(*iter)) {
            ArithmeticIR* iterInst = dynamic_cast<ArithmeticIR*>(*iter);
            TempVal* iterLeft = dynamic_cast<TempVal*>(iterInst->getOperands()[1]->getVal()), *iterRight = dynamic_cast<TempVal*>(iterInst->getOperands()[2]->getVal());
            
            if(!left->getVal() && !iterLeft->getVal() && left->getConst() == iterLeft->getConst() && !right->getVal() && !iterRight->getVal() && right->getConst() == iterRight->getConst()) {
                vec->push_back(iter);
            }
            else if(left->getVal() && iterLeft->getVal() && left->getVal() == iterLeft->getVal() && right->getVal() && iterRight->getVal() && right->getVal() == iterRight->getVal()) {
                vec->push_back(iter);
            }
            else if(!left->getVal() && !iterLeft->getVal() && left->getConst() == iterLeft->getConst() && right->getVal() && iterRight->getVal() && right->getVal() == iterRight->getVal()) {
                vec->push_back(iter);
            }
            else if(left->getVal() && iterLeft->getVal() && left->getVal() == iterLeft->getVal() && !right->getVal() && !iterRight->getVal() && right->getConst() == iterRight->getConst()) {
                vec->push_back(iter);
            }

            if(typeid(*iter) == typeid(AddIIR) && typeid(*iter) == typeid(AddFIR) && typeid(*iter) == typeid(MulIIR) && typeid(*iter) == typeid(MulFIR)) {
                if(!left->getVal() && !iterLeft->getVal() && !right->getVal() && !iterRight->getVal() && left->getConst() == iterRight->getConst() && right->getConst() == iterLeft->getConst()) {
                    vec->push_back(iter);
                }
                else if(left->getVal() && iterLeft->getVal() && right->getVal() && iterRight->getVal() && left->getVal() == iterRight->getVal() && right->getVal() == iterLeft->getVal()) {
                    vec->push_back(iter);
                }
            }
        }
    }

    return vec;
}

void Mem2reg::publicExp() {
    for(auto bb : function->getBB()) {
        auto& irs = bb->getIr();
        for(auto iter(irs.begin()); iter != irs.end(); iter++) {
            if(dynamic_cast<ArithmeticIR*>(*iter)) {
                auto vec = findPublicExp(iter, irs.end());
                if(vec->empty()) continue;

                TempVal* dst = dynamic_cast<TempVal*>((*iter)->getOperands()[0]->getVal());
                for(auto aimIter : *vec) {
                    ArithmeticIR* inst = dynamic_cast<ArithmeticIR*>(*(aimIter));
                    TempVal* aimDst = dynamic_cast<TempVal*>(inst->getOperands()[0]->getVal()), *left = dynamic_cast<TempVal*>(inst->getOperands()[1]->getVal()), *right = dynamic_cast<TempVal*>(inst->getOperands()[2]->getVal());
                    if(left->getVal()) {
                        left->getVal()->killUse((*aimIter)->getOperands()[1]);
                    }
                    if(right->getVal()) {
                        right->getVal()->killUse((*aimIter)->getOperands()[2]);
                    }

                    for(auto use : aimDst->getVal()->getUses()) {
                        User* user = use->getUser();
                        std::vector<Use*> operands = user->getOperands();

                        if(typeid(*(use->getVal())) != typeid(TempVal)) {
                            use->getVal()->killUse(use);
                        }
                        else if(dynamic_cast<TempVal*>(use->getVal())->getVal()) {
                            dynamic_cast<TempVal*>(use->getVal())->getVal()->killUse(use);
                        }

                        if(typeid(*user) == typeid(PhiIR)) {
                            dynamic_cast<PhiIR*>(user)->params[use->getBB()] = dst;
                        }
                        else operands[use->getArg()]->setVal(dst);
                    }
                }
            }
        }
    }
}

void Mem2reg::copyBroadcast() {
    for(auto bb : function->getBB()) {
        auto W = bb->getIr();
        while(!W.empty()) {
            auto inst = *W.rbegin();
            W.pop_back();

            if(inst->isDeleted()) continue;
            if(typeid(*inst) == typeid(PhiIR)) {
                PhiIR* phiIr = dynamic_cast<PhiIR*>(inst);
                Value* dst = phiIr->getOperands()[0]->getVal();
                Value* newDst = nullptr;
                if(typeid(*(dst)) == typeid(VarValue)) {
                    newDst = new VarValue(*dynamic_cast<VarValue*>(dst));
                    if(typeid(*(phiIr->params.begin()->second)) == typeid(TempVal)) {
                        if(dynamic_cast<TempVal*>(phiIr->params.begin()->second)->getVal()) {
                            newDst->setType(dynamic_cast<TempVal*>(phiIr->params.begin()->second)->getVal()->getType());
                        } else {
                            newDst->setType(dynamic_cast<TempVal*>(phiIr->params.begin()->second)->getType());
                        }
                    }
                    else newDst->setType(phiIr->params.begin()->second->getType());
                    newDst->setNum(function->varCnt++);
                }
                else if(typeid(*dst) == typeid(ConstValue)) {
                    newDst = new ConstValue(*dynamic_cast<ConstValue*>(dst));
                    if(typeid(*(phiIr->params.begin()->second)) == typeid(TempVal)) {
                        if(dynamic_cast<TempVal*>(phiIr->params.begin()->second)->getVal()) {
                            newDst->setType(dynamic_cast<TempVal*>(phiIr->params.begin()->second)->getVal()->getType());
                        } else {
                            newDst->setType(dynamic_cast<TempVal*>(phiIr->params.begin()->second)->getType());
                        }
                    }
                    else newDst->setType(phiIr->params.begin()->second->getType());
                    newDst->setNum(function->varCnt++);
                }

                for(auto use : dst->getUses()) {
                    if(typeid(*(use->getVal())) != typeid(TempVal)) {
                        use->getVal()->killUse(use);
                    }
                    else if(dynamic_cast<TempVal*>(use->getVal())->getVal()) {
                        dynamic_cast<TempVal*>(use->getVal())->getVal()->killUse(use);
                    }

                    User* user = use->getUser();
                    dynamic_cast<Instruction*>(user)->deleteIR();
                    auto operands = user->getOperands();
                    if(operands[0]->getVal()) {
                        for(auto nextUse : operands[0]->getVal()->getUses()) {
                            if(typeid(*(nextUse->getVal())) != typeid(TempVal)) {
                                nextUse->getVal()->killUse(nextUse);
                            }

                            auto val = nextUse->getVal();
                            if(dynamic_cast<TempVal*>(val)) {
                                for(auto nextNextUse : dynamic_cast<TempVal*>(val)->getVal()->getUses()) {
                                    if(typeid(*(nextNextUse->getVal())) == typeid(TempVal)) {
                                        dynamic_cast<TempVal*>(nextNextUse->getVal())->setVal(newDst);
                                    }
                                    else nextNextUse->setVal(newDst);
                                    newDst->addUse(nextNextUse);
                                }
                                // newDst->Uses.insert(dynamic_cast<TempVal*>(val)->getVal()->getUses().begin(), dynamic_cast<TempVal*>(val)->getVal()->getUses().end())
                            }
                            else {
                                for(auto nextNextUse : val->getUses()) {
                                    if(typeid(*(nextNextUse->getVal())) == typeid(TempVal)) {
                                        dynamic_cast<TempVal*>(nextNextUse->getVal())->setVal(newDst);
                                    }
                                    else nextNextUse->setVal(newDst);
                                    newDst->addUse(nextNextUse);
                                }
                                // newDst->Uses.insert(val->getUses().begin(), val->getUses().end())
                            }
                        }
                    }
                }

                auto& operands = phiIr->getOperands();
                operands[0]->setVal(newDst);
            }
            // else if(dynamic_cast<StoreIR*>(inst) && !inst->getOperands()[0]->getVal()->is_Array()) {
            //     StoreIR* sir = dynamic_cast<StoreIR*>(inst);
            //     TempVal* temp = dynamic_cast<TempVal*>(sir->getOperands()[1]->getVal());
                
            //     if(temp->getVal() && find(irVisitor->globalVars.begin(), irVisitor->globalVars.end(), sir->getOperands()[0]->getVal()) == end(irVisitor->globalVars)) {
            //     for(auto use : sir->getOperands()[0]->getVal()->getUses()) {
            //         User* user = use->getUser();
            //         if(dynamic_cast<LoadIR*>(user)) {
            //             LoadIR* lir = dynamic_cast<LoadIR*>(user);
            //             lir->deleteIR();
                        
            //             Value* v1 = lir->getOperands()[0]->getVal();
            //             lir->getOperands()[1]->getVal()->killUse(lir->getOperands()[1]);
            //             for(auto nextUse : v1->getUses()) {
            //                 User* nextUser = nextUse->getUser();
                            
            //             }
            //         }
            //     }
            // }
        }
    }
}

#endif