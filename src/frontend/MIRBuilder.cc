//
// Created by lin on 2022/7/3.
//
//Created by lin 5.22
#include "MIRBuilder.hh"
#include "Function.hh"
#include <algorithm>

std::vector<BasicBlock*> MIRBuilder::relatedCond(std::vector<BasicBlock*> bbs, BasicBlock* firstBB, BasicBlock* nextAB){
    BasicBlock* lastOrBB = nextAB;
    dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->trueBB = firstBB;
    dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->falseBB = nextAB;
    CondBlock* condBlock = dynamic_cast<CondBlock*>(bbs[bbs.size()-1]);
    if (condBlock->val.getVal()) {
        condBlock->ir.push_back(new BranchIR(firstBB,nextAB,condBlock->val.getVal()));
    } else if (condBlock->val.getConst() != 0){
        condBlock->ir.push_back(new JumpIR(firstBB));
    } else {
        condBlock->ir.push_back(new JumpIR(nextAB));
    }
//    dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->
//            ir.push_back(new BranchIR(firstBB, nextAB, dynamic_cast<CondBlock*>(bbs[bbs.size()-1])->val));

    for(int i = bbs.size() - 2; i >= 0; --i){
        if(dynamic_cast<CondBlock*>(bbs[i])->isAnd){
            dynamic_cast<CondBlock*>(bbs[i])->trueBB = bbs[i+1];
            dynamic_cast<CondBlock*>(bbs[i])->falseBB = lastOrBB;
            CondBlock* cb = dynamic_cast<CondBlock*>(bbs[i]);
            if (cb->val.getVal()) {
                cb->ir.push_back(new BranchIR(bbs[i+1],lastOrBB,cb->val.getVal()));
            } else if (cb->val.getConst() != 0){
                cb->ir.push_back(new JumpIR(bbs[i+1]));
            } else {
                cb->ir.push_back(new JumpIR(lastOrBB));
            }
        } else{
            dynamic_cast<CondBlock*>(bbs[i])->trueBB = firstBB;
            dynamic_cast<CondBlock*>(bbs[i])->falseBB = bbs[i+1];
            CondBlock* cb = dynamic_cast<CondBlock*>(bbs[i]);
            if (cb->val.getVal()) {
                cb->ir.push_back(new BranchIR(firstBB,bbs[i+1],cb->val.getVal()));
            } else if (cb->val.getConst() != 0){
                cb->ir.push_back(new JumpIR(firstBB));
            } else {
                cb->ir.push_back(new JumpIR(bbs[i+1]));
            }
            if(i+1<bbs.size()){
                lastOrBB = bbs[i+1];
            }
        }
    }
    return bbs;
}

std::vector<BasicBlock*> MIRBuilder::relatedContinueBreak(std::vector<BasicBlock*> bbs, BasicBlock* firstCond, BasicBlock* nextAB) {
    if(!bbs.empty()){
        for(size_t i = 0; i < bbs.size(); i++){
            if(typeid(*bbs[i]) == typeid(IterationBlock)){
                continue;
            } else if(typeid(*bbs[i]) == typeid(SelectBlock)){
                dynamic_cast<SelectBlock*>(bbs[i])->ifStmt =
                        relatedContinueBreak(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt, firstCond, nextAB);
                dynamic_cast<SelectBlock*>(bbs[i])->elseStmt =
                        relatedContinueBreak(dynamic_cast<SelectBlock*>(bbs[i])->elseStmt, firstCond, nextAB);
            }else if(typeid(*bbs[i]) == typeid(NormalBlock)){
                ReturnOfRelated* ro = relatedIR(dynamic_cast<NormalBlock*>(bbs[i])->ir);
                switch (ro->type) {
                    case 1:
                        dynamic_cast<NormalBlock*>(bbs[i])->nextBB = nextAB;
                        dynamic_cast<NormalBlock*>(bbs[i])->
                                ir.erase(std::begin(dynamic_cast<NormalBlock*>(bbs[i])->ir)+ro->index,
                                         std::end(dynamic_cast<NormalBlock*>(bbs[i])->ir));
                        break;
                    case 2:
                        dynamic_cast<NormalBlock*>(bbs[i])->nextBB = firstCond;
                        dynamic_cast<NormalBlock*>(bbs[i])->
                                ir.erase(std::begin(dynamic_cast<NormalBlock*>(bbs[i])->ir)+ro->index,
                                         std::end(dynamic_cast<NormalBlock*>(bbs[i])->ir));
                        break;
                }
            }
        }
    }
    return bbs;
}

