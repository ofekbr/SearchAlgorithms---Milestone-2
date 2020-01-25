//
// Created by ofeks on 25/01/2020.
//

#ifndef EX4_PARALLELSERVER_H
#define EX4_PARALLELSERVER_H

#include <thread>
#include "Server.h"
#include "ClientHandler.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <mutex>

class ParallelServer : public Server {
    list<thread> clients;
    int runningThreads = 0;
public:
    ParallelServer() = default;
    void open(int port, ClientHandler *clientHandler) override;
    void stop() override;
};


#endif //EX4_PARALLELSERVER_H
