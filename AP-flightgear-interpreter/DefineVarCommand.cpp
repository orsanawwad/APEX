#include "DefineVarCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DBEngine.h"
#include "ShuntingYard.h"

void DefineVarCommand::execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {

    //Sanity check
    if (begin == end) {
        perror("Should not happen here...");
    }

    //Prepare instances
    DBEngine *database = DBEngine::getInstance().get();

    std::vector<std::string>::iterator &lexerIterator = begin;

    std::string currentKeyword = *lexerIterator;
    std::string variableName = currentKeyword;
    std::string &firstKeyword = currentKeyword;

    //Used for identifying "var a = 4" or "a = 5"
    bool newVar = false;

    //Lambda function that appends 1 to lexerIterator and get the next token (string)
    auto getNext = [&]() {
        std::advance(lexerIterator, 1);
        currentKeyword = *lexerIterator;
    };
    //In short calling getNext() would just do the above 2 lines, the [&] is used to capture local variables.


    //Lambda function as an alias to the long shunting yard call
    auto getDouble = [&]() -> double {
        return ShuntingYard::getInstance().get()->parseExpression(lexerIterator, end)->calculate();
    };


    //If the command started as a var, check if its already defined, if not, set default one to 0 and mark the flag
    if (firstKeyword == "var") {
        getNext();

        newVar = true;

        if (database->symbolExist(currentKeyword)) {
            throw "VARIABLE ALREADY DEFINED";
        } else {
            database->setSymbol(currentKeyword, 0);
            variableName = currentKeyword;
        }

    } else {
        if (!database->symbolExist(currentKeyword)) {
            throw "VARIABLE NOT DEFINED";
        }
    }

    //Check if its a set command

    getNext();

    if (currentKeyword != "=") {
        if (newVar) {
            return;
        } else {
            throw "Syntax Error";
        }
    }

    getNext();

    //Check if its a bind command

    if (currentKeyword == "bind") {

        getNext();

        //If so parse it set it up

        if (*currentKeyword.begin() == '\"' && currentKeyword.back() == '\"') {
            database->setBind(variableName, std::string(currentKeyword.begin() + 1, currentKeyword.end() - 1));
        } else {
            if (database->bindExist(currentKeyword)) {
                database->setSymbol(variableName, database->getSymbol(currentKeyword));
                database->setBind(variableName, database->getBind(currentKeyword));
            } else {
                throw "ERROR, NOT A BIND TYPE";
            }
        }

    } else {
        //Otherwise parse expression and set it.
        database->setSymbol(variableName, getDouble());
        return;
    }

    getNext();

}

DefineVarCommand::DefineVarCommand() {}
