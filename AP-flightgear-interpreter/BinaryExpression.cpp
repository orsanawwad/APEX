#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression *ex1, Expression *ex2) {
    this->ex1 = ex1;
    this->ex2 = ex2;
}

BinaryExpression::~BinaryExpression() {
    delete this->ex1;
    delete this->ex2;
}
