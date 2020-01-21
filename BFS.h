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
S BFS<T,S>::backTrace(State<T> *goal) {

    S solution;

    // vector path stores the shortest path
    vector<State<T>*> path;
    path.push_back(goal);

    while (goal->cameFrom() != nullptr){
        path.push_back(goal->cameFrom());
        goal = goal->cameFrom();
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
