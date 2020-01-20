//
// Created by ofeks on 12/01/2020.
//

#include "SerialServer.h"
#include "ClientHandler.h"
#include "ObjectAdapter.h"
#include "BestFS.h"
#include <utility>

int main(int argc, char const *argv[]) {

    SerialServer server;

    Searcher<Searchable<pair<int,int>>*,string> *bestFs = new BestFS<pair<int,int>, string>();

    ObjectAdapter<Searchable<pair<int,int>>*,string> objectAdapter(bestFs);
    MyTestClientHandler ch(&objectAdapter);
    server.open(12345, &ch);

}