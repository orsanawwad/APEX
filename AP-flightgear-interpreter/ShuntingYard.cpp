#include "ShuntingYard.h"
#include "Token.h"
#include "DBEngine.h"
#include "Expression.h"
#include "Number.h"
#include "Minus.h"
#include "Plus.h"
#include "Mul.h"
#include "Neg.h"
#include "Div.h"
#include "Var.h"
#include "Power.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <stdio.h>
#include <cmath>

#define SYNTAX_ERROR "Syntax Error!"
#define DOUBLE_PARSE_ERROR "Could not parse double word"

using namespace std;


std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << token.str;
    return os;
}


/**
 * Get tokens of expression
 * @param begin
 * @param end
 * @return
 */
std::deque<Token> ShuntingYard::exprToTokens(std::vector<std::string>::iterator &begin,
                                             std::vector<std::string>::iterator &end) {
    std::deque<Token> tokens;

    bool isNumber = false;

    while (begin != end) {
        const auto *p = begin->c_str();

        if (DBEngine::getInstance().get()->symbolExist(*begin)) {
            if (isNumber) {
                break;
            }
            isNumber = true;
            const auto s = std::string(*begin);
            tokens.push_back(Token{Token::Type::Variable, s});
        } else if (validateNumber(*begin)) {
            if (isNumber) {
                break;
            } else {
                isNumber = true;
            }
            const auto s = std::string(*begin);
            tokens.push_back(Token{Token::Type::Number, s});
        } else {
            Token::Type t = Token::Type::Unknown;
            int pr = -1;            // precedence
            bool ra = false;        // rightAssociative
            bool doNotAdd = false;
            switch (*p) {
                case '(':
                    t = Token::Type::LeftParen;
                    break;
                case ')':
                    t = Token::Type::RightParen;
                    break;
                case '^':
                    t = Token::Type::Operator;
                    pr = 4;
                    ra = true;
                    isNumber = false;
                    break;
                case '*':
                    t = Token::Type::Operator;
                    pr = 3;
                    isNumber = false;
                    break;
                case '/':
                    t = Token::Type::Operator;
                    pr = 3;
                    isNumber = false;
                    break;
                case '+':
                    t = Token::Type::Operator;
                    pr = 2;
                    isNumber = false;
                    break;
                case '-':
                    t = Token::Type::Operator;
                    pr = 2;
                    isNumber = false;
                    break;
                default:
                    doNotAdd = true;
                    break;
            }
            if (!doNotAdd) {
                tokens.push_back(Token{
                        t, std::string(1, *p), pr, ra
                });
            } else {
                break;
            }
        }
        std::advance(begin, 1);
    }
    return tokens;
}


/**
 * Initiate the shunting yard process and return a stack
 * @param tokens
 * @return
 */
