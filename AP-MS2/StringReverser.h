#ifndef AP_MS2_STRINGREVERSER_H
#define AP_MS2_STRINGREVERSER_H


#include <string>
#include "ISolver.h"

class StringReverser : public server_side::ISolver<std::string, std::string> {
public:
    virtual std::string solve(std::string problem);
};


#endif //AP_MS2_STRINGREVERSER_H
