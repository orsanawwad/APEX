#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>
#include "MySerialServer.h"

void MySerialServer::open(int port, server_side::IClientHandler *clientHandler) {
    this->clientHandler = clientHandler;
    this->server = new posix_sockets::TCPServer(port);
    this->server->listen(maxAllowedListens);
    this->serverThread = new std::thread(&MySerialServer::startAccepting, this);
}

void MySerialServer::close() {
    this->serverThread->join();
    delete server;
    server = NULL;
    delete this->serverThread;
    this->serverThread = NULL;
}

void MySerialServer::startAccepting() {
    while (!this->should_exit) {
        try {
            posix_sockets::TCPClient newClient = this->server->accept();
            clientHandler->handleClient(newClient);
            this->server->setTimeout(5);
        } catch (posix_sockets::timeout_exception & e) {
            std::cout << "No new clients received, exiting..." << std::endl;
            this->server->close();
            this->close();
            break;
        }
    }
}

MySerialServer::~MySerialServer() {
    this->serverThread->join();
    delete server;
    server = NULL;
}
