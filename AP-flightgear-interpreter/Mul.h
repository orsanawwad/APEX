#ifndef APEX_MUL_H
#define APEX_MUL_H


#include "BinaryExpression.h"

class Mul : public BinaryExpression {
public:
    Mul(Expression *ex1, Expression *ex2);

    virtual double calculate();
};


#endif //APEX_MUL_H
