//
// Created by shani on 12/01/2020.
//

#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include "State.h"
#include <utility>
#include <vector>
#include <functional>
#include "Searchable.h"

template <typename T>
class Matrix : public Searchable<T>{
    string m_matrixName;
    State<pair<int,int>> m_initialState;
    State<pair<int,int>> m_goalState;
    vector<vector<State<pair<int,int>>>> m_matrix;

public:
    //interface function
    Matrix(State<pair<int,int>> initialState, State<pair<int,int>> goalState, vector<vector<State<pair<int,int>>>> matrix)
        :m_initialState(std::move(initialState)),m_goalState(std::move(goalState)), m_matrix(std::move(matrix)){};

    State<pair<int,int>> getInitialState(){
        return m_initialState;
    }

    bool isGoalState(State<pair<int,int>> state){
        return m_goalState.equals(state);
    }

    vector<State<pair<int,int>>> getAllPossibleStates(State<pair<int,int>>){
        //all neighbors?
    }

    //class function
    string getMatrixName(){
        return m_matrixName;
    }
    string serialize(const string& str){
        //hash to matrix
        hash<string> hashStr;
        m_matrixName = hashStr(str);
    }

};
#endif //EX4_MATRIX_H
