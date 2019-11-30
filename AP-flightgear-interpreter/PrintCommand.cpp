#include <iostream>
#include "PrintCommand.h"
#include "ShuntingYard.h"

#define PRINT_NAME_ERROR "Name Error: name '"<< *begin << "' is not defined" << std::endl;

PrintCommand::PrintCommand() {}

void PrintCommand::execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {
    std::advance(begin, 1);

    if (*begin->begin() == '\"') {
        for (char &c : *begin) {
            if (c != '\"') {
                std::cout << c;
            }
        }
        std::cout << std::endl;
    } else {
        try {
            std::cout << ShuntingYard::getInstance().get()->parseExpression(begin,end)->calculate() << std::endl;
            return;
        } catch (...) {
            std::cout << PRINT_NAME_ERROR ;
        }
    }
    std::advance(begin, 1);
}
