#ifndef APEX_PARSER_H
#define APEX_PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include "string"
#include "Command.h"
#include "DBEngine.h"

class Parser {
private:
    Parser();

public:
    /**
     * The parser constructor.
     */
    Parser(Parser const &) = delete;

    void operator=(Parser const &) = delete;

    static std::shared_ptr<Parser> getInstance() {
        static std::shared_ptr<Parser> s{new Parser};
        return s;
    }

/**
 * This method run the parse procces.
 */
    void parse(std::vector<std::string> lexerOutput);
};


#endif //APEX_PARSER_H