std::deque<Token> ShuntingYard::shuntingYard(const std::deque<Token> &tokens) {
    std::deque<Token> queue;
    std::vector<Token> stack;

    // While there are tokens to be read:
    for (auto token : tokens) {
        // Read a token
        switch (token.type) {
            case Token::Type::Number:
                // If the token is a number, then add it to the output queue
                queue.push_back(token);
                break;

            case Token::Type::Variable:
                // If the token is a variable, then add it to the output queue
                queue.push_back(token);
                break;

            case Token::Type::Operator: {
                // If the token is operator, o1, then:
                const auto o1 = token;

                // while there is an operator token,
                while (!stack.empty()) {
                    // o2, at the top of stack, and
                    const auto o2 = stack.back();

                    // either o1 is left-associative and its precedence is
                    // *less than or equal* to that of o2,
                    // or o1 if right associative, and has precedence
                    // *less than* that of o2,
                    if (
                            (!o1.rightAssociative && o1.precedence <= o2.precedence)
                            || (o1.rightAssociative && o1.precedence < o2.precedence)
                            ) {
                        // then pop o2 off the stack,
                        stack.pop_back();
                        // onto the output queue;
                        queue.push_back(o2);

                        continue;
                    }
                    break;
                }

                // push o1 onto the stack.
                stack.push_back(o1);
            }
                break;

            case Token::Type::LeftParen:
                // If token is left parenthesis, then push it onto the stack
                stack.push_back(token);
                break;

            case Token::Type::RightParen:
                // If token is right parenthesis:
            {
                bool match = false;
                // Until the token at the top of the stack
                // is a left parenthesis,
                // pop operators off the stack
                // onto the output queue.
                while (!stack.empty() && stack.back().type != Token::Type::LeftParen) {
                    queue.push_back(stack.back());
                    stack.pop_back();
                    match = true;
                }

                // Pop the left parenthesis from the stack,
                // but not onto the output queue.
                stack.pop_back();

                if (!match && stack.empty()) {
                    // If the stack runs out without finding a left parenthesis,
                    // then there are mismatched parentheses.
                    //std::cout << "RightParen error (" << token.str << ")\n";
                    return {};
                }

            }
                break;

            default:
                throw SYNTAX_ERROR;
        }
    }

    // When there are no more tokens to read:
    //   While there are still operator tokens in the stack:
    while (!stack.empty()) {
        // If the operator token on the top of the stack is a parenthesis,
        // then there are mismatched parentheses.
        if (stack.back().type == Token::Type::LeftParen) {
            throw SYNTAX_ERROR;
        }

        // Pop the operator onto the output queue.
        queue.push_back(std::move(stack.back()));
        stack.pop_back();
    }
    return queue;
}


/**
 * Evaluate and create expression object and return it
 * @param begin
 * @param end
 * @return
 */
Expression *ShuntingYard::parseExpression(std::vector<std::string>::iterator &begin,
                                          std::vector<std::string>::iterator &end) {
    const auto tokens = exprToTokens(begin, end);
    auto queue = shuntingYard(tokens);
    std::vector<Expression *> stack;
    std::deque<Token> unaryStack;

    while (!queue.empty()) {

        const auto token = queue.front();
        queue.pop_front();
        switch (token.type) {
            case Token::Type::Number:
                try {
                    stack.push_back(new Number(std::stod(token.str)));
                }
                catch (...) {
                    throw DOUBLE_PARSE_ERROR;
                }
                break;

            case Token::Type::Variable:
                stack.push_back(new Var(token.str));
                break;

            case Token::Type::Operator: {

                bool isUnary = false;
                if (stack.size() == 1) {
                    isUnary = true;
                }
                Expression *rhs = stack.back();
                stack.pop_back();
                Expression *lhs = NULL;
                if (!isUnary) {
                    lhs = stack.back();
                    stack.pop_back();
                }

                switch (token.str[0]) {
                    default:
                        throw SYNTAX_ERROR;
                    case '^':
                        stack.push_back(new Power(lhs, rhs));
                        break;
                    case '*':
                        stack.push_back(new Mul(lhs, rhs));
                        break;
                    case '/':
                        stack.push_back(new Div(lhs, rhs));
                        break;
                    case '+':
                        stack.push_back(new Plus(lhs, rhs));
                        break;
                    case '-':
                        if (isUnary) {
                            stack.push_back(new Neg(rhs));
                        } else {
                            stack.push_back(new Minus(lhs, rhs));
                        }
                        break;
                }
            }
                break;

            default:
                cout << TOKEN_ERROR << endl;
                throw TOKEN_ERROR;
        }
    }

    if (stack.size() != 1) {
        throw EXTRACT_EXP_ERROR;
    } else {
        return stack[0];
    }
}

ShuntingYard::ShuntingYard() {}

/**
 * Simple number check.
 * @param value
 * @return
 */
bool ShuntingYard::validateNumber(std::string value) {
    for (char &c : value) {
        int a = c - '0';
        if (a < 0 || a > 9) {
            return false;
        }
    }
    return true;
}
