//
// Created by shani on 23/01/2020.
//

#ifndef EX4_ASTARSTATECOMPARE_H
#define EX4_ASTARSTATECOMPARE_H

#include "State.h"
#include <cmath>

template <class T>
State<T>* goal;

template <class T>
int heuristic(State<T>* state) {
    int dx = state->getPos().first - goal<T>->getPos().first;
    int dy = state->getPos().second - goal<T>->getPos().second;
    int h = sqrt(pow(dx,2) + pow (dy,2));
    return h;
}


template <class T>
struct AStarStateCompare {
    bool operator()(State<T> *lhs, State<T> *rhs)
    {
        return (lhs->getCost() + heuristic(lhs)) > (rhs->getCost()+ heuristic(rhs));
    }
    ~AStarStateCompare()= default;
};



#endif //EX4_ASTARSTATECOMPARE_H
