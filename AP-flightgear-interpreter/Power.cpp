#include <cmath>
#include "Power.h"

double Power::calculate() {
    return pow(ex1->calculate(), ex2->calculate());
}

Power::Power(Expression *ex1, Expression *ex2) : BinaryExpression(ex1, ex2) {}
