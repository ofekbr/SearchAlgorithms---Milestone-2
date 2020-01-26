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
    virtual ClientHandler* clone() = 0;
};


class MyClientHandler: public ClientHandler{
    Solver<Searchable<pair<int, int>>*, string> *m_solver;
    static FileCacheManager<string> m_cacheManager;

public:
    explicit MyClientHandler(Solver<Searchable<pair<int,int>>*,string> *solver){
        m_solver = solver;
    }
    void handleClient(int socket) override;
    vector<vector<State<pair<int,int>>>> createStateMatrix(vector<vector<int>> vecMatrix, int numRow, int numCol);
    Searchable<pair<int,int>>* createProblem(int socket);
    //string = solution
    void sendSolution(int,const string&);
    ~MyClientHandler() =default;

    ClientHandler *clone() {
        return new MyClientHandler(m_solver->clone());
    }
    //      delete(m_cacheManager);
};

#endif //EX4_CLIENTHANDLER_H
