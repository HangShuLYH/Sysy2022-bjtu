//
// Created by hangshu on 22-7-13.
//
#include "allocRegs.hh"
#include <deque>

int ColoringAlloc::run() {
    liveAnalysis();
    build();
    makeWorkList();
    //std::cerr << "makeWorkList\n";
    while (true) {
        if (!simplifyWorkListGR.empty()) {
            //std::cerr << "simplify\n";
            simplifyGR();
        } else if (!workListMovesGR.empty()) {
            //std::cerr << "coalesce\n";
            coalesceGR();
        } else if (!freezeWorkListGR.empty()) {
            //std::cerr << "freeze\n";
            freezeGR();
        } else if (!spillWorkListGR.empty()) {
            //std::cerr << "selectSpill\n";
            selectSpillGR();
        }
        if (simplifyWorkListGR.empty() && workListMovesGR.empty() &&
            freezeWorkListGR.empty() && spillWorkListGR.empty()) {
            break;
        }
    }
    assignColorsGR();
    if (!spillWorkListGR.empty()) {
        //std::cerr << "spillGR " << spillWorkListGR.size() << "\n";
        rewriteProgramGR();
        run();
    }
    while (true) {
        if (!simplifyWorkListFR.empty()) {
            simplifyFR();
        } else if (!workListMovesFR.empty()) {
            coalesceFR();
        } else if (!freezeWorkListFR.empty()) {
            freezeFR();
        } else if (!spillWorkListFR.empty()) {
            selectSpillFR();
        }
        if (simplifyWorkListFR.empty() && workListMovesFR.empty() &&
            freezeWorkListFR.empty() && spillWorkListFR.empty()) {
            break;
        }
    }
    assignColorsFR();
    if (!spillWorkListFR.empty()) {
        rewriteProgramFR();
        run();
    }
    return spillCount;
}

void ColoringAlloc::liveAnalysis() {
    std::deque<std::pair<BasicBlock *, GR>> updateI;
    std::deque<std::pair<BasicBlock *, FR>> updateF;
    for (auto block: function->basicBlocks) {
        for (int i = block->getInstrs().size() - 1; i >= 0; i--) {
            Instr *ir = block->getInstrs()[i];
            for (GR gr: ir->getDefG()) {
                useI[block].erase(gr);
                defI[block].insert(gr);
                grs.insert(gr);
            }
            for (GR gr: ir->getUseG()) {
                defI[block].erase(gr);
                useI[block].insert(gr);
                grs.insert(gr);
            }
            for (FR fr: ir->getDefF()) {
                useF[block].erase(fr);
                defF[block].insert(fr);
                frs.insert(fr);
            }
            for (FR fr: ir->getUseF()) {
                defF[block].erase(fr);
                useF[block].insert(fr);
                frs.insert(fr);
            }
        }
        liveInI = useI;
        liveInF = useF;
        for (GR gr: useI[block]) {
            updateI.emplace_back(block, gr);
        }
        for (FR fr: useF[block]) {
            updateF.emplace_back(block, fr);
        }
    }
    while (!updateI.empty()) {
        std::pair<BasicBlock *, GR> cur = updateI.front();
        updateI.pop_front();
        for (BasicBlock *prev: cur.first->getPre()) {
            if (liveOutI[prev].find(cur.second) == liveOutI[prev].end()) {
                liveOutI[prev].insert(cur.second);
                if (defI[prev].find(cur.second) == defI[prev].end() &&
                    liveInI[prev].find(cur.second) == liveInI[prev].end()) {
                    liveInI[prev].insert(cur.second);
                    updateI.emplace_back(prev, cur.second);
                }
            }
        }
    }
    while (!updateF.empty()) {
        std::pair<BasicBlock *, FR> cur = updateF.front();
        updateF.pop_front();
        for (BasicBlock *prev: cur.first->getPre()) {
            if (liveOutF[prev].find(cur.second) == liveOutF[prev].end()) {
                liveOutF[prev].insert(cur.second);
                if (defF[prev].find(cur.second) == defF[prev].end() &&
                    liveInF[prev].find(cur.second) == liveInF[prev].end()) {
                    liveInF[prev].insert(cur.second);
                    updateF.emplace_back(prev, cur.second);
                }
            }
        }
    }
}

