//
// Created by hanyangchen on 22-6-30.
//

#include "IrVisitor.hh"
#include "Instruction.hh"
#include <map>
// #include

class mem2reg {
    IrVisitor irVisitor;
    std::map<Value*, std::set<NormalBlock*>> defsites;
    std::map<NormalBlock*, std::set<Value*>> bbPhis;
    std::map<Value*, int> counts;
    std::map<Value*, std::stack<int>> stacks;
    void execute();
    void placePhi(Function* function);
    void initAndRenaming(Function* function);
    void rename(NormalBlock* bb);
    void newName(NormalBlock* bb);
};

void mem2reg::execute()
{
    for(Function& function : irVisitor.getFunctions()) {
        if(function->getBB().size() == 0) continue;

        defsites.clear();
        bbPhis.clear();
        counts.clear();
        stacks.clear();

        placePhi();
    }
}

void mem2reg::placePhi(Function* function)
{
    for(NormalBlock* bb : function->getBB()) {
        for(Value& var : bb->getVar()) {
            defsites[var].insert(bb);
            vars.insert(var);
        }
    }

    for(auto& defsite : defsites) {
        std::set<NormalBlock*> W(defsite.second);
        while(!W.empty()) {
            NormalBlock* bb(*W.begin());
            W.erase(W.begin());
            for(auto& dfBB : bb->getDomFrontier()) {
                if(!bbPhis[dfBB].count(defsite.first)) {
                    dfBB.ir.insert(dfBB.ir.begin(), new PhiIR(defsite.first, dfBB->preBBs));
                    bbPhis[dfBB].insert(defsite.first);

                    // 查找是否存在相同的变量，bb的var可改进为set
                    bool flag(false);
                    for(auto& var : bb->getVar()) {
                        if(var == defsite.first) {
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
}

void mem2reg::initAndRenaming(Function* function) {
    for(NormalBlock* bb : function->getBB()) {
        // 初始化
        for(Value* var : bb->getVar()) {
            counts[var] = 0;
            stacks[var] = std::stack<Value*>();
            stacks[var].push(0);
        }

        rename(bb);
    }
}

void mem2reg::rename(NomalBlock* bb) {
    for(Instruction* ir : bb->getIr()) {
        if(typeid(*ir) != typeid(PhiIR)) {
            for()
        }
    }
}