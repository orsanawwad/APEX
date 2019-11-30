#ifndef AP_MS2_MYTESTCLIENTHANDLER_H
#define AP_MS2_MYTESTCLIENTHANDLER_H


#include "IClientHandler.h"
#include "ISolver.h"
#include "ICacheManager.h"


class MyTestClientHandler : public server_side::IClientHandler {
private:

public:
//    MyTestClientHandler(server_side::ISolver <Problem,Solution> *solver, server_side::ICacheManager<Key,Value> *cm );

    MyTestClientHandler();

//    MyTestClientHandler();

//    MyTestClientHandler(server_side::ISolver<Problem, Solution> *solver,
//                        server_side::ICacheManager<Problem, Solution> *cm);

//    virtual void handleClient(int socketIdentify);

//    virtual void handleClient(int socketIdentity);

    virtual void handleClient(posix_sockets::TCPClient client);

};


#endif //AP_MS2_MYTESTCLIENTHANDLER_H