void ColoringAlloc::build() {
    for (BasicBlock *block: function->basicBlocks) {
        std::set<GR> liveGR = liveOutI[block];
        std::set<FR> liveFR = liveOutF[block];
        for (int i = block->getInstrs().size() - 1; i >= 0; i--) {
            Instr *instr = block->getInstrs()[i];
            if (typeid(*instr) == typeid(MoveReg)) {
                for (GR gr: instr->getUseG()) {
                    liveGR.erase(gr);
                    moveListGR[gr].insert(instr);
                }
                for (GR gr: instr->getDefG()) {
                    moveListGR[gr].insert(instr);
                }
                workListMovesGR.insert(instr);
            }
            if (typeid(*instr) == typeid(VMoveReg)) {
                for (FR fr: instr->getUseF()) {
                    liveFR.erase(fr);
                    moveListFR[fr].insert(instr);
                }
                for (FR fr: instr->getDefF()) {
                    moveListFR[fr].insert(instr);
                }
                workListMovesFR.insert(instr);
            }
            for (GR gr: instr->getDefG()) {
                liveGR.insert(gr);
            }
            for (FR fr: instr->getDefF()) {
                liveFR.insert(fr);
            }
            for (GR gr1: instr->getDefG()) {
                for (GR gr2: liveGR) {
                    addEdgeGR(gr1, gr2);
                }
            }
            for (FR fr1: instr->getDefF()) {
                for (FR fr2: liveFR) {
                    addEdgeFR(fr1, fr2);
                }
            }
            for (GR gr: instr->getDefG()) {
                liveGR.erase(gr);
            }
            for (FR fr: instr->getDefF()) {
                liveFR.erase(fr);
            }
            for (GR gr: instr->getUseG()) {
                liveGR.insert(gr);
            }
            for (FR fr: instr->getUseF()) {
                liveFR.insert(fr);
            }
        }
    }
}

void ColoringAlloc::addEdgeGR(GR lhs, GR rhs) {
    if (adjSetGR.count(std::make_pair(lhs, rhs)) == 0 && lhs != rhs) {
        adjSetGR.insert(std::make_pair(lhs,rhs));
        adjSetGR.insert(std::make_pair(rhs,lhs));
        if (preColoredGR.count(lhs) == 0) {
            adjListGR[lhs].insert(rhs);
            if (degreeGR.count(lhs) == 0) degreeGR[lhs] = 0;
            degreeGR[lhs]++;
        }
        if (preColoredGR.count(rhs) == 0) {
            adjListGR[rhs].insert(lhs);
            if (degreeGR.count(rhs) == 0) degreeGR[rhs] = 0;
            degreeGR[rhs]++;
        }
    }
}

void ColoringAlloc::addEdgeFR(FR lhs, FR rhs) {
    if (adjSetFR.count(std::make_pair(lhs, rhs)) == 0 && lhs != rhs) {
        adjSetFR.insert(std::make_pair(lhs,rhs));
        adjSetFR.insert(std::make_pair(rhs,lhs));
        if (preColoredFR.count(lhs) == 0) {
            adjListFR[lhs].insert(rhs);
            if (degreeFR.count(lhs) == 0) degreeFR[lhs] = 0;
            degreeFR[lhs]++;
        }
        if (preColoredFR.count(rhs) == 0) {
            adjListFR[rhs].insert(lhs);
            if (degreeFR.count(rhs) == 0) degreeFR[rhs] = 0;
            degreeFR[rhs]++;
        }
    }
}

void ColoringAlloc::makeWorkList() {
    for (GR gr: grs) {
        if (!gr.isVirtual()) {
            colorGR[gr] = gr.getID();
            preColoredGR.insert(gr);
        }
    }
    for (FR fr: frs) {
        if (!fr.isVirtual()) {
            colorFR[fr] = fr.getID();
            preColoredFR.insert(fr);
        }
    }
    for (auto it = grs.begin(); it != grs.end();) {
        GR gr = *it;
        it = grs.erase(it);
        if (adjListGR[gr].size() >= KGR) {
            spillWorkListGR.insert(gr);
        } else if (moveRelatedGR(gr)) {
            freezeWorkListGR.insert(gr);
        } else {
            simplifyWorkListGR.insert(gr);
        }
    }
    for (auto it = frs.begin(); it != frs.end();) {
        FR fr = *it;
        it = frs.erase(it);
        if (adjListFR[fr].size() >= KFR) {
            spillWorkListFR.insert(fr);
        } else if (moveRelatedFR(fr)) {
            freezeWorkListFR.insert(fr);
        } else {
            simplifyWorkListFR.insert(fr);
        }
    }
}

