//
// Created by shani on 12/01/2020.
//

#include "CacheManager.h"
#include "Solver.h"

template <typename P,typename S>
class MyTestClientHandler{
    Solver<P,S> solver;
    CacheManager<P,S> cm;
};