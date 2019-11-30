#ifndef APEX_PLUS_H
#define APEX_PLUS_H


#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    Plus(Expression *ex1, Expression *ex2);

    virtual double calculate();
};


#endif //APEX_PLUS_H