bool ColoringAlloc::moveRelatedGR(GR gr) {
    std::set<Instr *> temp = nodeMovesGR(gr);
    return temp.size() > 0;
}

bool ColoringAlloc::moveRelatedFR(FR fr) {
    std::set<Instr *> temp = nodeMovesFR(fr);
    return temp.size() > 0;
}

std::set<Instr *> ColoringAlloc::nodeMovesGR(GR gr) {
    std::set<Instr *> ans = moveListGR[gr];
    for (auto it = ans.begin(); it != ans.end();) {
        Instr *instr = *it;
        if (activeMovesGR.count(instr) == 0 &&
            workListMovesGR.count(instr) == 0) {
            it = ans.erase(it);
        } else {
            it++;
        }
    }
    return ans;
}

std::set<Instr *> ColoringAlloc::nodeMovesFR(FR fr) {
    std::set<Instr *> ans = moveListFR[fr];
    for (auto it = ans.begin(); it != ans.end();) {
        Instr *instr = *it;
        if (activeMovesFR.count(instr) == 0 &&
            workListMovesFR.count(instr) == 0) {
            it = ans.erase(it);
        } else {
            it++;
        }
    }
    return ans;
}

void ColoringAlloc::simplifyGR() {
    for (auto it = simplifyWorkListGR.begin(); it != simplifyWorkListGR.end();) {
        GR gr = *it;
        it = simplifyWorkListGR.erase(it);
        if (preColoredGR.count(gr) != 0) {
            continue;
        }
        stackGR.push(gr);
        for (GR gr2: adjacentGR(gr)) {
            decrementDegreeGR(gr2);
        }
    }
}

void ColoringAlloc::simplifyFR() {
    for (auto it = simplifyWorkListFR.begin(); it != simplifyWorkListFR.end();) {
        FR fr = *it;
        it = simplifyWorkListFR.erase(it);
        if (preColoredFR.count(fr) != 0) {
            continue;
        }
        stackFR.push(fr);
        for (FR fr2: adjacentFR(fr)) {
            decrementDegreeFR(fr2);
        }
    }
}

std::set<GR> ColoringAlloc::adjacentGR(GR gr) {
    std::set<GR> ans = adjListGR[gr];
    std::stack<GR> temp = stackGR;
    while (!temp.empty()) {
        ans.erase(temp.top());
        temp.pop();
    }
    for (GR gr2: coloredNodesGR) {
        ans.erase(gr2);
    }
    return ans;
}

std::set<FR> ColoringAlloc::adjacentFR(FR fr) {
    std::set<FR> ans = adjListFR[fr];
    std::stack<FR> temp = stackFR;
    while (!temp.empty()) {
        ans.erase(temp.top());
        temp.pop();
    }
    for (FR fr2: coloredNodesFR) {
        ans.erase(fr2);
    }
    return ans;
}

void ColoringAlloc::decrementDegreeGR(GR gr) {
    int d = degreeGR[gr];
    degreeGR[gr] = d - 1;
    if (d == KGR) {
        std::set<GR> temp = adjacentGR(gr);
        temp.insert(gr);
        enableMovesGR(temp);
        spillWorkListGR.erase(gr);
        if (moveRelatedGR(gr)) {
            freezeWorkListGR.insert(gr);
        } else {
            simplifyWorkListGR.insert(gr);
        }
    }
}

void ColoringAlloc::decrementDegreeFR(FR fr) {
    int d = degreeFR[fr];
    degreeFR[fr] = d - 1;
    if (d == KFR) {
        std::set<FR> temp = adjacentFR(fr);
        temp.insert(fr);
        enableMovesFR(temp);
        spillWorkListFR.erase(fr);
        if (moveRelatedFR(fr)) {
            freezeWorkListFR.insert(fr);
        } else {
            simplifyWorkListFR.insert(fr);
        }
    }
}

