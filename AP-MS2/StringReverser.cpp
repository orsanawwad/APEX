#include "StringReverser.h"

std::string StringReverser::solve(std::string problem) {
    return std::string(problem.rbegin(), problem.rend());
}
