//
// Created by ofeks on 20/01/2020.
//

#ifndef EX4_STATEPTRCOMPARE_H
#define EX4_STATEPTRCOMPARE_H

#include "State.h"

template <class T>
struct StatePtrCompare {
    bool operator()(State<T> *lhs, State<T> *rhs)
    {
        return lhs->getCost() > rhs->getCost();
    }
    ~StatePtrCompare()= default;
};
#endif //EX4_STATEPTRCOMPARE_H
