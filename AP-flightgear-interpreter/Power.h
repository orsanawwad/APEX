#ifndef APEX_POWER_H
#define APEX_POWER_H


#include "BinaryExpression.h"

class Power : public BinaryExpression {
public:

    Power(Expression *ex1, Expression *ex2);

    virtual double calculate();
};


#endif //APEX_POWER_H
