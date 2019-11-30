#include "Div.h"

Div::Div(Expression *ex1, Expression *ex2) : BinaryExpression(ex1, ex2) {}

double Div::calculate() {
    return (this->ex1->calculate() / this->ex2->calculate());
}
