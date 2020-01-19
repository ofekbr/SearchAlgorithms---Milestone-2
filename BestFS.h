//
// Created by shani on 15/01/2020.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H


#include "Searcher.h"
#include "Searchable.h"
#include "State.h"
#include "MyPriorityQueue.h"
#include <algorithm>

using namespace std;

template <class T, class S>
class BestFS: public Searcher<Searchable<T>*, S> {
    //MyPriorityQueue<pair<int,int>> openList;
    MyQueue<State<T>> openList;
    int m_numOfNodes = 0;
public:
    S search(Searchable<T> *problem) override;
    static S backTrace(State<T>);
    int evaluatedNodes();
};


template <class T, class S>
int BestFS<T, S>::evaluatedNodes() {
    return m_numOfNodes;
}

template <class T, class S>
S BestFS<T, S>::backTrace(State<T> state) {
    S solution;
    while(state.cameFrom() != nullptr){
        solution += state.getCameFromPlacement() +"(" + to_string(state.getCost()) + ")";
        state = *state.cameFrom();
    }
    return solution;
}

template <class T, class S>
S BestFS<T, S>::search(Searchable<T> *problem) {
    m_numOfNodes = 0;
    set<State<T>> closed;
    openList.push(problem->getInitialState());
    while (openList.size() > 0) {
        m_numOfNodes++;
        State<T> n = openList.top();
        openList.pop();

        //so we wont check again
        if (problem->getGoalState().equals(n)) {
            S solution = backTrace(n);
            return solution;
        }
        //create n's successor
        vector<State<T>> neighbors = problem->getAllPossibleStates(n);

        //for each successor do:
        for (auto successor = neighbors.begin(); successor != neighbors.end(); successor++) {
            auto inClosed = find(neighbors.begin(), neighbors.end(),*successor);
            //if successor is not in closed and not in open
            if (inClosed == neighbors.end() && !openList.contains(*successor)) {
                //update that we came to it from n
                (*successor).setCameFrom(&n);
                (*successor).setCost(n.getCost() + (*successor).getValue());
                openList.push(*successor);
            } else if(((n.getCost() + (*successor).getValue()) < (*successor).getCost())){ // if the new path is better than previous one
                //if it is not in the open add it to the open
                if(!openList.contains(*successor)){
                    openList.push(*successor);
                } else {
                    //adjust its priority
                    openList.find(*successor).setCost(n.getCost() + (*successor).getValue());
                    openList.find(*successor).setCameFrom(&n);
                }
            }
        }
    }
    throw "bestFS failed";
}


#endif //EX4_BESTFS_H
