//
// Created by shani on 15/01/2020.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H


#include "Searcher.h"
#include "Searchable.h"
#include "State.h"
#include <queue>
#include "unordered_set"
#include "MyPriorityQueue.h"

using namespace std;

template <typename T>
class BestFS: public Searcher<Searchable<pair<int,int>>, string>{
    MyPriorityQueue<State<T>> openList;
    int m_numOfNodes;
public:
    string search(Searchable<T> problem) override;
    string backTrace(State<T>);
    int evaluatedNodes();
};


template <class T>
int BestFS<T>::evaluatedNodes() {
    return m_numOfNodes;
}
template<class T>
string BestFS<T>::backTrace(State<T> state) {
    string solution;
    while(state.cameFrom() != nullptr){
        solution += state.getCameFromPlacement() +"(" + state.getCost() + ")";
        state = state.cameFrom();
    }
    return solution;
}
template<typename T>
string BestFS<T>::search(Searchable<T> problem) {
    m_numOfNodes = 0;
    unordered_set<State<T>> closed;
    openList.insert(problem.getInitialState());
    while (openList.size() > 0) {
        m_numOfNodes++;
        State<T> n = openList.popMin();
        closed.insert(n); //so we wont check again

        if (problem.getGoalState().equals(n)) {
            string solution = backTrace(n);
            return solution;
        }
        //create n's successor
        list<State<T>> neighbors = problem.getAllPossibleStates(n);
        //for each successor do:
        for (auto successor = neighbors.begin(); successor != neighbors.end(); successor++) {
            auto inClosed = closed.find(*successor);
            //if successor is not in closed and not in open
            if (inClosed == neighbors.end() && !openList.contains(*successor)) {
                //update that we came to it from n
                *successor.setCameFrom(n);
                *successor.setCost(n.getCost() + *successor.getValue());
                openList.push(*successor);
            } else if((n.getCost()+ *successor.getValue() < *successor.getCost())){ // if the new path is better than previous one
                //if it is not in the open add it to the open
                if(!openList.contains(*successor)){
                    openList.push(*successor);
                } else {
                    //adjust its priority
                    openList.find(*successor).setCost(n.getCost() + *successor.getValue());
                    openList.find(*successor).setCameFrom(n);
                }
            }
        }
    }
    return string();
}



#endif //EX4_BESTFS_H
