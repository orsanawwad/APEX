#ifndef APEX_COMMAND_H
#define APEX_COMMAND_H

#include <stdlib.h>
#include <vector>
#include <string>


class Command {
public:
    virtual ~Command() {};

    /**
     * Execute method to run the command given by the beginning of an iterator.
     */
    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) = 0;
};


#endif //APEX_COMMAND_H