ReturnOfRelated* MIRBuilder::relatedIR(std::vector<Instruction*> ir){
    for(size_t i = 0; i < ir.size(); i++){
        if(typeid(*ir[i]) == typeid(BreakIR)){
            return new ReturnOfRelated(1, i); //on behalf of break
        } else if(typeid(*ir[i]) == typeid(ContinueIR)){
            return new ReturnOfRelated(2, i); //on behalf of continue
        } else if(typeid(*ir[i]) == typeid(ReturnIR)){
            return new ReturnOfRelated(3, i);
        }
    }
    return new ReturnOfRelated(0, 0); //nothing
}

BasicBlock* MIRBuilder::frontOfNextBB(BasicBlock* bb){
    if (!bb)
        return NULL;
    if(typeid(*bb) == typeid(SelectBlock)){
        return dynamic_cast<SelectBlock*>(bb)->cond.front();
    }else if(typeid(*bb) == typeid(IterationBlock)){
        return dynamic_cast<IterationBlock*>(bb)->cond.front();
    } else if(typeid(*bb) == typeid(NormalBlock)){
        return bb;
    }
    return bb;
}

//end by lin

//create by lin 7.2
void MIRBuilder::getPreAndSucc(){
    //std::cout<<"begin pre and succ:"<<std::endl;
    std::vector<Function*> functions = irVisitor.functions;
    for (size_t i = 0; i < functions.size(); ++i) {
        if (functions[i]->basicBlocks.empty()) continue;
        if (functions[i]->return_type->isVoid()) {
            if (typeid(*functions[i]->basicBlocks.back()) != typeid(NormalBlock)) {    // solve problem of void
                functions[i]->basicBlocks.
                        push_back(new NormalBlock(nullptr, functions[i]->name, functions[i]->bbCnt++));
            }
            functions[i]->basicBlocks.back()->ir.push_back(new ReturnIR(nullptr));
        }
        functions[i]->basicBlocks = refresh(functions[i]->basicBlocks, NULL);
    }
    removeDuplicate();
    //std::cout<<"end pre and succ:"<<std::endl;
}

