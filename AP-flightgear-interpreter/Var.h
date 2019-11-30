#ifndef APEX_VAR_H
#define APEX_VAR_H

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Expression.h"

using namespace std;

class Var : public Expression {
private:
    string var;
public:
    /**
     * Var constructor.
     */
    Var(const string &var);

/**
 * returns the var given.
 * @return this var.
 */
    virtual double calculate();
};


#endif //APEX_VAR_H
