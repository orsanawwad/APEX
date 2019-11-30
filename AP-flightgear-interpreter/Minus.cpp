#include "Minus.h"

double Minus::calculate() {
    return (this->ex1->calculate() - this->ex2->calculate());
}

Minus::Minus(Expression *ex1, Expression *ex2) : BinaryExpression(ex1, ex2) {}
