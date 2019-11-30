#include "Neg.h"

Neg::Neg(Expression *expression) : UnaryExpression(expression) {}

double Neg::calculate() {
    return -(this->expression->calculate());
}
