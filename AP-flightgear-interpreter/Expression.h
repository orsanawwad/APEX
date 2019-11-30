#ifndef APEX_EXPRESSION_H
#define APEX_EXPRESSION_H


class Expression {
public:
    /**
     * This function calculate the expression.
     * @return the expression after calculating.
     */
    virtual double calculate() = 0;

    virtual ~Expression() {}
};


#endif //APEX_EXPRESSION_H
