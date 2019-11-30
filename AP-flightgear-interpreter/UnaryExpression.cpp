#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(Expression *expression) {
    this->expression = expression;
}

UnaryExpression::~UnaryExpression() {
    delete this->expression;
}
