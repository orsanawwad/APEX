#ifndef APEX_TOKEN_H
#define APEX_TOKEN_H

#include <string>

/**
 * Used for shunting yard.
 */
class Token {
public:
    enum Type {
        Unknown = 0,
        Number,
        Operator,
        LeftParen,
        RightParen,
        Variable,
    };

    /**
     * A constructor.
     * @param t type.
     * @param s string.
     * @param prec precedence.
     * @param ra  right associative.
     */
    Token(Type t, const std::string &s, int prec = -1, bool ra = false)
            : type{t}, str(s), precedence{prec}, rightAssociative{ra} {}

    Type type{Type::Unknown};
    std::string str{};
    int precedence{-1};
    bool rightAssociative{false};
};


#endif //APEX_TOKEN_H