void ColoringAlloc::enableMovesGR(std::set<GR> nodesGR) {
    for (GR gr: nodesGR) {
        for (Instr *instr: nodeMovesGR(gr)) {
            if (activeMovesGR.count(instr) != 0) {
                activeMovesGR.erase(instr);
                workListMovesGR.insert(instr);
            }
        }
    }
}

void ColoringAlloc::enableMovesFR(std::set<FR> nodesFR) {
    for (FR fr: nodesFR) {
        for (Instr *instr: nodeMovesFR(fr)) {
            if (activeMovesFR.count(instr) != 0) {
                activeMovesFR.erase(instr);
                workListMovesFR.insert(instr);
            }
        }
    }
}

void ColoringAlloc::coalesceGR() {
    for (auto it = workListMovesGR.begin(); it != workListMovesGR.end();) {
        Instr *instr = *it;
        GR x = getAliasGR(instr->getDefG()[0]);
        GR y = getAliasGR(instr->getUseG()[0]);
        GR u, v;
        if (preColoredGR.count(y) != 0) {
            u = y;
            v = x;
        } else {
            u = x;
            v = y;
        }
        it = workListMovesGR.erase(it);
        if (u == v) {
            coalescedMovesGR.insert(instr);
            addWorkListGR(u);
        } else if (preColoredGR.count(v) != 0 ||
                   adjSetGR.count(std::make_pair(u, v)) != 0) {
            constrainedMovesGR.insert(instr);
            addWorkListGR(u);
            addWorkListGR(v);
        } else {
            bool flag = (preColoredGR.count(u) != 0);
            for (GR t: adjacentGR(v)) {
                flag &= okGR(t, u);
            }
            std::set<GR> temp = adjacentGR(u);
            for (GR gr: adjacentGR(v)) {
                temp.insert(gr);
            }
            if (flag || preColoredGR.count(u) == 0 && conservativeGR(temp)) {
                coalescedMovesGR.insert(instr);
                combineGR(u, v);
                addWorkListGR(u);
            } else {
                activeMovesGR.insert(instr);
            }
        }
    }
}

void ColoringAlloc::coalesceFR() {
    for (auto it = workListMovesFR.begin(); it != workListMovesFR.end();) {
        Instr *instr = *it;
        FR x = getAliasFR(instr->getDefF()[0]);
        FR y = getAliasFR(instr->getUseF()[0]);
        FR u, v;
        if (preColoredFR.count(y) != 0) {
            u = y;
            v = x;
        } else {
            u = x;
            v = y;
        }
        it = workListMovesFR.erase(it);
        if (u == v) {
            coalescedMovesFR.insert(instr);
            addWorkListFR(u);
        } else if (preColoredFR.count(v) != 0 ||
                   adjSetFR.count(std::make_pair(u, v)) != 0) {
            constrainedMovesFR.insert(instr);
            addWorkListFR(u);
            addWorkListFR(v);
        } else {
            bool flag = (preColoredFR.count(u) != 0);
            for (FR t: adjacentFR(v)) {
                flag &= okFR(t, u);
            }
            std::set<FR> temp = adjacentFR(u);
            for (FR gr: adjacentFR(v)) {
                temp.insert(gr);
            }
            if (flag || preColoredFR.count(u) && conservativeFR(temp)) {
                coalescedMovesFR.insert(instr);
                combineFR(u, v);
                addWorkListFR(u);
            } else {
                activeMovesFR.insert(instr);
            }
        }
    }
}

void ColoringAlloc::addWorkListGR(GR gr) {
    if (preColoredGR.count(gr) == 0 && !(moveRelatedGR(gr) && degreeGR[gr] < KGR)) {
        freezeWorkListGR.erase(gr);
        simplifyWorkListGR.insert(gr);
    }
}

void ColoringAlloc::addWorkListFR(FR fr) {
    if (preColoredFR.count(fr) == 0  && !(moveRelatedFR(fr) && degreeFR[fr] < KFR)) {
        freezeWorkListFR.erase(fr);
        simplifyWorkListFR.insert(fr);
    }
}

GR ColoringAlloc::getAliasGR(GR gr) {
    if (coalescedNodesGR.count(gr) != 0) {
        return getAliasGR(aliasGR[gr]);
    }
    return gr;
}

