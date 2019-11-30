//
// Created by Orsan Awwad on 2019-01-15.
//

#ifndef AP_MS2_MYCLIENTHANDLER_H
#define AP_MS2_MYCLIENTHANDLER_H


#include "IClientHandler.h"
#include "ISolver.h"
#include "ICacheManager.h"
#include "ISearchable.h"

//TODO: FIX GENERICS
class MyClientHandler : public server_side::IClientHandler{
    server_side::ISolver<ISearchable<std::pair<int,int>,double>*,std::string>* solver;
    server_side::ICacheManager<std::string,std::string>* cacheManager;
public:
    MyClientHandler(server_side::ISolver<ISearchable<std::pair<int, int>, double> *, std::string> *solver,
                    server_side::ICacheManager<std::string, std::string> *cacheManager);

    virtual void handleClient(posix_sockets::TCPClient client);

    virtual ~MyClientHandler();
};


#endif //AP_MS2_MYCLIENTHANDLER_H
