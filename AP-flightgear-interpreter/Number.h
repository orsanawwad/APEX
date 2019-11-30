#ifndef APEX_NUMBER_H
#define APEX_NUMBER_H


#include "Expression.h"

class Number : public Expression {
private:
    double value;
public:
    Number(double value);

    virtual double calculate();
};


#endif //APEX_NUMBER_H
