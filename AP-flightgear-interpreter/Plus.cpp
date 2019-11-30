#include "Plus.h"


double Plus::calculate() {
    return (this->ex1->calculate() + this->ex2->calculate());
}

Plus::Plus(Expression *ex1, Expression *ex2) : BinaryExpression(ex1, ex2) {}