FR ColoringAlloc::getAliasFR(FR fr) {
    if (coalescedNodesFR.count(fr) != 0) {
        return getAliasFR(aliasFR[fr]);
    }
    return fr;
}

bool ColoringAlloc::okGR(GR t, GR r) {
    return degreeGR[t] < KGR || preColoredGR.count(t) != 0 ||
           adjSetGR.count(std::make_pair(t, r));
}

bool ColoringAlloc::okFR(FR t, FR r) {
    return degreeFR[t] < KFR || preColoredFR.count(t) != 0 ||
           adjSetFR.count(std::make_pair(t, r));
}

bool ColoringAlloc::conservativeGR(std::set<GR> nodesGR) {
    int k = 0;
    for (GR gr: nodesGR) {
        if (degreeGR[gr] >= KGR) k++;
    }
    return k < KGR;
}

bool ColoringAlloc::conservativeFR(std::set<FR> nodesFR) {
    int k = 0;
    for (FR fr: nodesFR) {
        if (degreeFR[fr] >= KFR) k++;
    }
    return k < KFR;
}

void ColoringAlloc::combineGR(GR u, GR v) {
    if (freezeWorkListGR.count(v) != 0) {
        freezeWorkListGR.erase(v);
    } else {
        spillWorkListGR.erase(v);
    }
    coalescedNodesGR.insert(v);
    aliasGR[v] = u;
    for (Instr *instr: moveListGR[v]) {
        moveListGR[u].insert(instr);
    }
    enableMovesGR({v});
    for (GR gr: adjacentGR(v)) {
        addEdgeGR(gr, u);
        decrementDegreeGR(gr);
    }
    if (degreeGR[u] >= KGR && freezeWorkListGR.count(u) != 0) {
        freezeWorkListGR.erase(u);
        spillWorkListGR.insert(u);
    }
}

void ColoringAlloc::combineFR(FR u, FR v) {
    if (freezeWorkListFR.count(v) != 0) {
        freezeWorkListFR.erase(v);
    } else {
        spillWorkListFR.erase(v);
    }
    coalescedNodesFR.insert(v);
    aliasFR[v] = u;
    for (Instr *instr: moveListFR[v]) {
        moveListFR[u].insert(instr);
    }
    enableMovesFR({v});
    for (FR fr: adjacentFR(v)) {
        addEdgeFR(fr, u);
        decrementDegreeFR(fr);
    }
    if (degreeFR[u] >= KFR && freezeWorkListFR.count(u) != 0) {
        freezeWorkListFR.erase(u);
        spillWorkListFR.insert(u);
    }
}

void ColoringAlloc::freezeGR() {
    while (true) {
        auto it = freezeWorkListGR.begin();
        if (it == freezeWorkListGR.end()) {
            break;
        }
        GR gr = *it;
        it = freezeWorkListGR.erase(it);
        simplifyWorkListGR.insert(gr);
        freezeMovesGR(gr);
    }
}

void ColoringAlloc::freezeFR() {
    while (true) {
        auto it = freezeWorkListFR.begin();
        if (it == freezeWorkListFR.end()) {
            break;
        }
        FR fr = *it;
        it = freezeWorkListFR.erase(it);
        simplifyWorkListFR.insert(fr);
        freezeMovesFR(fr);
    }
}

void ColoringAlloc::freezeMovesGR(GR u) {
    for (Instr *instr: nodeMovesGR(u)) {
        GR x = instr->getDefG()[0];
        GR y = instr->getUseG()[0];
        GR v;
        if (getAliasGR(y) == getAliasGR(u)) {
            v = getAliasGR(x);
        } else {
            v = getAliasGR(y);
        }
        activeMovesGR.erase(instr);
        frozenMovesGR.insert(instr);
        if (nodeMovesGR(v).empty() && degreeGR[v] < KGR) {
            freezeWorkListGR.erase(v);
            simplifyWorkListGR.insert(u);
        }
    }
}

void ColoringAlloc::freezeMovesFR(FR u) {
    for (Instr *instr: nodeMovesFR(u)) {
        FR x = instr->getDefF()[0];
        FR y = instr->getUseF()[0];
        FR v;
        if (getAliasFR(y) == getAliasFR(u)) {
            v = getAliasFR(x);
        } else {
            v = getAliasFR(y);
        }
        activeMovesFR.erase(instr);
        frozenMovesFR.insert(instr);
        if (nodeMovesFR(v).empty() && degreeFR[v] < KFR) {
            freezeWorkListFR.erase(v);
            simplifyWorkListFR.insert(u);
        }
    }
}

