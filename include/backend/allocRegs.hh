//
// Created by hangshu on 22-7-13.
//

#ifndef SYSY2022_BJTU_ALLOCREGS_HH
#define SYSY2022_BJTU_ALLOCREGS_HH
#include "Function.hh"
#include <map>
#include <set>
#include "instr.hh"
#include <stack>
class ColoringAlloc {
private:
    Function* function;
    std::set<GR> grs;
    std::set<FR> frs;
    std::map<GR, std::set<GR>> grIG;
    std::map<FR, std::set<FR>> frIG;
    std::map<BasicBlock*, std::set<GR>> liveInI,liveOutI,defI,useI;
    std::map<BasicBlock*, std::set<FR>> liveInF,liveOutF,defF,useF;
    std::set<GR> preColoredGR;
    std::set<FR> preColoredFR;
    std::set<GR> simplifyWorkListGR;
    std::set<FR> simplifyWorkListFR;
    std::set<Instr*> workListMovesGR;
    std::set<Instr*> workListMovesFR;
    std::set<GR> freezeWorkListGR;
    std::set<FR> freezeWorkListFR;
    std::set<GR> spillWorkListGR;
    std::set<FR> spillWorkListFR;
    std::map<GR, std::set<Instr*>> moveListGR;
    std::map<FR, std::set<Instr*>> moveListFR;
    std::set<Instr*> activeMovesGR;
    std::set<Instr*> activeMovesFR;
    std::set<Instr*> coalescedMovesGR;
    std::set<Instr*> coalescedMovesFR;
    std::set<Instr*> constrainedMovesGR;
    std::set<Instr*> constrainedMovesFR;
    std::set<Instr*> frozenMovesGR;
    std::set<Instr*> frozenMovesFR;
    std::set<std::pair<GR,GR>> adjSetGR;
    std::set<std::pair<FR,FR>> adjSetFR;
    std::map<GR, std::set<GR>> adjListGR;
    std::map<FR, std::set<FR>> adjListFR;
    std::map<GR, int> degreeGR;
    std::map<FR, int> degreeFR;
    std::stack<GR> stackGR;
    std::stack<FR> stackFR;
    std::set<GR> coloredNodesGR;
    std::set<FR> coloredNodesFR;
    std::set<GR> coalescedNodesGR;
    std::set<FR> coalescedNodesFR;
    std::map<GR, GR> aliasGR;
    std::map<FR, FR> aliasFR;
    std::map<GR, int> colorGR;
    std::map<FR, int> colorFR;
    int KGR = 12;
    int KFR = 32; 
    int spillCount = 0;
    std::map<GR, int> spillMappingGR;
    std::map<FR, int> spillMappingFR;
public:
    ColoringAlloc(Function* function):function(function){}
    int run();
    void liveAnalysis();
    void build();
    void addEdgeGR(GR lhs,GR rhs);
    void addEdgeFR(FR lhs,FR rhs);
    void makeWorkList();
    bool moveRelatedGR(GR gr);
    bool moveRelatedFR(FR fr);
    std::set<Instr*> nodeMovesGR(GR gr);
    std::set<Instr*> nodeMovesFR(FR fr);
    std::set<GR> adjacentGR(GR gr);
    std::set<FR> adjacentFR(FR fr);
    void decrementDegreeGR(GR gr);
    void decrementDegreeFR(FR fr);
    void enableMovesGR(std::set<GR> nodesGR);
    void enableMovesFR(std::set<FR> nodesFR);
    void simplifyGR();
    void simplifyFR();
    void addWorkListGR(GR gr);
    void addWorkListFR(FR fr);
    void coalesceGR();
    void coalesceFR();
    GR getAliasGR(GR gr);
    FR getAliasFR(FR fr);
    bool okGR(GR t,GR r);
    bool okFR(FR t,FR r);
    bool conservativeGR(std::set<GR> nodesGR);
    bool conservativeFR(std::set<FR> nodesFR);
    void combineGR(GR u, GR v);
    void combineFR(FR u, FR v);
    void freezeGR();
    void freezeFR();
    void freezeMovesGR(GR u);
    void freezeMovesFR(FR u);
    void selectSpillGR();
    void selectSpillFR();
    void assignColorsGR();
    void assignColorsFR();
    std::map<GR, int> getColorGR(){return colorGR;}
    std::map<FR, int> getColorFR(){return colorFR;}
    void rewriteProgramGR();
    void rewriteProgramFR();
};
#endif //SYSY2022_BJTU_ALLOCREGS_HH
