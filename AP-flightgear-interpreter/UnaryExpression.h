#ifndef APEX_UNARYEXPRESSION_H
#define APEX_UNARYEXPRESSION_H


#include "Expression.h"

class UnaryExpression : public Expression {
protected:
    Expression *expression;
public:
    /**
     * A consrucor to an unary expression.
     * @param expression the expression to set.
     */
    UnaryExpression(Expression *expression);

    /**
     * A destructor.
     */
    virtual ~UnaryExpression();

};


#endif //APEX_UNARYEXPRESSION_H
