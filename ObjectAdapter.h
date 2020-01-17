//
// Created by shani on 15/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H


#include "Solver.h"
#include "Searcher.h"

template<typename P, typename  S>
class ObjectAdapter: public Solver<P,S> {
Searcher<P,S> m_searcher;
public:
    ObjectAdapter(const Searcher <P, S> &searcher) : m_searcher(searcher) {}
    S solve(P problem) override ;
};


#endif //EX4_OBJECTADAPTER_H
