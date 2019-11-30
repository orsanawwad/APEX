#include "Program.h"
#include <iostream>
#include <thread>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdio.h>

#include "ConnectCommand.h"
#include "OpenServerCommand.h"

#define WELCOME_MESSAGE "Welcome to APEX!" << std::endl;
#define USAGE_BEGIN "Usage:" << std::endl;
#define RUN_COMMAND_USAGE "  'run' to run an external script or pass the script as an argument, do note that you have to wrap it with quotes.\n        For example, run \"fly.fgs\"." << std::endl;
#define EXIT_COMMAND_USAGE "  'exit' to exit the program." << std::endl;

#define ANNOUNCE_RUNNING "Running " << pathWithoutQuote << std::endl;
#define THANK_YOU_MESSAGE "Thank you for using APEX! Have a nice day!" << std::endl;

#define ARROW_TERMINAL "> ";

#define RUN_COMMAND "run"
#define EXIT_COMMAND "exit"

#define FILE_READ_ERROR "Cannot read from file" << endl;
#define USER_READ_ERROR "Cannot read input" << endl;

using namespace std;

Program::Program() {}

void Program::launchProgram(int argc, char **argv) {

    //Initial messages

    std::cout << WELCOME_MESSAGE

    std::cout << USAGE_BEGIN;
    std::cout << RUN_COMMAND_USAGE;
    std::cout << EXIT_COMMAND_USAGE;


    //read from file.
    if (argc > 1) {
        processFile(argv[1]);
    }
    //read from the user.
    while (true) {
        std::string input = "";
        std::cout << ARROW_TERMINAL;
        std::vector<string> vec;
        getline(cin, input);
        if (input == "") {
            continue;
        }
        vec = mainLexer->process(input);
        if (vec[0] == RUN_COMMAND) {
            processFile(vec[1]);
            continue;
        } else if (vec[0] == EXIT_COMMAND) {
            break;
        }
        mainParser->parse(vec);
        input = "";
    }

    std::cout << THANK_YOU_MESSAGE;

    ConnectCommand::getInstance().get()->closeThread();
    OpenServerCommand::getInstance().get()->closeThread();

}

void Program::processFile(std::string path) {
    try {
        std::string pathWithoutQuote = std::string(path.begin()+1,path.end()-1);
        ifstream file(pathWithoutQuote, std::ios::in | std::ios::binary);
        if (file) {
            std::vector<string> vec;
            std::cout << ANNOUNCE_RUNNING;
            std::ostringstream input;
            input << file.rdbuf();
            file.close();
            vec = mainLexer->process(input.str());
            mainParser->parse(vec);
        } else {
            cout << FILE_READ_ERROR;
        }
        file.close();
    } catch (...) {
        cout << USER_READ_ERROR;
    }
}
