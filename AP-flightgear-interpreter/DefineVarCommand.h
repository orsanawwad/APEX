#ifndef APEX_DEFINEVARCOMMAND_H
#define APEX_DEFINEVARCOMMAND_H


#include <unordered_map>
#include <memory>
#include "Command.h"

class DefineVarCommand : public Command {
private:
    DefineVarCommand();

public:
    DefineVarCommand(DefineVarCommand const &) = delete;

    void operator=(DefineVarCommand const &) = delete;

    static std::shared_ptr<DefineVarCommand> getInstance() {
        static std::shared_ptr<DefineVarCommand> s{new DefineVarCommand};
        return s;
    }

    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);
};


#endif //APEX_DEFINEVARCOMMAND_H
