//
// Created by ofeks on 12/01/2020.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H


class Server {
    virtual void open(int port) = 0;
    virtual void stop() = 0;
};


#endif //EX4_SERVER_H
