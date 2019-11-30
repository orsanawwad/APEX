#ifndef APEX_CONDITIONPARSER_H
#define APEX_CONDITIONPARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <tuple>

#include "Command.h"
#include "Expression.h"
#include "DBEngine.h"

using namespace std;

class ConditionParser : public Command {


protected:
    ConditionParser();

    enum ConditionType {
        EqualTo,
        GreaterThan,
        LessThan,
        NotEqualTo,
        GreaterThanOrEqualTo,
        LessThatOrEqualTo
    };

    /**
     * The parse condition method takes a iterator for the begin of the vector and return the condition type readen.
     * @param begin the begin of the string iterator.
     * @return the condition type.
     */
    ConditionParser::ConditionType parseConditionType(vector<string>::iterator &begin);

    /**
     * Returns the expression by reading the string from the iterator pointer to.
     * @param begin the begin of the vector.
     * @param end the end of the vector.
     * @return an expression created by the command reader.
     */
    Expression *getExpression(vector<string>::iterator &begin, vector<string>::iterator &end);

    /**
     * Like the parse this is used to go over the commands from lexer and initiate the commands.
     * @param current
     * @param end
     * @param openBracket
     * @param endBracket
     */
    void invokeCommands(vector<string>::iterator &current, vector<string>::iterator &end,
                        vector<string>::iterator &openBracket, vector<string>::iterator &endBracket);

    /**
     *  Get open and end bracket, given a pointer to an open bracket, return as a tuple it's related bracket.
     * @param begin bracket beginning
     * @param end bracked ending
     * @return tuple of 2 objects, begin and end iterator pointer
     */
    tuple<vector<string>::iterator, vector<string>::iterator> getBeginCloseBrackets(
            vector<string>::iterator &begin, vector<string>::iterator &end);

    /**
     *  Evaluate expression condition and return its boolean result.
     * @param type logic type
     * @param leftExp
     * @param rightExp
     * @return result of logic operator
     */
    bool evaluateCondition(const ConditionParser::ConditionType &type, Expression *leftExp, Expression *rightExp);

public:
    ConditionParser(ConditionParser const &) = delete;

    void operator=(ConditionParser const &) = delete;

public:
    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {};
};


#endif //APEX_CONDITIONPARSER_H
