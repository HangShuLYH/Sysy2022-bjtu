//
// Created by hanyangchen on 22-6-30.
//

#include "IrVisitor.hh"
#include <map>
#include <list>
#include <set>

class DominateTree {
private:
    IrVisitor& irVisitor;
    std::vector<NormalBlock*> doms;
    std:map<NormalBlock*, int> bbMap;
    std::list<NormalBlock*> reversePostOrder;
public:
    DominateTree(IrVisitor& irVisitor) : irVisitor(irVisitor) {}
    void execute();
    void getIdom(Function* function);
    void getDomFront(Function* function);
    void getPostOrder(NormalBlock* bb, std::set<NormalBlock*>& visited);
    void genDominateTree(Function* function);
    void genBBDom(NormalBlock* bb);
    NormalBlock* intersect(NormalBlock* bb1, NormalBlock* bb2);
};

void DominateTree::execute() {
    for (auto function : irVisitor.getFunctions()) {
        if(function->getBB().empty()) continue;

        // 清空，初始化
        doms.clear();
        bbMap.clear();
        reversePostOrder.clear();

        getIdom(function);
        getDomFront(function);
    }
}

// 获得立即支配集
void DominateTree::getIdom(Function* function) {
    // 获得逆序后续遍历
    NormalBlock* entryBB = function->getBB()[0];
    std::set<NormalBlock*> visited = {};
    getPostOrder(entryBB, visited);
    reversePostOrder.reverse();

    // 初始化dom
    for(int i(0); i <= bbMap[entryBB]; i++) {
        doms.push_back(nullptr);
    }

    // 开始迭代算法
    doms[bbMap[entryBB]] = entryBB;

    bool changed = true;
    while(changed) {
        changed = false;
        for(auto bb : reversePostOrder) {
            if(bb == entryBB) continue;
            NormalBlock* newIdom = nullptr;
            // 获得bb的前驱  new_idom ← first (processed) predecessor of b /* (pick one) */
            for(auto preBB : bb->getPre()) {
                if(doms[bbMap[preBB]] != nullptr) {
                    newIdom = preBB;
                    break;
                }
            }
            
            for(auto preBB : bb->getPre()) {
                if(doms[bbMap[preBB]] != nullptr) {
                    newIdom = intersect(preBB, newIdom);
                }
            }

            if(newIdom != doms[bbMap[bb]]) {
                doms[bbMap[bb]] = newIdom;
                changed = true;
            }
        }
    }

    for(auto bb : reversePostOrder){
        bb->setIdom(doms[bbMap[bb]]);
    }
}

// 后续遍历
void DominateTree::getPostOrder(NormalBlock* bb, std::set<NormalBlock*>& visited) {
    visited.insert(bb);
    list<NormalBlock*> succBBs = bb->getSucc();
    for(auto succBB : succBBs) {
        visited.count(succBB) == 0 ? getPostOrder(succBB, visited) : continue;
    }
    bbMap[bb] = reversePostOrder.size();
    reversePostOrder.push_back(bb);
}

// 双指针算法求交集
NormalBlock* intersect(NormalBlock* bb1, NormalBlock* bb2) {
    NormalBlock* finger1 = bb1, finger2 = bb1;
    while(finger1 != finger2) {
        while(bbMap[finger1] < bbMap[finger2]) {
            finger1 = doms[finger1];
        } else {
            finger2 = doms[finger2];
        }
    }
    return finger1;
}

// 获得支配前沿
void DominateTree::getDomFront(Function* function) {
    for(NormalBlock* bb : function->getBB()) {
        if(bb->getPre().size() >= 2) {
            for(NormalBlock* preBB : bb->getPre()) {
                NormalBlock* runner = preBB;
                while(runner != doms[bb]) {
                    runner->insertDomFrontier(bb);
                    runner = doms[bbMap[runner]];
                }
            }
        }
    }
}

// 获得支配树
void genDominateTree(Function* function) {
    for(auto bb :: function->getBB()) {
        getBBDominateTree(bb);
    }
}

void genBBDom(NormalBlock* bb) {
    if(!bb) return;

    bb->insertDom(bb);
    genBBDom(bb->getIdom());
}
