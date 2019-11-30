#ifndef APEX_NEG_H
#define APEX_NEG_H


#include "UnaryExpression.h"

class Neg : public UnaryExpression {
public:
    Neg(Expression *expression);

    virtual double calculate();
};


#endif //APEX_NEG_H
