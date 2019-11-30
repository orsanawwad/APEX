#include "LoopCommand.h"
#include "Expression.h"
#include "Number.h"
#include "DefineVarCommand.h"
#include "DBEngine.h"

void LoopCommand::execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {

    std::vector<std::string>::iterator &lexerIterator = begin;

    std::advance(lexerIterator, 1);

    Expression *leftExpr = getExpression(lexerIterator, end);

    const ConditionType type = parseConditionType(lexerIterator);

    Expression *rightExpr = getExpression(lexerIterator, end);

    auto brackets = getBeginCloseBrackets(lexerIterator, end);

    std::vector<std::string>::iterator openBracket = std::get<0>(brackets);
    std::vector<std::string>::iterator endBracket = std::get<1>(brackets);


    // Main element
    while (this->evaluateCondition(type, leftExpr, rightExpr)) {
        invokeCommands(lexerIterator, end, openBracket, endBracket);
    }
    lexerIterator = endBracket;
    std::advance(lexerIterator, 1);


}

LoopCommand::LoopCommand() {}
