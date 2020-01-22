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
    stack<State<T>*> m_stack;
    set<State<T>*> m_visited;
    int m_numOfNodes = 0;
public:
    S search(Searchable<T> *problem) override;
    int evaluatedNodes();
};

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
            solution += (s->getCameFromPlacement()) + "(" + to_string(pathCost+s->getValue()) + ")";
            break;
        }
        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        auto inVisited = m_visited.find(s);
        if (inVisited == m_visited.end())
        {
            //save path
            pathCost += s->getValue();
            s->setCost(pathCost);
            if (s != problem->getInitialState())
                solution += (s->getCameFromPlacement()) + "(" + to_string(s->getCost()) + ")";
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
            }
        }
    }

    return solution;
}

template <class T,class S>
int DFS<T,S>::evaluatedNodes() {
    return m_numOfNodes;
}

#endif //EX4_DFS_H
