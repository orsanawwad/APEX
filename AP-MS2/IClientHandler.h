#ifndef AP_MS2_ICLIENTHANDLER_H
#define AP_MS2_ICLIENTHANDLER_H

#include "POSIXSockets.h"

namespace server_side {
    class IClientHandler {
    public:
        virtual void handleClient(posix_sockets::TCPClient client) = 0;

        virtual ~IClientHandler() {}
    };
}

#endif //AP_MS2_ICLIENTHANDLER_H
