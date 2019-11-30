#include "Mul.h"

double Mul::calculate() {
    return (this->ex1->calculate() * this->ex2->calculate());
}

Mul::Mul(Expression *ex1, Expression *ex2) : BinaryExpression(ex1, ex2) {}
