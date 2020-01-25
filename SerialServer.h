//
// Created by ofeks on 12/01/2020.
//

#ifndef EX4_SERIALSERVER_H
#define EX4_SERIALSERVER_H

#include "Server.h"

class SerialServer : public Server {
    bool server_holder = true;
public:
    SerialServer() = default;
    void open(int port, ClientHandler *clientHandler) override;
    void stop() override;
};


#endif //EX4_SERIALSERVER_H
