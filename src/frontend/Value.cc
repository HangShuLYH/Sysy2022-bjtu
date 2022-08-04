#include "Value.hh"

Use::Use(Value* Val, User* U, int arg) : Val(Val), U(U), arg(arg) {
    this->bb = nullptr;
    // if(Val) Val->addUse(this);
}

Use::Use(Value* Val, User* U, BasicBlock* bb) : Val(Val), U(U), bb(bb) {
    this->arg = -1;
    // if(Val) Val->addUse(this);
}

Use::Use() {
    this->Val = nullptr;
    this->U = nullptr;
    this->arg = -1;
}