#include "Var.h"
#include "DBEngine.h"

Var::Var(const string &var) : var(var) {}

double Var::calculate() {
    return DBEngine::getInstance().get()->getSymbol(this->var);
}
