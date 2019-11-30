#ifndef APEX_LOOPCOMMAND_H
#define APEX_LOOPCOMMAND_H


#include "ConditionParser.h"

class LoopCommand : public ConditionParser {
    LoopCommand();

public:
    /**
     * A constructtor.
     */
    LoopCommand(LoopCommand const &) = delete;

/**
 * an equal operator.
 */
    void operator=(LoopCommand const &) = delete;

    static std::shared_ptr<LoopCommand> getInstance() {
        static std::shared_ptr<LoopCommand> s{new LoopCommand};
        return s;
    }

    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);
};


#endif //APEX_LOOPCOMMAND_H
