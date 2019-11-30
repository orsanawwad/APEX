#ifndef APEX_SLEEPCOMMAND_H
#define APEX_SLEEPCOMMAND_H


#include <memory>

#include "Command.h"

class SleepCommand : public Command {
    SleepCommand();

public:

    SleepCommand(SleepCommand const &) = delete;

    void operator=(SleepCommand const &) = delete;

    static std::shared_ptr<SleepCommand> getInstance() {
        static std::shared_ptr<SleepCommand> s{new SleepCommand};
        return s;
    }

    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);


};


#endif //APEX_SLEEPCOMMAND_H
