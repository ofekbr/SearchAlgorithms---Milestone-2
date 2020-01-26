//
// Created by shani on 23/01/2020.
//

#ifndef EX4_BOOT_H
#define EX4_BOOT_H

//
// Created by shani on 23/01/2020.
//

#include "SerialServer.h"
#include "ClientHandler.h"
#include "ObjectAdapter.h"
#include "BestFS.h"
#include "DFS.h"
#include "BFS.h"
#include "AStar.h"
#include "ParallelServer.h"
#include <utility>

namespace boot {
    class Main;
}

class boot :: Main{

public:
    Main(){};
    ~Main(){};
    int main(string port) {
        ParallelServer server;

        //Searcher<Searchable<pair<int,int>>*,string> *bestFs = new BestFS<pair<int,int>, string>();
        //Searcher<Searchable<pair<int,int>>*,string> *Dfs = new DFS<pair<int,int>, string>();
        //Searcher<Searchable<pair<int,int>>*,string> *Bfs = new BFS<pair<int,int>, string>();
        Searcher<Searchable<pair<int,int>>*,string> *Astar = new AStar<pair<int,int>, string>();

        //ObjectAdapter<Searchable<pair<int,int>>*,string> objectAdapter(bestFs);
        ObjectAdapter<Searchable<pair<int,int>>*,string> objectAdapter(Astar);
        MyClientHandler ch(&objectAdapter);
        server.open(stod(port), &ch);
        int num = Astar->evaluatedNodes();
        cout<< num << endl;
    };
};


#endif //EX4_BOOT_H
