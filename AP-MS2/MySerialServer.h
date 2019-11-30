#ifndef AP_MS2_MYSERIALSERVER_H
#define AP_MS2_MYSERIALSERVER_H


#include <thread>
#include "POSIXSockets.h"
#include "IServer.h"

#define MAX_ALLOWED_LISTENS 10;

class MySerialServer : public server_side::IServer {
    posix_sockets::TCPServer *server;
    server_side::IClientHandler *clientHandler;
    std::thread *serverThread;
    const int maxAllowedListens = MAX_ALLOWED_LISTENS;
    void startAccepting();
    bool should_exit = false;
public:
    virtual void open(int port, server_side::IClientHandler *clientHandler);

    virtual void close();

    virtual ~MySerialServer();
};


#endif //AP_MS2_MYSERIALSERVER_H
