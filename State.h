//
// Created by shani on 12/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H

#include <string>
#include "algorithm"

using namespace std;

template <typename T>
class State{
    T m_state;
    double m_value;
    double m_cost;
    State<T> *m_cameFrom;
    string m_cameFromPlacement;
public:
    explicit State(T state){
        m_state = state;
    }

    void setCameFromPlacement(const string& placment) {
        m_cameFromPlacement = placment;
    }
    string getCameFromPlacement() {
        return  m_cameFromPlacement;
    }
    void setCost(double cost){
        m_cost = cost;
    }
    void setValue(int value) {
        m_value = value;
    }

    State<T>* cameFrom(){
        return m_cameFrom;
    }
    void setCameFrom(State<T> *mCameFrom) {
        m_cameFrom = mCameFrom;
    }

    double getValue() {
        return m_value;
    }
    double getCost() const{
        return m_cost;
    }
    bool equals(State<T> state){
        return (this->m_state == state.m_state);
    }

    T getPos() {
        return m_state;
    }


    friend bool operator<(const State<T> &c1, const State<T> &c2){
        return (c1.m_cost < c2.m_cost);
    }

    friend bool operator==(const State<T> &c1, const State<T> &c2){
        return c1.m_state == c2.m_state;
    }

};

#endif //EX4_STATE_H
