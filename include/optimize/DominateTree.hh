//
// Created by hanyangchen on 22-6-30.
//

#include "IrVisitor.hh"
#include <map>
#include <list>
#include <set>

class DominateTree {
private:
    IrVisitor* irVisitor;
    std::vector<BasicBlock*> doms;
    std::map<BasicBlock*, int> bbMap;
    std::list<BasicBlock*> reversePostOrder;
public:
    DominateTree(IrVisitor* irVisitor) : irVisitor(irVisitor) {}
    void execute();
    void getIdom(Function* function);
    void getDomFront(Function* function);
    void getPostOrder(BasicBlock* bb, std::set<BasicBlock*>& visited);
    void genDominateTree(Function* function);
    // void genBBDom(BasicBlock* bb);
    BasicBlock* intersect(BasicBlock* bb1, BasicBlock* bb2);
};

void DominateTree::execute() {
    for (auto function : irVisitor->getFunctions()) {
        if(function->getBB().empty()) continue;

        // 清空，初始化
        doms.clear();
        bbMap.clear();
        reversePostOrder.clear();

        getIdom(function);
        getDomFront(function);
        genDominateTree(function);
    }
}

// 获得立即支配集
void DominateTree::getIdom(Function* function) {
    // 获得逆序后续遍历
    BasicBlock* entryBB = function->getBB()[0];
    std::set<BasicBlock*> visited = {};
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
            BasicBlock* newIdom = nullptr;
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
void DominateTree::getPostOrder(BasicBlock* bb, std::set<BasicBlock*>& visited) {
    visited.insert(bb);
    std::vector<BasicBlock*> succBBs = bb->getSucc();
    for(int i(succBBs.size() - 1); i >= 0; i--) {
        if(!visited.count(succBBs[i])) getPostOrder(succBBs[i], visited);
    }
    bbMap[bb] = reversePostOrder.size();
    reversePostOrder.push_back(bb);
}

// 双指针算法求交集
BasicBlock* DominateTree::intersect(BasicBlock* bb1, BasicBlock* bb2) {
    BasicBlock* finger1 = bb1, *finger2 = bb2;
    while(finger1 != finger2) {
        while(bbMap[finger1] < bbMap[finger2]) {
            finger1 = doms[bbMap[finger1]];
        }
        while(bbMap[finger2] < bbMap[finger1]) {
            finger2 = doms[bbMap[finger2]];
        }
    }
    return finger1;
}

// 获得支配前沿
void DominateTree::getDomFront(Function* function) {
    for(BasicBlock* bb : function->getBB()) {
        if(bb->getPre().size() >= 2) {
            for(BasicBlock* preBB : bb->getPre()) {
                BasicBlock* runner = preBB;
                while(runner != doms[bbMap[bb]]) {
                    runner->insertDomFrontier(bb);
                    runner = doms[bbMap[runner]];
                }
            }
        }
    }
}

// 获得支配树
void DominateTree::genDominateTree(Function* function) {
    for(auto bb : function->getBB()) {
        BasicBlock* idom = bb->getIdom();
        if(idom && idom != bb) {
            idom->pushDomTreeSuccNode(bb);
        }
    }
}

// void genBBDom(BasicBlock* bb) {
//     if(!bb) return;

//     bb->insertDom(bb);
//     genBBDom(bb->getIdom());
// }