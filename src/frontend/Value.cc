#include "Value.hh"

Use::Use(Value* Val, User* U, int arg) : Val(Val), U(U), arg(arg) {
    if(Val) Val->addUse(this);
}

Use::Use() {
    this->Val = nullptr;
    this->U = nullptr;
    this->arg = -1;
}