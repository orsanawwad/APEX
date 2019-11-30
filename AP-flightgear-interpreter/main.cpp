#include "Program.h"

int main(int argc, char **argv) {
    Program::getInstance().get()->launchProgram(argc, argv);
    return 0;
}