void ColoringAlloc::selectSpillGR() {
    GR m = *spillWorkListGR.begin();
    spillWorkListGR.erase(m);
    simplifyWorkListGR.insert(m);
    freezeMovesGR(m);
}

void ColoringAlloc::selectSpillFR() {
    FR m = *spillWorkListFR.begin();
    spillWorkListFR.erase(m);
    simplifyWorkListFR.insert(m);
    freezeMovesFR(m);
}

void ColoringAlloc::assignColorsGR() {
    while (!stackGR.empty()) {
        GR n = stackGR.top();
        stackGR.pop();
        std::set<int> okColorsGR;
        for (int i = 0; i < KGR; ++i) {
            okColorsGR.insert(i);
        }
        for (GR w: adjListGR[n]) {
            GR ww = getAliasGR(w);
            if (coloredNodesGR.count(ww) != 0 || preColoredGR.count(ww) != 0) {
                okColorsGR.erase(colorGR[ww]);
            }
        }
        if (okColorsGR.empty()) {
            spillWorkListGR.insert(n);
        } else {
            coloredNodesGR.insert(n);
            colorGR[n] = *okColorsGR.begin();
        }
    }
    for (GR n: coalescedNodesGR) {
        GR x = getAliasGR(n);
        colorGR[n] = colorGR[getAliasGR(n)];
    }
}

void ColoringAlloc::assignColorsFR() {
    while (!stackFR.empty()) {
        FR n = stackFR.top();
        stackFR.pop();
        std::set<int> okColorsFR;
        for (int i = 0; i < KFR; ++i) {
            okColorsFR.insert(i);
        }
        for (FR w: adjListFR[n]) {
            FR ww = getAliasFR(w);
            if (coloredNodesFR.count(ww) != 0 || preColoredFR.count(ww) != 0) {
                okColorsFR.erase(colorFR[ww]);
            }
        }
        if (okColorsFR.empty()) {
            spillWorkListFR.insert(n);
        } else {
            coloredNodesFR.insert(n);
            colorFR[n] = *okColorsFR.begin();
        }
    }
    for (FR n: coalescedNodesFR) {
        colorFR[n] = colorFR[getAliasFR(n)];
    }
}

void ColoringAlloc::rewriteProgramGR() {
    for (GR gr: spillWorkListGR) {
        if (spillMappingGR.count(gr) == 0) {
            spillMappingGR[gr] = spillCount * 4 + function->stackSize;
            spillCount++;
        }
    }
    std::set<GR> newTemps;
//    std::cerr << "enter rewrite\n";
    int load = 0;
    int store = 0;
    for (BasicBlock* block:function->basicBlocks) {
        for (auto it = block->getInstrs().begin();it != block->getInstrs().end();it++) {
            Instr* instr = *it;
            int new_load_cnt = 0;
            for (GR gr:instr->getUseG()) {
                if (spillWorkListGR.count(gr) != 0) {
                    GR new_gr = GR::allocateReg();
                    newTemps.insert(new_gr);
                    it = block->getInstrs().insert(it, new Load(new_gr, GR(13), spillMappingGR[gr]));
                    instr->setNewGR(gr, new_gr,true);
                    new_load_cnt++;
                    load++;
                }
            }
            it = it + new_load_cnt;
            int new_store_cnt = 0;
            for (GR gr:instr->getDefG()) {
                if (spillWorkListGR.count(gr) != 0) {
                    GR new_gr = GR::allocateReg();
                    newTemps.insert(new_gr);
                    it = block->getInstrs().insert(it+1, new Store(new_gr, GR(13), spillMappingGR[gr]));
                    instr->setNewGR(gr, new_gr, false);
                    new_store_cnt++;
                    store++;
                }
            }
        }
    }
//    for (BasicBlock* block:function->basicBlocks) {
//        for (auto it = block->getInstrs().begin();it != block->getInstrs().end();it++) {
//            Instr* instr = *it;
//            for (GR gr:instr->getUseG()) {
//                if (spillWorkListGR.count(gr) != 0) {
//                    std::cerr << "error!\n";
//                }
//            }
//            for (GR gr:instr->getDefG()) {
//                if (spillWorkListGR.count(gr) != 0) {
//                    std::cerr << "error!\n";
//                }
//            }
//        }
//    }
//    std::cerr << "new load: " << load << "\n";
//    std::cerr << "new store " << store << "\n";
//    std::cerr << "exit rewrite\n";

//    for (GR gr:coloredNodesGR) {
//        grs.insert(gr);
//    }
//    for (GR gr:coalescedNodesGR) {
//        grs.insert(gr);
//    }
//    for (GR gr:newTemps) {
//        grs.insert(gr);
//    }
    grs.clear();
    grIG.clear();
    liveInI.clear();
    liveOutI.clear();
    defI.clear();
    useI.clear();
    preColoredGR.clear();
    simplifyWorkListGR.clear();
    workListMovesGR.clear();
    freezeWorkListGR.clear();
    spillWorkListGR.clear();
    moveListGR.clear();
    activeMovesGR.clear();
    coalescedMovesGR.clear();
    constrainedMovesGR.clear();
    frozenMovesGR.clear();
    adjSetGR.clear();
    adjListGR.clear();
    degreeGR.clear();
    while(!stackGR.empty()) {
        stackGR.pop();
    }
    coloredNodesGR.clear();
    coalescedNodesGR.clear();
    aliasGR.clear();
    colorGR.clear();
}

