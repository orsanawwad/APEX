#ifndef APEX_OPENSERVERCOMMAND_H
#define APEX_OPENSERVERCOMMAND_H

#include <thread>
#include <vector>
#include <string>
#include <unordered_map>
#include "Command.h"
#include "Expression.h"

// Use getInstance to invoke functions (uses singleton pattern)
class OpenServerCommand : public Command {
private:
    int sockfd;
    Expression *refreshRate;
    Expression *port;
    std::thread *serverThread;

    void listenFromSource();

    void processData(std::string &buffer);

    bool shouldClose = false;

    OpenServerCommand();

public:
    OpenServerCommand(OpenServerCommand const &) = delete;

    void operator=(OpenServerCommand const &) = delete;

    static std::shared_ptr<OpenServerCommand> getInstance() {
        static std::shared_ptr<OpenServerCommand> s{new OpenServerCommand};
        return s;
    }

    std::thread *getServerThread() const;

    void closeThread();

    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);
};


#endif //APEX_OPENSERVERCOMMAND_H
