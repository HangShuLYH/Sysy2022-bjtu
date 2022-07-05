//
// Created by hangshu on 22-7-4.
//
#define DEBUG
#include "codegen.hh"
#include <set>
#include <algorithm>
void Codegen::regAlloc() {
    for (Function* function: irVisitor.functions) {
        std::map<BasicBlock*, std::set<Value*>> liveIn_i,liveOut_i,def_i,use_i;
        std::map<BasicBlock*, std::set<Value*>> liveIn_f,liveOut_f,def_f,use_f;
        for (BasicBlock* bb: function->basicBlocks) {
            //init in,out,def,use
            std::set<Value*> in_i,out_i,in_f,out_f;
            liveIn_i[bb] = in_i;
            liveOut_i[bb] = out_i;
            liveIn_f[bb] = in_f;
            liveOut_f[bb] = out_f;
            std::set<Value*> defSet_i, defSet_f;
            std::set<Value*> useSet_i, useSet_f;
            for (Instruction* ir: bb->ir) {
                if (ir->getDef()) {
                    if (ir->getDef()->getType()->isInt()) {
                        defSet_i.insert(ir->getDef());
                    }else {
                        defSet_f.insert(ir->getDef());
                    }
                }
                for (int i = 0; i < ir->getUseList().size(); ++i) {
                    if (ir->getUseList()[i]->getType()->isInt()) {
                        useSet_i.insert(ir->getUseList()[i]);
                    }else {
                        useSet_f.insert(ir->getUseList()[i]);
                    }
                }
            }
            def_i[bb] = defSet_i;
            use_i[bb] = useSet_i;
            def_f[bb] = defSet_f;
            use_f[bb] = useSet_f;
        }
        //function arguments
        for (int i = 0; i < function->params.size(); ++i) {
            if (function->params[i]->getType()->isInt()) {
                liveIn_i[function->basicBlocks[0]].insert(function->params[i]);
            } else {
                liveIn_f[function->basicBlocks[0]].insert(function->params[i]);
            }
        }
        //cal GR livein and liveout
        while(true) {
            bool flag = true;
            for (BasicBlock* bb: function->basicBlocks) {
                std::set<Value*> temp,in_prime,out_prime;
                std::set_difference(liveOut_i[bb].begin(),liveOut_i[bb].end(),
                                    def_i[bb].begin(),def_i[bb].end(),
                                    std::inserter(temp,temp.begin()));
                std::set_union(use_i[bb].begin(),use_i[bb].end(),
                               temp.begin(),temp.end(),
                               std::inserter(in_prime,in_prime.begin()));
                if (in_prime != liveIn_i[bb]) {
                    liveIn_i[bb] = in_prime;
                    flag = false;
                }
                std::set<Value*> t1,t2;
                for (BasicBlock* succ:bb->getSucc()) {
                    std::set_union(liveIn_i[succ].begin(),liveIn_i[succ].end(),
                                   t1.begin(),t1.end(),
                                   std::inserter(t2,t2.begin()));
                    t1 = t2;
                    out_prime = t2;
                    t2.clear();
                }
                if (out_prime != liveOut_i[bb]) {
                    liveOut_i[bb] = out_prime;
                    flag = false;
                }
            }
            if (flag) {
                break;
            }
        }

        //cal GR livein and liveout
        calLiveInfo(function,liveIn_i,liveOut_i,def_i,use_i);
        //cal FR livein and liveout
        calLiveInfo(function,liveIn_f,liveOut_f,def_f,use_f);
#ifdef DEBUG
        std::cout << "GR Info:\n";
        printLiveInfo(function,liveIn_i,liveOut_i);
        std::cout << "FR Info:\n";
        printLiveInfo(function,liveIn_f,liveOut_f);
#endif
        //create Inference graph: both GR and FR graph
        std::map<Value*, std::set<Value*>> IG_i, IG_f;
        createIG(IG_i,liveIn_i,liveOut_i);
        createIG(IG_f,liveIn_f,liveOut_f);
        std::cout << "IG create finish\n";
    }
}
void Codegen::calLiveInfo(Function* function,
                 std::map<BasicBlock*,std::set<Value*>>& liveIn,
                 std::map<BasicBlock*,std::set<Value*>>& liveOut,
                 std::map<BasicBlock*,std::set<Value*>>& def,
                 std::map<BasicBlock*,std::set<Value*>>& use) {
    while(true) {
        bool flag = true;
        for (BasicBlock* bb: function->basicBlocks) {
            std::set<Value*> temp,in_prime,out_prime;
            std::set_difference(liveOut[bb].begin(),liveOut[bb].end(),
                                def[bb].begin(),def[bb].end(),
                                std::inserter(temp,temp.begin()));
            std::set_union(use[bb].begin(),use[bb].end(),
                           temp.begin(),temp.end(),
                           std::inserter(in_prime,in_prime.begin()));
            if (in_prime != liveIn[bb]) {
                liveIn[bb] = in_prime;
                flag = false;
            }
            std::set<Value*> t1,t2;
            for (BasicBlock* succ:bb->getSucc()) {
                std::set_union(liveIn[succ].begin(),liveIn[succ].end(),
                               t1.begin(),t1.end(),
                               std::inserter(t2,t2.begin()));
                t1 = t2;
                out_prime = t2;
                t2.clear();
            }
            if (out_prime != liveOut[bb]) {
                liveOut[bb] = out_prime;
                flag = false;
            }
        }
        if (flag) {
            break;
        }
    }
}
void Codegen::printLiveInfo(Function* function,
                            std::map<BasicBlock*,std::set<Value*>>& liveIn,
                            std::map<BasicBlock*,std::set<Value*>>& liveOut) {
    std::cout << function->name << ":\n";
    std::cout << "liveIn():\n";
    auto iter = liveIn.begin();
    while(iter != liveIn.end()) {
        std::cout << "\t" << iter->first->name << ":";
        for (Value* v:iter->second) {
            std::cout << "%" <<v->getNum() << " ";
        }
        std::cout << std::endl;
        iter++;
    }
    std::cout << "liveOut:\n";
    iter = liveOut.begin();
    while(iter != liveOut.end()) {
        std::cout << "\t" <<iter->first->name << ":";
        for (Value* v:iter->second) {
            std::cout << "%" <<v->getNum() << " ";
        }
        std::cout << std::endl;
        iter++;
    }
}

void Codegen::createIG(std::map<Value *, std::set<Value *>>& IG,
              std::map<BasicBlock *, std::set<Value *>> &liveIn,
              std::map<BasicBlock *, std::set<Value *>> &liveOut) {
    auto iter = liveIn.begin();
    while(iter != liveIn.end()) {
        for (Value* v1: iter->second) {
            for (Value* v2: iter->second) {
                if (v1 != v2) {
                    IG[v1].insert(v2);
                    IG[v2].insert(v1);
                }
            }
        }
        iter++;
    }
    iter = liveOut.begin();
    while(iter != liveOut.end()) {
        for (Value* v1: iter->second) {
            for (Value* v2: iter->second) {
                if (v1 != v2) {
                    IG[v1].insert(v2);
                    IG[v2].insert(v1);
                }
            }
        }
        iter++;
    }
}