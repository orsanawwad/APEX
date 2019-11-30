#include "iostream"

#include "DBEngine.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

DBEngine::DBEngine() {
    //Define reserved words
    this->commandTable["openDataServer"] = OpenServerCommand::getInstance().get();
    this->commandTable["connect"] = ConnectCommand::getInstance().get();
    this->commandTable["var"] = DefineVarCommand::getInstance().get();
    this->commandTable["while"] = LoopCommand::getInstance().get();
    this->commandTable["if"] = IfCommand::getInstance().get();
    this->commandTable["print"] = PrintCommand::getInstance().get();
    this->commandTable["sleep"] = SleepCommand::getInstance().get();
}

const std::unordered_map<std::string, Command *> DBEngine::getCommandTable() const {
    return commandTable;
}

bool DBEngine::isBind(std::string symbolName) {
    return this->symbolBinding.count(symbolName) != 0;
}

bool DBEngine::isSymbol(std::string symbolName) {
    return this->symbolTable.count(symbolName) != 0;
}

bool DBEngine::inRTData(std::string symbolName) {
    DBEngine::getInstance().get()->lockMutex();
    bool value = this->RTData.count(symbolName) != 0;
    DBEngine::getInstance().get()->unlockMutex();
    return value;
}

std::string DBEngine::getBind(std::string symbolName) {
    return this->symbolBinding[symbolName];
}

double DBEngine::getSymbol(std::string symbolName) {

    //If the symbol was binded to a real-time updated path from simulator, get that value and update it in symbol
    if (this->isBind(symbolName)) {
        if (this->inRTData(this->getBind(symbolName))) {
            this->symbolTable[symbolName] = this->getRTData(this->getBind(symbolName));
        }
    }

    return this->symbolTable[symbolName];

}

double DBEngine::getRTData(std::string symbolName) {
    //Because this is a shared resource, we lock and unlock
    DBEngine::getInstance().get()->lockMutex();
    double value = this->RTData[symbolName];
    DBEngine::getInstance().get()->unlockMutex();
    return value;
}

void DBEngine::setBind(std::string symbolName, std::string value) {
    this->symbolBinding[symbolName] = value;
}

void DBEngine::setSymbol(std::string symbolName, double value) {
    this->symbolTable[symbolName] = value;

    //If a symbol got updated and it was binded to a path, send a set command to simulator
    if (this->isBind(symbolName)) {
        DBEngine::getInstance().get()->lockMutex();
        std::string bindValue = this->getBind(symbolName);
        ConnectCommand::getInstance().get()->sendSetCommand(bindValue, value);
        DBEngine::getInstance().get()->unlockMutex();
    }
}

void DBEngine::processDataFromServer(std::vector<double> &data) {
    std::vector<double>::iterator valuesIterator;
    valuesIterator = data.begin();


    //Yeah.... Can't do xml parsing thanks to requirements.

    RTData["/instrumentation/airspeed-indicator/indicated-speed-kt"] = *(valuesIterator);
    RTData["/instrumentation/altimeter/indicated-altitude-ft"] = *(++valuesIterator);
    RTData["/instrumentation/altimeter/pressure-alt-ft"] = *(++valuesIterator);
    RTData["/instrumentation/attitude-indicator/indicated-pitch-deg"] = *(++valuesIterator);
    RTData["/instrumentation/attitude-indicator/indicated-roll-deg"] = *(++valuesIterator);
    RTData["/instrumentation/attitude-indicator/internal-pitch-deg"] = *(++valuesIterator);
    RTData["/instrumentation/attitude-indicator/internal-roll-deg"] = *(++valuesIterator);
    RTData["/instrumentation/encoder/indicated-altitude-ft"] = *(++valuesIterator);
    RTData["/instrumentation/encoder/pressure-alt-ft"] = *(++valuesIterator);
    RTData["/instrumentation/gps/indicated-altitude-ft"] = *(++valuesIterator);
    RTData["/instrumentation/gps/indicated-ground-speed-kt"] = *(++valuesIterator);
    RTData["/instrumentation/gps/indicated-vertical-speed"] = *(++valuesIterator);
    RTData["/instrumentation/heading-indicator/indicated-heading-deg"] = *(++valuesIterator);
    RTData["/instrumentation/magnetic-compass/indicated-heading-deg"] = *(++valuesIterator);
    RTData["/instrumentation/slip-skid-ball/indicated-slip-skid"] = *(++valuesIterator);
    RTData["/instrumentation/turn-indicator/indicated-turn-rate"] = *(++valuesIterator);
    RTData["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = *(++valuesIterator);
    RTData["/controls/flight/aileron"] = *(++valuesIterator);
    RTData["/controls/flight/elevator"] = *(++valuesIterator);
    RTData["/controls/flight/rudder"] = *(++valuesIterator);
    RTData["/controls/flight/flaps"] = *(++valuesIterator);
    RTData["/controls/engines/engine/throttle"] = *(++valuesIterator);
    RTData["/engines/engine/rpm"] = *(++valuesIterator);

}

bool DBEngine::symbolExist(std::string &value) {
    return this->symbolTable.count(value) != 0;
}

bool DBEngine::bindExist(std::string &value) {
    return this->symbolBinding.count(value) != 0;
}

void DBEngine::lockMutex() {
    this->globalMutex.lock();
}

void DBEngine::unlockMutex() {
    this->globalMutex.unlock();
}
