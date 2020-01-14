//
// Created by ofeks on 12/01/2020.
//

#include "SerialServer.h"
#include "ClientHandler.h"

int main(int argc, char const *argv[]) {
    SerialServer server;
    MyTestClientHandler ch;
    server.open(12345, &ch);
}