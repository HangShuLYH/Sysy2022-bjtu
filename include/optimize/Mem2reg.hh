//
// Created by hanyangchen on 22-6-30.
//

#include "IrVisitor.hh"
#include "Instruction.hh"
#include <map>
// #include

class Mem2reg {
private:
    IrVisitor* irVisitor;
    Function* function;
    std::map<Value*, std::set<BasicBlock*>> defsites;
    std::map<BasicBlock*, std::set<Value*>> bbPhis;
    std::map<Value*, int> counts;
    std::map<Value*, std::stack<int>> stacks;
public:
    Mem2reg(IrVisitor* irVisitor) : irVisitor(irVisitor) {;}
    void execute();
    void genDefUse();
    void addPhiDefUse(BasicBlock* bb, Use* use);
    void placePhi();
    void rename();
    void addStartDefUse(BasicBlock* bb, Value* val, std::vector<Use*>* vec);
};

void Mem2reg::execute()
{
    std::vector<Function*> functions = irVisitor->getFunctions();
    for(Function* func : functions) {
        if(func->getBB().size() == 0) continue;

        this->function = func;
        defsites.clear();
        bbPhis.clear();
        counts.clear();
        stacks.clear();
        // insideBlockForwarding(function);
        genDefUse();
        placePhi();
        rename();
    }
}

void Mem2reg::genDefUse() {
    for(auto bb : function->getBB()) {
        auto& irs = bb->getIr();
        for(int i(0); i < irs.size(); i++) {
            // auto type = typeid(*irs[i]);
            if(typeid(*irs[i]) != typeid(BreakIR) && typeid(*irs[i]) != typeid(ContinueIR) && typeid(*irs[i]) != typeid(JumpIR)) {
                if((typeid(*irs[i]) == typeid(AllocIIR) || typeid(*irs[i]) == typeid(AllocFIR)) && !irs[i]->is_Array()) {
                    auto operands = irs[i]->getOperands();
                    std::vector<Use*>* vec = new std::vector<Use*>();
                    std::pair<Value*, std::vector<Use*>*> p(operands[0]->getVal(), vec);
                    bb->defuse[operands[0]->getVal()].push_back(p);
                    function->allocaVars.insert(operands[0]->getVal());
                }
                else if(typeid(*irs[i]) == typeid(StoreIIR) || typeid(*irs[i]) == typeid(StoreFIR)) {
                    auto operands = irs[i]->getOperands();
                    if(function->allocaVars.count(operands[0]->getVal())) {
                        std::vector<Use*>* vec = new std::vector<Use*>(1, operands[0]);
                        std::pair<Value*, std::vector<Use*>*> p(operands[0]->getVal(), vec);
                        bb->defuse[operands[0]->getVal()].push_back(p);
                    }
                }
                else {
                    auto operands = irs[i]->getOperands();
                    for(auto operand : operands) {
                        if(bb->defuse.count(operand->getVal())) {
                            auto top = bb->defuse[operand->getVal()].rbegin();
                            top->second->push_back(operand);
                        }
                    }
                }
            }
        }
    }
}

void Mem2reg::addStartDefUse(BasicBlock* bb, Value* val, std::vector<Use*>* vec) {
    auto& irs = bb->getIr();
    for(int i(0); i < irs.size(); i++) {
        // auto type = typeid(*irs[i]);
        if(typeid(*irs[i]) != typeid(BreakIR) && typeid(*irs[i]) != typeid(ContinueIR) && typeid(*irs[i]) != typeid(JumpIR)) {
            if((typeid(*irs[i]) == typeid(AllocIIR) || typeid(*irs[i]) == typeid(AllocFIR)) && !irs[i]->is_Array()) {
                continue;
            }
            else if(typeid(*irs[i]) == typeid(StoreIIR) || typeid(*irs[i]) == typeid(StoreFIR) || typeid(*irs[i]) == typeid(PhiIR)) {
                auto operands = irs[i]->getOperands();
                if(val == operands[0]->getVal()) {
                    return;
                }
            }
            else {
                auto operands = irs[i]->getOperands();
                for(auto operand : operands) {
                    if(val == operand->getVal()) {
                        vec->push_back(operand);
                    }
                }
            }
        }
    }
    
    for(auto succBB : bb->getSucc()) {
        addStartDefUse(succBB, val, vec);
    }
}

