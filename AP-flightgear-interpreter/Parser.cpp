#include "Parser.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "DBEngine.h"
#include "iostream"

#define PRINT_UNKNOWN_COMMAND_ERROR "Syntax Error: Unknown command '" << *lexerIteratorBegin << "'" << std::endl;

Parser::Parser() {}

/**
 * Given a vector, prepare 2 iterators (begin,end), check current begin and pass it to its own command
 * if it not a command try to evaluate it
 *
 * The way this works is by taking 2 iterators, and pass them to each command, and let the commands deal with them.
 *
 * @param lexerOutput
 */
void Parser::parse(std::vector<std::string> lexerOutput) {

    std::unordered_map<std::string, Command *> commands = DBEngine::getInstance().get()->getCommandTable();

    std::vector<std::string>::iterator lexerIteratorBegin;
    std::vector<std::string>::iterator lexerIteratorEnd;
    lexerIteratorBegin = lexerOutput.begin();
    lexerIteratorEnd = lexerOutput.end();

    while (lexerIteratorBegin != lexerOutput.end()) {
        if (commands.find(*lexerIteratorBegin) == commands.end()) {
            if (DBEngine::getInstance().get()->symbolExist(*lexerIteratorBegin)) {
                DefineVarCommand::getInstance().get()->execute(lexerIteratorBegin, lexerIteratorEnd);
            } else {
                if (*lexerIteratorBegin == "") {
                    break;
                }
                std::cout << PRINT_UNKNOWN_COMMAND_ERROR;
                break;
            }
        } else {
            commands[*lexerIteratorBegin]->execute(lexerIteratorBegin, lexerIteratorEnd);
        }
    }


}
