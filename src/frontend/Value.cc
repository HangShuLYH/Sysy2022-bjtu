#include "Value.hh"

Use::Use(Value* Val, User* U) : Val(Val), U(U) {
    if(Val) Val->addUse(this);
}

Use::Use() {
    this->Val = nullptr;
    this->U = nullptr;
}