void Mem2reg::addPhiDefUse(BasicBlock* bb, Use* use) {
    std::vector<Use*>* vec = new std::vector<Use*>(1, use);
    std::pair<Value*, std::vector<Use*>*> p(use->getVal(), vec);

    for(auto ir : bb->getIr()) {
        if((typeid(*ir) == typeid(StoreIIR) || typeid(*ir) == typeid(StoreFIR)) && ir->getOperands()[0]->getVal() == use->getVal()) {
            break;
        }
        else {
            auto operands = ir->getOperands();
            for(auto operand : operands) {
                if(operand->getVal() == use->getVal()) {
                    p.second->push_back(operand);
                }
            }
        }
    }

    bb->defuse[use->getVal()].insert(bb->defuse[use->getVal()].begin(), p);
}

void Mem2reg::placePhi() {
    for(BasicBlock* bb : function->getBB()) {
        for(auto def : bb->defuse) {
            defsites[def.first].insert(bb);
            // vars.insert(var);
        }
    }

    for(auto& defsite : defsites) {
        std::set<BasicBlock*> W(defsite.second);
        while(!W.empty()) {
            BasicBlock* bb(*W.begin());
            W.erase(W.begin());
            for(auto& dfBB : bb->getDomFrontier()) {
                if(!bbPhis[dfBB].count(defsite.first)) {
                    dfBB->ir.insert(dfBB->ir.begin(), new PhiIR(dfBB->getPre(), defsite.first));
                    this->addPhiDefUse(dfBB, dfBB->ir[0]->getOperands()[0]);
                    bbPhis[dfBB].insert(defsite.first);

                    // 查找是否存在相同的变量，bb的var可改进为set
                    bool flag(false);
                    for(auto& def : bb->defuse) {
                        if(def.first == defsite.first) {
                            flag = true;
                            break;
                        }
                    }
                    if(!flag) {
                        W.insert(dfBB);
                    }
                    // if(bb->getVar().(defsite.first))
                }
            }
        }
    }

    for(BasicBlock* bb : function->getBB()) {
        for(auto& defuse : bb->defuse) {
            for(auto succBB : bb->getSucc()) {
                addStartDefUse(succBB, defuse.first, defuse.second[defuse.second.size() - 1].second);
            }
        }
    }
}

void Mem2reg::rename() {
    for(auto& bb : function->getBB()) {
        for(auto& defuse : bb->defuse) {
            for(int i(0); i < defuse.second.size(); i++) {
                std::vector<Use*>* vec(defuse.second[i].second);
                Value* val;
                if(typeid(*(defuse.second[i].first)) == typeid(VarValue)) {
                    val = new VarValue(*(dynamic_cast<VarValue*>(defuse.second[i].first)));
                } else if(typeid(*(defuse.second[i].first)) == typeid(TempVal)) {
                    val = new TempVal(*(dynamic_cast<TempVal*>(defuse.second[i].first)));
                } else if(typeid(*(defuse.second[i].first)) == typeid(ConstValue)) {
                    val = new ConstValue(*(dynamic_cast<ConstValue*>(defuse.second[i].first)));
                }
                val->setNum(function->varCnt++);

                for(int i(0); i < vec->size(); i++) {
                    Instruction* inst = dynamic_cast<Instruction*>((*vec)[i]->getUser());
                    (*vec)[i]->setVal(val);
                }

                std::pair<Value*, std::vector<Use*>*> p(val, vec);
                defuse.second[i].swap(p);
            }
        }
    }

    for(auto& bb : function->getBB()) {
        for(auto& defuse : bb->defuse) {
            for(auto iter(defuse.second.begin()); iter != defuse.second.end(); iter++) {
                std::vector<Use*>* vec(iter->second);
                if(vec && vec->size() > 0 && typeid(*(*vec)[0]->getUser()) == typeid(PhiIR)) {
                    PhiIR* phiIR = dynamic_cast<PhiIR*>((*vec)[0]->getUser());
                    for(auto& param : phiIR->params) {
                        if(param.first->defuse.count(param.second)) {
                            param.second = param.first->defuse[param.second].rbegin()->first;
                        } else {
                            param.second = nullptr;
                        }
                    }
                }
            }
        }
    }
}