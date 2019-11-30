#ifndef APEX_DBENGINE_H
#define APEX_DBENGINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include "string"
#include "Command.h"

class DBEngine {
    //All data in one place

    //This is used to sync with the simulator
    std::unordered_map<std::string, double> RTData; //RealTimeData
    //Used to bind a symbol to its path in the simulator
    std::unordered_map<std::string, std::string> symbolBinding;
    //Normal global data
    std::unordered_map<std::string, double> symbolTable;
    //Reserved keywords
    std::unordered_map<std::string, Command *> commandTable;

    //One global mutex to prevent deadlocks
    std::mutex globalMutex;

    //Used to define reserved words
    DBEngine();

public:
    DBEngine(DBEngine const &) = delete;

    void operator=(DBEngine const &) = delete;

    static std::shared_ptr<DBEngine> getInstance() {
        static std::shared_ptr<DBEngine> s{new DBEngine};
        return s;
    }

    bool isBind(std::string symbolName);

    std::string getBind(std::string symbolName);

    void setBind(std::string symbolName, std::string value);

    bool isSymbol(std::string symbolName);

    double getSymbol(std::string symbolName);

    void setSymbol(std::string symbolName, double value);

    bool inRTData(std::string symbolName);

    double getRTData(std::string symbolName);

    /**
     * Update the data from server.
     * @param data
     */
    void processDataFromServer(std::vector<double> &data);

    bool symbolExist(std::string &value);

    bool bindExist(std::string &value);

    /**
     * Lock mutex
     */
    void lockMutex();

    /**
     * Unlock mutex
     */
    void unlockMutex();

    /**
     * Get list of reserved words.
     * @return
     */
    const std::unordered_map<std::string, Command *> getCommandTable() const;
};


#endif //APEX_DBENGINE_H
