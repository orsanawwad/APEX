#ifndef APEX_IFCOMMAND_H
#define APEX_IFCOMMAND_H


#include "ConditionParser.h"


class IfCommand : public ConditionParser {
    IfCommand();

public:
    /**
     * A constructor.
     */
    IfCommand(IfCommand const &) = delete;

/**
 * An equal operator.
 */
    void operator=(IfCommand const &) = delete;

    static std::shared_ptr<IfCommand> getInstance() {
        static std::shared_ptr<IfCommand> s{new IfCommand};
        return s;
    }

    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);
};


#endif //APEX_IFCOMMAND_H
