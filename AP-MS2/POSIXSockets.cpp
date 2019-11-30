#include <sstream>
#include "POSIXSockets.h"

posix_sockets::timeout_exception::timeout_exception(const char *msg) : runtime_error(msg){}
posix_sockets::timeout_exception::timeout_exception(const std::string msg) : runtime_error(msg){}

posix_sockets::illegal_state_exception::illegal_state_exception(const std::string msg) : logic_error(msg){}

posix_sockets::TCPSocket::TCPSocket() {
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        throw std::system_error(std::error_code(errno, std::generic_category()), "failure on opening socket");
    }
    int opt = 1;
    // Forcefully attaching socket to the port 8080
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt));
//        throw std::system_error(std::error_code(errno, std::generic_category()), "failure on setsockopt");
}

posix_sockets::TCPSocket::TCPSocket(int open_sock_fd) : sock_fd(open_sock_fd) {}

void posix_sockets::TCPSocket::close() {
    if (::close(sock_fd) < 0)	{
        throw std::system_error(std::error_code(errno, std::generic_category()), "failure on closing socket");
    }
}

void posix_sockets::TCPSocket::setTimeout(int sec, int usec) {
    timeval timeout;
    timeout.tv_sec = sec;
    timeout.tv_usec = usec;

    // setting socket option for recieve timeout
    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO,
                   (char *)&timeout, sizeof(timeout)) == -1)	{
        throw std::system_error(std::error_code(errno, std::generic_category()), "failure on setsockopt");
    }
}

posix_sockets::TCPClient::TCPClient(const posix_sockets::TCPSocket sock) : sock(sock) {}

void posix_sockets::TCPClient::setTimeout(int sec, int usec) {
    sock.setTimeout(sec, usec);
}

void posix_sockets::TCPClient::close() {
    sock.close();
}

long posix_sockets::TCPClient::readLine(std::string &bufferLine) {
    std::stringstream ss;
    char buffer[2];
    bzero(buffer,2);
    while(strcmp(buffer,"\n")) {
        auto read_len = ::read(sock.sock_fd, buffer, 1);
        if (read_len < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                throw timeout_exception("timeout on read");
            }
            throw std::system_error(std::error_code(errno, std::generic_category()), "error on read");
        } else if (read_len == 0) {
//            this->close();
//            return std::string("end");
            return read_len;
            //TODO: FIX THIS HACK LIKE
        }
        ss << buffer;
    }
    bufferLine = ss.str();
    return bufferLine.length();
}

long posix_sockets::TCPClient::sendMessage(std::string &message) {
    long msg;
    if ((msg = ::send(this->sock.sock_fd , message.c_str(), message.length(), 0) < 0)) {
        throw std::system_error(std::error_code(errno, std::generic_category()), "error on write");
    }
    return msg;
}

posix_sockets::TCPServer::TCPServer(int port) {
    sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(port);
    addr_in.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock.sock_fd, (sockaddr *)&addr_in, sizeof(addr_in)) == -1)	{
        throw std::system_error(std::error_code(errno, std::generic_category()), "failure on bind");
    }
}

void posix_sockets::TCPServer::listen(int maxAllowedListens) {
    if (::listen(sock.sock_fd, maxAllowedListens) == -1)	{
        throw std::system_error(std::error_code(errno, std::generic_category()), "error on listen");
    }
}

void posix_sockets::TCPServer::setTimeout(int sec, int usec) {
    sock.setTimeout(sec, usec);
}

posix_sockets::TCPClient posix_sockets::TCPServer::accept() {
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int client_sock_fd = ::accept(sock.sock_fd, (sockaddr*)&addr, &len);
    if (client_sock_fd < 0)	{
        // eagain and ewouldblock are errors normally hapenning on timeouts
        if (errno == EAGAIN || errno == EWOULDBLOCK)	{
            throw timeout_exception("timeout on accept");
        }	else	{
            throw std::system_error(std::error_code(errno, std::generic_category()), "error on accept");
        }
    }

    TCPSocket client_sock(client_sock_fd);

    // in Unix, client socket have their parents' timeout
    // so we set the timeout to 0 (effectively - infinity)
    // for newly created sockets
    client_sock.setTimeout(0);
    return client_sock;
}

void posix_sockets::TCPServer::close() {
    sock.close();
}
