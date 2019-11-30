#ifndef APEX_MINUS_H
#define APEX_MINUS_H


#include "BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus(Expression *ex1, Expression *ex2);

    virtual double calculate();
};


#endif //APEX_MINUS_H
