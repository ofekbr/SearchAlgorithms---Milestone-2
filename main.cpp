//
// Created by ofeks on 12/01/2020.
//

#include "SerialServer.h"
#include "ClientHandler.h"
#include "ObjectAdapter.h"
#include "BestFS.h"
#include "DFS.h"
#include "BFS.h"
#include <utility>

int main(int argc, char const *argv[]) {

    //TODO fix cameFrom element in matrix..
    SerialServer server;

    //Searcher<Searchable<pair<int,int>>*,string> *bestFs = new BestFS<pair<int,int>, string>();
    //Searcher<Searchable<pair<int,int>>*,string> *Dfs = new DFS<pair<int,int>, string>();
    Searcher<Searchable<pair<int,int>>*,string> *Bfs = new BFS<pair<int,int>, string>();

    ObjectAdapter<Searchable<pair<int,int>>*,string> objectAdapter(Bfs);
    MyTestClientHandler ch(&objectAdapter);
    server.open(12345, &ch);

}