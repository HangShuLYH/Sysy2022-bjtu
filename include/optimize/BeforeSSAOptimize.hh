// //
// // Created by hanyangchen on 22-8-1
// //

// #include "IrVisitor.hh"
// #include "Instruction.hh"
// #include "IRManager.hh"
// #include <map>
// #include <stack>
// #include <algorithm>

// class BeforeSSAOptimize {
// private:
//     IrVisitor* irVisitor;
//     Function* function;
// public:
//     BeforeSSAOptimize(IrVisitor* irVisitor) : irVisitor(irVisitor) {;}
//     void execute();
//     void algebraicOptimazation();
// };

// void BeforeSSAOptimize::execute() {
//     std::vector<Function*> functions = irVisitor->getFunctions();
//     for(Function* func : functions) {
//         if(func->getBB().size() == 0) continue;
//         this->function = func;
//         algebraicOptimazation();
//     }
// }

// void BeforeSSAOptimize::algebraicOptimazation() {
//     for(auto bb : function->getBB()) {
//         auto W = bb->getIr();
//         while (!W.empty())
//         {
//             auto inst = *W.rbegin();
//             W.pop_back();

//             if(!inst->isDeleted()) {
//                 ArithmeticIR* ir = nullptr;
//                 if(typeid(*inst) == typeid(AddIIR) || typeid(*inst) == typeid(AddFIR) || typeid(*inst) == typeid(SubIIR) || typeid(*inst) == typeid(SubFIR)) {
//                     ir = dynamic_cast<ArithmeticIR*>(inst);
//                     auto operands = ir->getOperands();
//                     TempVal* res = dynamic_cast<TempVal*>(operands[0]->getVal()), *left = dynamic_cast<TempVal*>(operands[1]->getVal()), *right = dynamic_cast<TempVal*>(operands[2]->getVal());
//                     if(!left->getVal() && left->getConst() == 0) {
//                         if(!right->getVal()) {
//                             res->setVal(nullptr);
//                             res->setConst(right->getConst());
//                         } else {
//                             res->setVal(right->getVal());

//                             for(auto use : res->getVal()->getUses()) {
//                                 if(typeid(*(use->getVal())) != typeid(TempVal)) {
//                                     use->getVal()->killUse(use);
//                                 }

//                                 User* user = use->getUser();
//                                 if(typeid(*user) == typeid(PhiIR)) {
//                                     dynamic_cast<PhiIR*>(user)->params[use->getBB()] = newTemp;
//                                 } else {
//                                     std::vector<Use*> operands = user->getOperands();
//                                     operands[use->getArg()]->setVal(newTemp);
//                                 }
//                                 W.push_back(dynamic_cast<Instruction*>(user));
//                             }
//                         }
//                         ir->deleteIR();

//                     } else if((!right->getVal() && right->getConst() == 0)) {
//                         if(!left->getVal()) {
//                             res->setVal(nullptr);
//                             res->setConst(left->getConst());
//                         } else {
//                             res->setVal(left->getVal());
//                         }
//                         ir->deleteIR();
//                     }
//                 } else if(typeid(*inst) == typeid(MulIIR) || typeid(*inst) == typeid(MulFIR)) {
//                     ir = dynamic_cast<ArithmeticIR*>(inst);
//                     auto operands = ir->getOperands();
//                     TempVal* res = dynamic_cast<TempVal*>(operands[0]->getVal()), *left = dynamic_cast<TempVal*>(operands[1]->getVal()), *right = dynamic_cast<TempVal*>(operands[2]->getVal());
//                     if(!left->getVal() && left->getConst() == 1) {
//                         if(!right->getVal()) {
//                             res->setVal(nullptr);
//                             res->setConst(right->getConst());
//                         } else {
//                             res->setVal(right->getVal());
//                         }
//                         ir->deleteIR();
//                     } else if((!right->getVal() && right->getConst() == 1)) {
//                         if(!left->getVal()) {
//                             res->setVal(nullptr);
//                             res->setConst(left->getConst());
//                         } else {
//                             res->setVal(left->getVal());
//                         }
//                         ir->deleteIR();
//                     }
//                 } else if(typeid(*inst) == typeid(DivIIR) || typeid(*inst) == typeid(DivFIR)) {
//                     ir = dynamic_cast<ArithmeticIR*>(inst);
//                     auto operands = ir->getOperands();
//                     TempVal* res = dynamic_cast<TempVal*>(operands[0]->getVal()), *left = dynamic_cast<TempVal*>(operands[1]->getVal()), *right = dynamic_cast<TempVal*>(operands[2]->getVal());
//                     if((!right->getVal() && right->getConst() == 1)) {
//                         if(!left->getVal()) {
//                             res->setVal(nullptr);
//                             res->setConst(left->getConst());
//                         } else {
//                             res->setVal(left->getVal());
//                         }
//                         ir->deleteIR();
//                     }
//                 }
//             }
//         }
//     }
// }