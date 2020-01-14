//
// Created by shani on 12/01/2020.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"
#include "FileCacheManager.h"

class ClientHandler{
public:
    virtual void handleClient(int socket) = 0;
};


class MyTestClientHandler: public ClientHandler{
//    Solver<P,S> m_solver;
    //string = solution
    FileCacheManager<string> m_cacheManager;

public:
    MyTestClientHandler()= default;
    void handleClient(int socket) override;
    vector<vector<State<pair<int,int>>>> createStateMatrix(vector<vector<int>> vecMatrix, int numRow, int numCol);
    //TODO change from matrix to searchable
    Matrix createProblem(int socket);
    //string = solution
    void sendSolution(int,const string&);
    ~MyTestClientHandler() =default;
  //      delete(m_cacheManager);
};




#endif //EX4_CLIENTHANDLER_H
