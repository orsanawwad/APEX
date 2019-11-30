#ifndef APEX_DIV_H
#define APEX_DIV_H


#include "BinaryExpression.h"

class Div : public BinaryExpression {
private:

public:


    Div(Expression *ex1, Expression *ex2);

    virtual double calculate();


};


#endif //APEX_DIV_H
