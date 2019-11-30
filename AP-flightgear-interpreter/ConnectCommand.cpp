#include "ConnectCommand.h"
#include "Number.h"
#include "ShuntingYard.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

#include <thread>
#include "DBEngine.h"
#include <future>
#include <sstream>
#include <iostream>


void ConnectCommand::connectToServer() {
    //Save as the one in moodle
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1024];

    portno = (int) port->calculate();

    //Except that it keeps trying to connect
    while (1) {
        DBEngine::getInstance().get()->lockMutex();
        if (shouldClose) {
            DBEngine::getInstance().get()->unlockMutex();
            break;
        }
        DBEngine::getInstance().get()->unlockMutex();

        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        server = gethostbyname(this->host.c_str());

        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);

        /* Now connect to the server */
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            close(sockfd);
            continue;
        }

        break;
    }

    //Until it connects

    while (1) {

        //Then it checks if we need to end the thread.
        DBEngine::getInstance().get()->lockMutex();
        if (shouldClose) {
            close(sockfd);
            DBEngine::getInstance().get()->unlockMutex();
            break;
        }
        DBEngine::getInstance().get()->unlockMutex();

        //Then checks if there's something to send in a set of strings in a queue.
        DBEngine::getInstance().get()->lockMutex();
        if (this->commandsToSend.size() == 0) {
            DBEngine::getInstance().get()->unlockMutex();
            continue;
        }

        bzero(buffer, 1024);


        //If so write to buffer and send directly to server

        strcpy(buffer, this->commandsToSend.front().c_str());
        this->commandsToSend.erase(this->commandsToSend.begin());
        DBEngine::getInstance().get()->unlockMutex();

        /* Send message to the server */
        n = write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            std::cout << "LOST CONNECT" << std::endl;
            close(sockfd);
            break;
        }

        //Reading from server would result in a massive delay between each command to flightgear.

    }
}


void ConnectCommand::execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {

    //Parse arguments here

    if (begin == end) {
        perror("Should not happen");
    }

    begin++;
    this->host = *begin;
    begin++;
    this->port = ShuntingYard::getInstance().get()->parseExpression(begin, end);
    this->connectionThread = new std::thread(&ConnectCommand::connectToServer, this);
}

ConnectCommand::ConnectCommand() {}

void ConnectCommand::sendSetCommand(std::string &path, double &value) {

    //Prepare set command as required
    std::ostringstream setCommand;
    setCommand << "set";
    setCommand << " ";
    setCommand << path;
    setCommand << " ";
    setCommand << value;
    setCommand << "\r\n";

    //Push to queue stack for the thread to pick up
    commandsToSend.push_back(setCommand.str());

}

void ConnectCommand::closeThread() {
    DBEngine::getInstance().get()->lockMutex();
    this->shouldClose = true;
    DBEngine::getInstance().get()->unlockMutex();
}

std::thread *ConnectCommand::getConnectionThread() const {
    return connectionThread;
}
