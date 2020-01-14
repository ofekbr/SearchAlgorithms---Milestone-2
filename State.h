//
// Created by shani on 12/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <string>
#include "algorithm"

using namespace std;

template <typename  T>
class State{
    T m_state;
    double m_cost;
    State<T> *m_cameFrom;
public:
    State(T state){
        m_state = state;
    }
    void setCost(double cost){
        m_cost = cost;
    }
    bool equals(State<T> state){
        return (this->equals(state));
    }


};

#endif //EX4_STATE_H
