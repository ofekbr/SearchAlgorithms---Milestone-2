//
// Created by shani on 22/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "State.h"
#include "Searcher.h"
#include "Searchable.h"
#include "StatePtrCompare.h"
#include "MyQueue.h"
#include <set>
#include <cmath>
template <class T, class S>
class AStar:public Searcher<Searchable<T>*, S> {
    MyQueue<State<T>*, std::vector<State<T>*>, StatePtrCompare<T>> openList;
    int m_numOfNodes = 0;
public:
    S search(Searchable<T> *problem) override;
    static S backTrace(State<T>*);
    int heuristic(State<T>*, State<T>*);
    int evaluatedNodes();
};

template<class T, class S>
int AStar<T,S>::heuristic(State<T> *state, State<T>* goal) {
    int dx = state->getPos().first - goal->getPos().first;
    int dy = state->getPos().second - goal->getPos().second;
    int h = sqrt(pow(dx,2) +  pow(dy,2));

    return h;
}

template <class T, class S>
S AStar<T,S>::search(Searchable<T> *problem) {

    m_numOfNodes = 0;
    set<State<T>*> closed;

    problem->getInitialState()->setf(problem->getInitialState()->getValue() + heuristic(problem->getInitialState(), problem->getGoalState()));
    openList.push(problem->getInitialState());

    while (!openList.empty()) {
        m_numOfNodes++;
        State<T> *n = openList.top();
        openList.pop();
        (*n).setF((*n).getCost()+ heuristic(n, problem->getGoalState()));

        //so we wont check again
        if (problem->isGoalState(*n)) {
            S solution = backTrace(n);
            return solution;
        }

        //create n's successor
        vector<State<T>*> neighbors = problem->getAllPossibleStates(*n);

        //for each successor do:
        for (auto neigh = neighbors.begin(); neigh != neighbors.end(); neigh++) {
            (*neigh)->setCost((*neigh)->getCost + (*neigh)->getValue);
        }
    }
    throw "AStar failed";
}


#endif //EX4_ASTAR_H
