//
// Created by shani on 22/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H

#include "State.h"
#include "Searcher.h"
#include "Searchable.h"
#include <set>
template <class T, class S>
class AStar:public Searcher<Searchable<T>*, S> {
    set<State<T>*> openList;
    int m_numOfNodes = 0;
    set<State<T>*> m_visited;
public:
    S search(Searchable<T> *problem) override;
    static S backTrace(State<T>*);
    int evaluatedNodes();
};

template <class T, class S>
S AStar<T,S>::search(Searchable<T> *problem) {
   
}
#endif //EX4_ASTAR_H
