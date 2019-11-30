#ifndef APEX_PRINTCOMMAND_H
#define APEX_PRINTCOMMAND_H

#include "ConditionParser.h"

class PrintCommand : public Command {
    PrintCommand();

public:
    PrintCommand(PrintCommand const &) = delete;

    void operator=(PrintCommand const &) = delete;

    static std::shared_ptr<PrintCommand> getInstance() {
        static std::shared_ptr<PrintCommand> s{new PrintCommand};
        return s;
    }

    /**
     * Print string or expression.
     * @param begin
     * @param end
     */
    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);
};


#endif //APEX_PRINTCOMMAND_H
