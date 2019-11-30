#include "OpenServerCommand.h"
#include "Number.h"
#include "DefineVarCommand.h"
#include "DBEngine.h"
#include "ShuntingYard.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

#include <thread>
#include <future>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

void OpenServerCommand::listenFromSource() {
    int newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = (int) this->port->calculate();

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t * ) & clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    char buffer[2];
    std::string lineBuffer;
    int n;
    while (1) {

        //Check if program requested to close the thread
        DBEngine::getInstance().get()->lockMutex();
        if (shouldClose) {
            //If so close the socket first and break out of the loop to let the thread end
            close(sockfd);
            DBEngine::getInstance().get()->unlockMutex();
            break;
        }
        DBEngine::getInstance().get()->unlockMutex();

        bzero(buffer, 2);
        n = read(newsockfd, buffer, 1);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        //Keep reading until line ending and process it
        if (std::strcmp(buffer, "\n") == 0) {
            lineBuffer.append(buffer);
            processData(lineBuffer);
            lineBuffer.clear();
        } else {
            lineBuffer.append(buffer);
        }
    }
}


void OpenServerCommand::execute(std::vector<std::string>::iterator &begin, std::vector<std::string>::iterator &end) {

    if (begin == end) {
        std::cout << "Something went wrong" << std::endl;
        return;
    }
    std::advance(begin, 1);

    this->port = ShuntingYard::getInstance().get()->parseExpression(begin, end);
    this->refreshRate = ShuntingYard::getInstance().get()->parseExpression(begin, end);


    this->serverThread = new std::thread(&OpenServerCommand::listenFromSource, this);

}

OpenServerCommand::OpenServerCommand() {}

void OpenServerCommand::processData(std::string &buffer) {

    //Split csv row

    std::string &tableRow = buffer;

    std::stringstream rowStream(tableRow);

    std::vector<char> cellValue;
    std::vector<double> rowValues;

    char i;

    while (rowStream >> i) {
        cellValue.push_back(i);
        if (rowStream.peek() == ',') {
            rowValues.push_back(std::stod(std::string(cellValue.begin(), cellValue.end()).c_str(), NULL));
            cellValue.clear();
            rowStream.ignore();
        }
    }
    rowValues.push_back(std::stod(std::string(cellValue.begin(), cellValue.end()).c_str(), NULL));
    cellValue.clear();

    //Process the values
    DBEngine::getInstance().get()->lockMutex();
    DBEngine::getInstance().get()->processDataFromServer(rowValues);;
    DBEngine::getInstance().get()->unlockMutex();

    std::this_thread::sleep_for(std::chrono::milliseconds((int) (1.0 / this->refreshRate->calculate()) * 1000));
}

void OpenServerCommand::closeThread() {
    DBEngine::getInstance().get()->lockMutex();
    close(sockfd);
    this->shouldClose = true;
    DBEngine::getInstance().get()->unlockMutex();
}

std::thread *OpenServerCommand::getServerThread() const {
    return serverThread;
}


