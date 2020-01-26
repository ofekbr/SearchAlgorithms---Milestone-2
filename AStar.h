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
#include "BestFS.h"
#include "AStarStateCompare.h"
#include <set>

using namespace std;

template <class T, class S>
class AStar: public Searcher<Searchable<T>*, S> {
    MyQueue<State<T>*, std::vector<State<T>*>, AStarStateCompare<T>> openList;
    int m_numOfNodes = 0;
public:
    S search(Searchable<T> *problem) override;
    static S backTrace(State<T>*);
    int evaluatedNodes();
    AStar<T,S>* clone();
};


template <class T, class S>
AStar<T,S>* AStar<T,S>::clone() {
    return new AStar<T,S>;
}

template <class T, class S>
int AStar<T, S>::evaluatedNodes() {
    return m_numOfNodes;
}

template <class T, class S>
S AStar<T, S>::backTrace(State<T>* state) {
    S solution, direction;
    int dx, dy;
    list<string> trace;
    while(state->getCameFrom() != nullptr){
        State<T> *prev = state->getCameFrom();
        dx = prev->getPos().first - state->getPos().first;
        dy = prev->getPos().second - state->getPos().second;
        if (dx == 0) {
            if (dy == 1) {
                direction = "LEFT";
            } else {
                direction = "RIGHT";
            }
        } else if (dx == 1) {
            direction = "UP";
        } else if (dx == -1) {
            direction = "DOWN";
        }
        trace.push_back(direction +"(" + to_string(state->getCost()) + ")");
        state = state->getCameFrom();
    }

    for (int i = trace.size(); i > 0; i--) {
        solution += trace.back();
        trace.pop_back();
    }
    return solution;
}

template <class T, class S>
S AStar<T, S>::search(Searchable<T> *problem) {
    goal<T>  = problem->getGoalState();
    m_numOfNodes = 0;
    set<State<T>*> closed;
    openList.push(problem->getInitialState());
    while (openList.size() > 0) {
        m_numOfNodes++;
        State<T> *n = openList.top();
        openList.pop();
        closed.insert(n);

        //so we wont check again
        if (problem->isGoalState(*n)) {
            S solution = backTrace(n);
            return solution;
        }
        //create n's successor
        vector<State<T>*> neighbors = problem->getAllPossibleStates(*n);

        //for each successor do:
        for (auto neigh = neighbors.begin(); neigh != neighbors.end(); neigh++) {
            auto inClosed = closed.find(*neigh);
            //if neigh is not in closed and not in open

            if (inClosed == closed.end() && !openList.contains(*neigh)) {
                //update that we came to it from n
                (*neigh)->setCameFrom(n);
                (*neigh)->setCost(n->getCost() + (*neigh)->getValue());
                openList.push(*neigh);
            } else if(((n->getCost() + (*neigh)->getValue()) < (*neigh)->getCost())){ // if the new path is better than previous one
                //if it is not in the open add it to the open
                if(!openList.contains(*neigh)){
                    openList.push(*neigh);
                } else {
                    //adjust its priority
                    openList.find(*neigh)->setCost(n->getCost() + (*neigh)->getValue());
                    openList.find(*neigh)->setCameFrom(n);
                    openList.update(*neigh);
                }
            }
        }
    }
    throw "AStar failed";
}


#endif //EX4_ASTAR_H
