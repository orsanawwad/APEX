#ifndef AP_MS2_POSIXSOCKETS_H
#define AP_MS2_POSIXSOCKETS_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#include <iostream>
#include <string>
#include "string.h"
#include <system_error>
#include <stdexcept>

namespace posix_sockets
{
    class timeout_exception : public std::runtime_error {
    public:
        timeout_exception(const char *msg);
        timeout_exception(const std::string msg);
    };

    class illegal_state_exception : public std::logic_error {
    public:
        illegal_state_exception(const std::string msg);
    };


    // struct defining general socket, with general operations (open and close)
    // opening is done in the constructor.
    // the socket is not automatically closed in the destructor so that the object
    // can be passed as a parameter (possibly to another thread)
    struct TCPSocket {
        int sock_fd;
        TCPSocket();
        TCPSocket(int open_sock_fd);
        void close();
        void setTimeout(int sec, int usec = 0);
    };

    class TCPClient {
        TCPSocket sock;
    public:
        // It makes sense to creates another constructor that
        // will create a client from scratch
        TCPClient(const TCPSocket sock);

        // you should definitely use your own logic here
        // suggestions are - read_until (char), read_min(int)
        // read_line, etc.
        // you can obviously define a write (or send) method
        std::string read(int n);

        long readLine(std::string &bufferLine);

        long sendMessage(std::string &message);

        void setTimeout(int sec, int usec = 0);

        void close();
    };

    class TCPServer {
        TCPSocket sock;
    public:
        TCPServer(int port);

        void listen(int maxAllowedListens);

        void setTimeout(int sec, int usec = 0);

        TCPClient accept();

        void close();
    };
}

#endif //AP_MS2_POSIXSOCKETS_H
