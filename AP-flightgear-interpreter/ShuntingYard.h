#ifndef APEX_SHUNTINGYARD_H
#define APEX_SHUNTINGYARD_H


#define TOKEN_ERROR "Token error"

#define EXTRACT_EXP_ERROR "Error parsing expression"

#include <iosfwd>
#include <ostream>
#include <deque>
#include <string>
#include <vector>
#include <memory>
#include "Token.h"
#include "Expression.h"

class ShuntingYard {
private:
    bool validateNumber(std::string value);

    ShuntingYard();

public:

    ShuntingYard(ShuntingYard const &) = delete;

    void operator=(ShuntingYard const &) = delete;

    static std::shared_ptr<ShuntingYard> getInstance() {
        static std::shared_ptr<ShuntingYard> s{new ShuntingYard};
        return s;
    }

    /**
     * this method takes the vector of strings(exp) and returns a tokens.
     * @param begin of the vector.
     * @param end the end of the vector.
     * @return a deque with tokens.
     */
    std::deque<Token> exprToTokens(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);

    /**
     * This method returns a deque of tokens.
     * @param tokens
     * @return
     */
    std::deque<Token> shuntingYard(const std::deque<Token> &tokens);

    /**
     * This method returns exp* after created.
     * @param begin the start of the vector.
     * @param end the end of the vector.
     * @return expression* after creating it.
     */
    Expression *parseExpression(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);


};


#endif //APEX_SHUNTINGYARD_H
