//
// Created by shani on 15/01/2020.
//

#include "ObjectAdapter.h"


template <class P, class S>
S ObjectAdapter<P,S>::solve(P problem) {
    return m_searcher.search(problem);
}