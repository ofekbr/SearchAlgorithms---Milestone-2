//
// Created by ofeks on 12/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H


#include "ClientHandler.h"

class Server {
    virtual void open(int port, ClientHandler *clientHandler) = 0;
    virtual void stop() = 0;
};


#endif //EX4_SERVER_H
