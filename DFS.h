//
// Created by shani on 20/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H


#include "Searcher.h"
#include "Searchable.h"
#include <stack>
#include <set>
#include <iostream>

template <class T, class S>
class DFS: public Searcher<Searchable<T>*, S> {
    stack<State<T> *> m_stack;
    set<State<T> *> m_visited;
    int m_numOfNodes = 0;
public:
    S search(Searchable<T> *problem) override;
    int evaluatedNodes();
    S backTrace(State<T> *state);
    DFS<T,S>* clone();
};

template <class T, class S>
DFS<T,S>* DFS<T,S>::clone() {
    return new DFS<T,S>;
}



template<class T,class S>
S DFS<T,S>::search(Searchable<T> *problem){

    S solution;
    int pathCost = 0;

    // Push the current source node.
    m_stack.push(problem->getInitialState());

    while (!m_stack.empty())
    {
        // Pop a vertex from stack and print it
        State<T>* s = m_stack.top();
        m_stack.pop();
        m_numOfNodes++;

        if (problem->isGoalState(*s)){
            //solution += (s->getCameFromPlacement()) + "(" + to_string(pathCost+s->getValue()) + ")";
            return backTrace(problem->getGoalState());
            break;
        }
        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        auto inVisited = m_visited.find(s);
        if (inVisited == m_visited.end()) {
            m_visited.insert(s);
        }

        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        vector<State<T>*> neighbors = problem->getAllPossibleStates(*s);
        for (auto i = neighbors.begin(); i != neighbors.end(); ++i) {
            inVisited = m_visited.find(*i);
            if (inVisited == m_visited.end()) {
                m_stack.push(*i);
                (*i)->setCameFrom(s);
            }
        }
    }

    return solution;
}

template <class T, class S>
S DFS<T, S>::backTrace(State<T>* state) {
    S solution, direction;
    int dx, dy;
    int valuePath = 0;
    list<string> trace;
    State<T> *state2 = state;
    vector<State<T> *> path;

    path.push_back(state2);
    while (state2->getCameFrom() != nullptr) {
        path.push_back(state2->getCameFrom());
        state2 = state2->getCameFrom();
    }

    // saving path from source to destination
    while (!path.empty()) {
        State<T> *lastElement = path.back();
        valuePath += lastElement->getValue();
        lastElement->setCost(valuePath);
        path.pop_back();
    }

    while (state->getCameFrom() != nullptr) {
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
        trace.push_back(direction + "(" + to_string(state->getCost()) + ")");
        state = state->getCameFrom();
    }
    for (int i = trace.size(); i > 0; i--) {
        solution += trace.back();
        trace.pop_back();
    }
    return solution;
}

template <class T,class S>
int DFS<T,S>::evaluatedNodes() {
    return m_numOfNodes;
}

#endif //EX4_DFS_H
