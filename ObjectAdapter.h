//
// Created by shani on 15/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H


#include "Solver.h"
#include "Searcher.h"

template<class P, class  S>
class ObjectAdapter: public Solver<P,S> {
Searcher<P,S> *m_searcher;
public:
    explicit ObjectAdapter(Searcher <P, S> *searcher) : m_searcher(searcher) {}
    S solve(P problem) override {
        return m_searcher->search(problem);
    }
    ObjectAdapter<P,S>* clone() {
        return new ObjectAdapter(m_searcher->clone());
    }
};


#endif //EX4_OBJECTADAPTER_H