std::vector<BasicBlock*> MIRBuilder::refresh(std::vector<BasicBlock*> bbs, BasicBlock* nextAB){
    std::vector<BasicBlock*> newBBs;
    std::vector<BasicBlock*> tempBBs;

    if(bbs.empty()){
        return bbs;
    }
    for(size_t i = 0; i < bbs.size(); i++){
        BasicBlock* nextBB;
        if(i+1<bbs.size()){
            nextBB = frontOfNextBB(bbs[i + 1]);
        }else{
            nextBB = nextAB;
        }

        if(typeid(*bbs[i]) == typeid(SelectBlock)){
            BasicBlock* firstOfIfBB;
            if(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt.empty()){
                firstOfIfBB = nextBB;
            } else{
                firstOfIfBB = frontOfNextBB(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt.front());
            }

            BasicBlock* firstOfElseBB;
            if(dynamic_cast<SelectBlock*>(bbs[i])->elseStmt.empty()){
                firstOfElseBB = nextBB;
            } else{
                firstOfElseBB = frontOfNextBB(dynamic_cast<SelectBlock*>(bbs[i])->elseStmt.front());
            }

            dynamic_cast<SelectBlock*>(bbs[i])->cond = relatedCond(dynamic_cast<SelectBlock*>(bbs[i])->cond, firstOfIfBB, firstOfElseBB);

            tempBBs = refresh(dynamic_cast<SelectBlock*>(bbs[i])->cond, NULL);
            newBBs.insert(newBBs.end(), tempBBs.begin(), tempBBs.end());
            tempBBs = refresh(dynamic_cast<SelectBlock*>(bbs[i])->ifStmt, nextBB);
            newBBs.insert(newBBs.end(), tempBBs.begin(), tempBBs.end());
            tempBBs = refresh(dynamic_cast<SelectBlock*>(bbs[i])->elseStmt, nextBB);
            newBBs.insert(newBBs.end(), tempBBs.begin(), tempBBs.end());
        } else if(typeid(*bbs[i]) == typeid(IterationBlock)){

            BasicBlock* firstBB;
            if(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt.empty()){
                firstBB = dynamic_cast<IterationBlock*>(bbs[i])->cond.front();
            } else{
                firstBB = frontOfNextBB(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt.front());
            }

            dynamic_cast<IterationBlock*>(bbs[i])->cond = relatedCond(dynamic_cast<IterationBlock*>(bbs[i])->cond, firstBB, nextBB);

            dynamic_cast<IterationBlock*>(bbs[i])->whileStmt =
                    relatedContinueBreak(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt,
                                         dynamic_cast<IterationBlock*>(bbs[i])->cond.front(), nextBB);

            tempBBs = refresh(dynamic_cast<IterationBlock*>(bbs[i])->cond, NULL);
            newBBs.insert(newBBs.end(), tempBBs.begin(), tempBBs.end());
            tempBBs = refresh(dynamic_cast<IterationBlock*>(bbs[i])->whileStmt,
                              dynamic_cast<IterationBlock*>(bbs[i])->cond.front());
            newBBs.insert(newBBs.end(), tempBBs.begin(), tempBBs.end());
        } else if(typeid(*bbs[i]) == typeid(NormalBlock)){     //NormalBlock
            BasicBlock* next;
            if (dynamic_cast<NormalBlock*>(bbs[i])->nextBB) {
                next = dynamic_cast<NormalBlock*>(bbs[i])->nextBB;
            } else {
                next = nextBB;
            }
            NormalBlock* nb = toNormal(next);
            if(nb){
                nb->pushPre(dynamic_cast<NormalBlock*>(bbs[i]));
                dynamic_cast<NormalBlock*>(bbs[i])->pushSucc(nb);
            }

            //  solve return sentence
            dynamic_cast<NormalBlock*>(bbs[i])->ir.push_back(new JumpIR(nb));
            ReturnOfRelated* ro = relatedIR(dynamic_cast<NormalBlock*>(bbs[i])->ir);
            if(ro->type == 3){
                dynamic_cast<NormalBlock*>(bbs[i])->
                        ir.erase(std::begin(dynamic_cast<NormalBlock*>(bbs[i])->ir)+ro->index+1,
                                 std::end(dynamic_cast<NormalBlock*>(bbs[i])->ir));
            }
            newBBs.push_back(dynamic_cast<NormalBlock*>(bbs[i]));
        } else if(typeid(*bbs[i]) == typeid(CondBlock)){
            newBBs.push_back(toNormal(bbs[i]));
        }
    }
    return newBBs;
}

