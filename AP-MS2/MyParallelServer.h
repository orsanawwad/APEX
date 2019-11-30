#ifndef AP_MS2_MYPARALLELSERVER_H
#define AP_MS2_MYPARALLELSERVER_H

#include <thread>
#include "POSIXSockets.h"
#include "IServer.h"
#include "ThreadPool.h"

#define MAX_ALLOWED_LISTENS 10;

class MyParallelServer : public server_side::IServer {
    posix_sockets::TCPServer *server;
    server_side::IClientHandler *clientHandler;
    ThreadPool threadPool;
    const int maxAllowedListens = MAX_ALLOWED_LISTENS;
    void startAccepting();
    std::thread *serverThread;
    bool should_exit = false;
public:
    virtual void open(int port, server_side::IClientHandler *clientHandler);

    virtual void close();

    virtual ~MyParallelServer();
};


#endif //AP_MS2_MYPARALLELSERVER_H
