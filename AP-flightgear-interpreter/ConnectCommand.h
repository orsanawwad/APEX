#ifndef APEX_CONNECTCOMMAND_H
#define APEX_CONNECTCOMMAND_H


#include "Command.h"
#include "Expression.h"
#include <thread>
#include <string>

/**
 * Handle outgoing connection.
 */
class ConnectCommand : public Command {
private:
    std::string host;
    Expression *port;
    std::thread *connectionThread;
    std::vector<std::string> commandsToSend;

    void connectToServer();

    bool shouldClose = false;

    ConnectCommand();

public:

    ConnectCommand(ConnectCommand const &) = delete;

    void operator=(ConnectCommand const &) = delete;

    static std::shared_ptr<ConnectCommand> getInstance() {
        static std::shared_ptr<ConnectCommand> s{new ConnectCommand};
        return s;
    }

    virtual void execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end);

    void sendSetCommand(std::string &path, double &value);

    std::thread *getConnectionThread() const;

    /**
     * Used to close outgoing connection thread.
     */
    void closeThread();
};


#endif //APEX_CONNECTCOMMAND_H