NormalBlock* MIRBuilder::toNormal(BasicBlock* bb){
    if(bb == NULL){
        return NULL;
    }
    std::string func_name = bb->name;
    std::string num = func_name.substr(func_name.find("::BB")+4);
    func_name = func_name.substr(0, func_name.find(':'));

    NormalBlock* nb = new NormalBlock(nullptr, func_name, atoi(num.c_str()));

    if(typeid(*bb) == typeid(NormalBlock)){
        return dynamic_cast<NormalBlock*>(bb);
    } else{                                         //CondBlock
        if(getCondToNormal(dynamic_cast<CondBlock*>(bb))){
            nb = getCondToNormal(dynamic_cast<CondBlock*>(bb));
        }
        nb->ir = bb->ir;

        std::vector<NormalBlock*> reversed = reversedSucc[dynamic_cast<CondBlock*>(bb)];
        if(reversed.size() != 0){         //  check reversed station
            for(int i = 0; i < reversed.size(); i++){
                reversed[i]->pushSucc(nb);
                nb->pushPre(reversed[i]);
            }
        }

        putCondToNormal(dynamic_cast<CondBlock*>(bb), nb);

        BasicBlock* succ = dynamic_cast<CondBlock*>(bb)->trueBB;            //solve trueBB
        if(succ){
            if(typeid(*succ) == typeid(CondBlock)){
                if(getCondToNormal(dynamic_cast<CondBlock*>(succ))){
                    succ = getCondToNormal(dynamic_cast<CondBlock*>(succ));
                    dynamic_cast<NormalBlock*>(succ)->pushPre(nb);
                    nb->pushSucc(dynamic_cast<NormalBlock*>(succ));
                } else{
                    reversedSucc[dynamic_cast<CondBlock*>(succ)].push_back(nb);
                }
            } else{
                dynamic_cast<NormalBlock*>(succ)->pushPre(nb);
                nb->pushSucc(dynamic_cast<NormalBlock*>(succ));
            }
        }

        succ = dynamic_cast<CondBlock*>(bb)->falseBB;                       //solve falseBB
        if(succ){
            if(typeid(*succ) == typeid(CondBlock)){
                if(getCondToNormal(dynamic_cast<CondBlock*>(succ))){
                    succ = getCondToNormal(dynamic_cast<CondBlock*>(succ));
                    dynamic_cast<NormalBlock*>(succ)->pushPre(nb);
                    nb->pushSucc(dynamic_cast<NormalBlock*>(succ));
                } else{
                    reversedSucc[dynamic_cast<CondBlock*>(succ)].push_back(nb);
                }
            } else{
                dynamic_cast<NormalBlock*>(succ)->pushPre(nb);
                nb->pushSucc(dynamic_cast<NormalBlock*>(succ));
            }
        }

//        std::cout<<nb->name<<std::endl;
    }
    return nb;
}

void MIRBuilder::print(std::ostream& out){
    irVisitor.print(std::cout);
}
//end by lin 7.2
//create by lin 7.3
NormalBlock* MIRBuilder::getCondToNormal(CondBlock *cb){
    return condToNormal[cb];
}

void MIRBuilder::putCondToNormal(CondBlock* cb, NormalBlock* nb){
    condToNormal[cb] = nb;
//    std::cout<<getCondToNormal(cb)->name<<std::endl;
}

void MIRBuilder::removeDuplicate(){
    for(size_t i = 0; i < irVisitor.functions.size(); i++){
        std::vector<BasicBlock*> bbs = irVisitor.functions[i]->basicBlocks;
        if (bbs.empty()) continue;
        //std::cout<<bbs.size()<<std::endl;
        for(size_t j = bbs.size() - 1; j > 0 ; j--){
            NormalBlock* nowNB = dynamic_cast<NormalBlock*>(bbs[j]);
            if(nowNB->getPre().size() == 1){
                NormalBlock* preNB = dynamic_cast<NormalBlock*>(*nowNB->getPre().begin());
                if(preNB->getSucc().size() == 1){
                    preNB->setSucc(nowNB->getSucc());
                    preNB->ir.pop_back();
                    preNB->ir.insert(preNB->ir.end(), nowNB->ir.begin(), nowNB->ir.end());
                    for (auto succNB:nowNB->getSucc()) {
                        std::vector<BasicBlock*> preBBs(succNB->getPre());
                        preBBs.erase(find(preBBs.begin(), preBBs.end(), nowNB));
                        preBBs.push_back(preNB);
                        succNB->setPre(preBBs);
                    }
                    bbs[j] = preNB;
                    bbs.erase(bbs.begin()+j);
                }
            }
        }
        for (size_t j = 0;j < bbs.size() - 1;j++) {
            NormalBlock* nowNB = dynamic_cast<NormalBlock*>(bbs[j]);
            if (nowNB->ir.empty()) continue;
            if (typeid(*(nowNB->ir.back())) == typeid(BranchIR)) {
                BranchIR* branchIr = dynamic_cast<BranchIR*>(nowNB->ir.back());
                if (branchIr->trueTarget == branchIr->falseTarget) {
                    nowNB->ir.pop_back();
                    nowNB->ir.push_back(new JumpIR(branchIr->trueTarget));
                }
            }
            if (typeid(*(nowNB->ir.back())) == typeid(JumpIR)) {
                if (dynamic_cast<JumpIR*>(nowNB->ir.back())->target->name == bbs[j+1]->name){
                    nowNB->ir.pop_back();
                }
            }
        }
        irVisitor.functions[i]->basicBlocks = bbs;
    }
}
//end by lin 7.3