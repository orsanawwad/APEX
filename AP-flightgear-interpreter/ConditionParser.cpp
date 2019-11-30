#include <unordered_map>
#include "ConditionParser.h"
#include "DBEngine.h"
#include "DefineVarCommand.h"
#include "ShuntingYard.h"

ConditionParser::ConditionType ConditionParser::parseConditionType(vector<string>::iterator &begin) {

    std::string type = std::string(*begin);

    std::advance(begin, 1);

    if (type == "==") {
        return ConditionParser::ConditionType::EqualTo;
    } else if (type == ">") {
        return ConditionParser::ConditionType::GreaterThan;
    } else if (type == "<") {
        return ConditionParser::ConditionType::LessThan;
    } else if (type == "!=") {
        return ConditionParser::ConditionType::NotEqualTo;
    } else if (type == ">=") {
        return ConditionParser::ConditionType::GreaterThanOrEqualTo;
    } else if (type == "<=") {
        return ConditionParser::ConditionType::LessThatOrEqualTo;
    } else {
        throw "Operator not supported.";
    }

}

tuple<vector<string>::iterator, vector<string>::iterator>
ConditionParser::getBeginCloseBrackets(vector<string>::iterator &begin, vector<string>::iterator &end) {

    std::vector<std::string>::iterator &lexerIterator = begin;

    std::vector<std::string>::iterator openBracket(lexerIterator);
    std::vector<std::string>::iterator endBracket;

    int bracketsCount = 0;

    if (*openBracket == "{") {

        while (begin != end) {
            std::advance(lexerIterator, 1);
            if (*lexerIterator == "}") {
                if (bracketsCount == 0) {
                    endBracket = std::vector<std::string>::iterator(lexerIterator);
                    break;
                } else if (bracketsCount > 0) {
                    bracketsCount--;
                } else {
                    perror("Syntax error!");
                    throw "ERROR: Syntax Error!";
                }
            } else if (*lexerIterator == "{") {
                bracketsCount++;
            }
        }

        if (lexerIterator == end) {
            perror("ERROR: Syntax Error!");
            throw "ERROR: Syntax Error!";
        }

        lexerIterator = openBracket;
        std::advance(lexerIterator, 1);

    } else {
        perror("ERROR: Syntax Error!");
        throw "ERROR: Syntax Error!";
    }

    return make_tuple(openBracket, endBracket);
}

Expression *ConditionParser::getExpression(vector<string>::iterator &begin, vector<string>::iterator &end) {
    return ShuntingYard::getInstance().get()->parseExpression(begin, end);
}

bool ConditionParser::evaluateCondition(const ConditionParser::ConditionType &type, Expression *leftExp,
                                        Expression *rightExp) {

    switch (type) {
        case ConditionParser::ConditionType::EqualTo:
            return leftExp->calculate() == rightExp->calculate();
        case ConditionParser::ConditionType::GreaterThan:
            return leftExp->calculate() > rightExp->calculate();
        case ConditionParser::ConditionType::LessThan:
            return leftExp->calculate() < rightExp->calculate();
        case ConditionParser::ConditionType::NotEqualTo:
            return leftExp->calculate() != rightExp->calculate();
        case ConditionParser::ConditionType::GreaterThanOrEqualTo:
            return leftExp->calculate() >= rightExp->calculate();
        case ConditionParser::ConditionType::LessThatOrEqualTo:
            return leftExp->calculate() <= rightExp->calculate();
        default:
            throw "Something went wrong";

    }
}

void ConditionParser::invokeCommands(vector<string>::iterator &lexerIterator, vector<string>::iterator &end,
                                     vector<string>::iterator &openBracket, vector<string>::iterator &endBracket) {
    std::unordered_map<std::string, Command *> commands = DBEngine::getInstance().get()->getCommandTable();
    while (lexerIterator != endBracket) {

        if (commands.count(*lexerIterator) == 0) {
            if (DBEngine::getInstance().get()->symbolExist(*lexerIterator)) {
                DefineVarCommand::getInstance().get()->execute(lexerIterator, end);
            } else {
                throw "Syntax Error";
            }
        } else {
            commands[*lexerIterator]->execute(lexerIterator, end);
        }
    }
    lexerIterator = openBracket;
    std::advance(lexerIterator, 1);
}

ConditionParser::ConditionParser() {}
