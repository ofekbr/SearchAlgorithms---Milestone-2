//
// Created by ofeks on 25/01/2020.
//

#include "ParallelServer.h"


void ParallelServer::open(int port, ClientHandler *clientHandler) {
//create socket
    int client_socket;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return;
    }

    //bind socket to IP address
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);

    //setting timeout - still needed to be tested
    struct timeval tv{};
    tv.tv_sec = 200;
    tv.tv_usec = 0;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return;
    }
    //making socket listen to the port
    if (listen(socketfd, 10) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    while (true) {
        // accepting a client
        client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

        if (client_socket == -1) {
            std::cerr << "Timeout during accept - server socket" << std::endl;
            this->stop();
            break;
        }

        runningThreads++;

        clients.emplace_back([this, client_socket, clientHandler]{
            clientHandler->clone()->handleClient(client_socket);
            runningThreads--;
        });
    }
    close(socketfd); //closing the listening socket
}

void ParallelServer::stop() {
    while (runningThreads > 0) {
        sleep(2);
    }
    for (auto & client : clients) {
        client.join();
    }
}

