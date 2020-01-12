//
// Created by ofeks on 12/01/2020.
//

#include "SerialServer.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>

void SerialServer::open(int port) {
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
    while (server_holder) {
        // accepting a client
        client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

        if (client_socket == -1) {
            std::cerr << "Error accepting client" << std::endl;
            return;
        }

        //reading from client
        char buffer[1024] = {0};
        int valread = read( client_socket , buffer, 1024);
        std::cout<<buffer<<std::endl;

        //writing back to client
        char *hello = "Hello, I can hear you!! \n";
        send(client_socket , hello , strlen(hello) , 0 );
        std::cout<<"Hello message sent\n"<<std::endl;

        //clienthandler.handle(client_socket);
        close(client_socket);
        stop();
    }
    close(socketfd); //closing the listening socket
}

void SerialServer::stop() {
    server_holder = false;
}

SerialServer::SerialServer() = default;
