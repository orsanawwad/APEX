#ifndef APEX_PROGRAM_H
#define APEX_PROGRAM_H


#include <stdio.h>
#include <iostream>
#include "Parser.h"
#include "Lexer.h"

class Program {
    Program();

public:
    Program(Program const &) = delete;

    void operator=(Program const &) = delete;

    /**
     * Get parser instance.
     */
    Parser *mainParser = Parser::getInstance().get();
    /**
     * Get lexer instance.
     */
    Lexer *mainLexer = Lexer::getInstance().get();

    /**
     * Singleton design
     * @return return one and only instance of this object.
     */
    static std::shared_ptr<Program> getInstance() {
        static std::shared_ptr<Program> s{new Program};
        return s;
    }

    /**
     * Get values from the main.
     * @param argc
     * @param argv
     */
    void launchProgram(int argc, char **argv);

    /**
     * Given a filepath, run the file.
     * @param path
     */
    void processFile(std::string path);
};


#endif //APEX_PROGRAM_H