void ColoringAlloc::rewriteProgramFR() {
    for (FR fr: spillWorkListFR) {
        if (spillMappingFR.count(fr) == 0) {
            spillMappingFR[fr] = spillCount * 4 + function->stackSize;
            spillCount++;
        }
    }
    std::set<FR> newTemps;
//    std::cerr << "enter rewrite\n";
    int load = 0;
    int store = 0;
    for (BasicBlock* block:function->basicBlocks) {
        for (auto it = block->getInstrs().begin();it != block->getInstrs().end();it++) {
            Instr* instr = *it;
            int new_load_cnt = 0;
            for (FR fr:instr->getUseF()) {
                if (spillWorkListFR.count(fr) != 0) {
                    FR new_fr = FR::allocateReg();
                    newTemps.insert(new_fr);
                    it = block->getInstrs().insert(it, new VLoad(new_fr, GR(13), spillMappingFR[fr]));
                    instr->setNewFR(fr, new_fr,true);
                    new_load_cnt++;
                    load++;
                }
            }
            it = it + new_load_cnt;
            int new_store_cnt = 0;
            for (FR fr:instr->getDefF()) {
                if (spillWorkListFR.count(fr) != 0) {
                    FR new_fr = FR::allocateReg();
                    newTemps.insert(new_fr);
                    it = block->getInstrs().insert(it+1, new VStore(new_fr, GR(13), spillMappingFR[fr]));
                    instr->setNewFR(fr, new_fr, false);
                    new_store_cnt++;
                    store++;
                }
            }
        }
    }
//    std::cerr << "new load: " << load << "\n";
//    std::cerr << "new store " << store << "\n";
//    std::cerr << "exit rewrite\n";
    frs.clear();
    for (FR fr:coloredNodesFR) {
        frs.insert(fr);
    }
    for (FR fr:coalescedNodesFR) {
        frs.insert(fr);
    }
    for (FR fr:newTemps) {
        frs.insert(fr);
    }
    frs.clear();
    frIG.clear();
    liveInF.clear();
    liveOutF.clear();
    defF.clear();
    useF.clear();
    preColoredFR.clear();
    simplifyWorkListFR.clear();
    workListMovesFR.clear();
    freezeWorkListFR.clear();
    spillWorkListFR.clear();
    moveListFR.clear();
    activeMovesFR.clear();
    coalescedMovesFR.clear();
    constrainedMovesFR.clear();
    frozenMovesFR.clear();
    adjSetFR.clear();
    adjListFR.clear();
    degreeFR.clear();
    while(!stackFR.empty()) {
        stackFR.pop();
    }
    coloredNodesFR.clear();
    coalescedNodesFR.clear();
    aliasFR.clear();
    colorFR.clear();
}