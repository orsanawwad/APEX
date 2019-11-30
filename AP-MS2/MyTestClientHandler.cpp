#include <cstdlib>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <strings.h>
#include "MyTestClientHandler.h"
#include "ISolver.h"
#include "ICacheManager.h"


//void MyTestClientHandler::handleClient(int socketIdentity) {
//
////    string input;
////    inputStream.getline(input);
////    while (input != "end") {
////        if (this->cm->doesExist) {
////            this->cm->get(input);
////        } else {
////            this->cm->set(input, this->solver->solve(input));
////
////<<<<<<< Updated upstream
////        }
////    }
////=======
//    char buffer[256];
//    int n;
//
//    /* If connection is established then start communicating */
//    bzero(buffer, 256);
//    n = read(socketIdentity, buffer, 255);
//
//    if (n < 0) {
//        perror("ERROR reading from socket");
//        exit(1);
//    }
//    printf("Here is the message: %s\n", buffer);
//    close(socketIdentity);
////>>>>>>> Stashed changes
//}

MyTestClientHandler::MyTestClientHandler() {}

void MyTestClientHandler::handleClient(posix_sockets::TCPClient client) {
    std::string message;
    long msg;
    try {
        while ((msg = client.readLine(message)) > 0 && message != "end") {
            std::cout << message;
        }
        if (msg == 0) {
            std::cout << "Client closed connection" << std::endl;
            client.close();
        }
    } catch (posix_sockets::timeout_exception &e) {
        std::cout << "Client timed out" << std::endl;
        client.close();
    }
}

//template<typename Problem, typename Solution>
//MyTestClientHandler<Problem, Solution>::MyTestClientHandler(
//        server_side::ISolver<Problem, Solution> *solver,
//        server_side::ICacheManager<Problem, Solution> *cm):solver(
//        solver), cm(cm) {}
