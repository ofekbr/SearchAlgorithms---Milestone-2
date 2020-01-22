//
// Created by shani on 20/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "Searchable.h"
#include "Searcher.h"
#include <set>
#include <queue>
#define INT_MAX 0x7fffffff

template <class T, class S>
class BFS:public Searcher<Searchable<T>*, S> {
    queue<State<T>*> m_queue;
    int m_numOfNodes = 0;
    set<State<T>*> m_visited;
public:
    S search(Searchable<T> *problem) override;
    static S backTrace(State<T>*);
    int evaluatedNodes();
};

template <class T, class S>
int BFS<T, S>::evaluatedNodes() {
    return m_numOfNodes;
}

template <class T, class S>
S backTrace(State<T> state) {

}

template <class T, class S>
S BFS<T,S>::backTrace(State<T> *state) {

    S solution, direction;
    int dx, dy;
    int valuePath = 0;
    list<string> trace;
    State<T>* state2 = state;
    vector<State<T>*> path;

    path.push_back(state2);
    while (state2->cameFrom() != nullptr){
        path.push_back(state2->cameFrom());
        state2 = state2->cameFrom();
    }

    // saving path from source to destination
    while(!path.empty()){
        State<T>* lastElement = path.back();
        valuePath += lastElement->getValue();
        lastElement->setCost(valuePath);
        path.pop_back();
    }

    while(state->cameFrom() != nullptr) {
        State<T> *prev = state->cameFrom();
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
        trace.push_back(direction + "(" + to_string(state->getCost()) + ")");
        state = state->cameFrom();
    }
    for (int i = trace.size(); i > 0; i--) {
        solution += trace.back();
        trace.pop_back();
    }
    return solution;
/*
    S solution;

    // vector path stores the shortest path
    vector<State<T>*> path;
    path.push_back(state);

    while (state->cameFrom() != nullptr){
        path.push_back(state->cameFrom());
        state = state->cameFrom();
    }
    int valuePath = 0;

    // saving path from source to destination
    while(!path.empty()){
        State<T>* lastElement = path.back();
        valuePath += lastElement->getValue();
        solution += path.back()->getCameFromPlacement() + "(" + to_string(valuePath) + ")";
        path.pop_back();
    }

    return solution;
    */
}


template <class T,class S>
S BFS<T,S>::search(Searchable<T> *problem) {

    S solution;
    //update all cost to be INT_MAX
    problem->updateCost(INT_MAX);

    // now source is first to be visited and
    // distance from source to itself should be 0
    State<T>* src = problem->getInitialState();
    m_visited.insert(src);
    src->setCost(0);
    m_queue.push(src);

    // standard BFS algorithm
    while (!m_queue.empty()) {
        State<T>* s = m_queue.front();
        m_queue.pop();
        m_numOfNodes++;

        vector<State<T>*> neighbors = problem->getAllPossibleStates(*s);
        for (auto i = neighbors.begin(); i != neighbors.end(); ++i) {
            auto inVisited = m_visited.find(*i);
            if (inVisited == m_visited.end()) {
                m_visited.insert(*i);
                (*i)->setCost((*s).getCost() + 1);
                (*i)->setCameFrom(s);
                m_queue.push(*i);


                // We stop BFS when we find
                // destination.
                if (problem->isGoalState(**i)){
                    return backTrace(problem->getGoalState());
                }
            }
        }
    }

}

#endif //EX4_BFS_H
