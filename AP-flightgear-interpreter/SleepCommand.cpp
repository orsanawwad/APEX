#include <iostream>
#include <chrono>
#include <thread>
#include "SleepCommand.h"
#include "DBEngine.h"
#include "ShuntingYard.h"

SleepCommand::SleepCommand() {}

void SleepCommand::execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {
    std::advance(begin, 1);

    int waitTime = 0;

    if (DBEngine::getInstance().get()->symbolExist(*begin)) {
        waitTime = (int) DBEngine::getInstance().get()->getSymbol(*begin);
        std::advance(begin, 1);
    } else {
        waitTime = (int) ShuntingYard::getInstance().get()->parseExpression(begin, end)->calculate();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
}
