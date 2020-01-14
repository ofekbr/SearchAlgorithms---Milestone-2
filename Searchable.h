//
// Created by ofeks on 14/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include <list>
#include <vector>
#include "State.h"

template <typename T>
class Searchable {
    string m_matrixName;
    State<pair<int,int>> m_initialState;
    State<pair<int,int>> m_goalState;
    vector<vector<State<pair<int,int>>>> m_matrix;
public:
    virtual State<T>* getInitialState() = 0;
    virtual State<T> getGoalState() = 0;
    virtual list<State<T>> getAllPossibleStates(State<T> s) = 0;
};

#endif //EX4_SEARCHABLE_H
