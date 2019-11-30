#ifndef APEX_BINARYEXPRESSION_H
#define APEX_BINARYEXPRESSION_H


#include "Expression.h"

/**
 * Binary operator container.
 */
class BinaryExpression : public Expression {

protected:
    //left expression
    Expression *ex1;
    //right expression
    Expression *ex2;
public:
    /**
     * The binary expression constructor.
     * @param ex1 left
     * @param ex2 right
     */
    BinaryExpression(Expression *ex1, Expression *ex2);

    /**
     * Binary expression destructor.
     */
    virtual ~BinaryExpression();


};


#endif //APEX_BINARYEXPRESSION_H
