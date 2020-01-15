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

    State<T> getGoalState() override {
        return m_goalState;
    }


    vector<State<pair<int,int>>*> getAllPossibleStates(State<pair<int,int>> state) override{
        vector<State<pair<int,int>>*> neighbors;
        State<pair<int, int>> *up, *down, *left, *right;
        int row = state.getPos().first;
        int col = state.getPos().second;
        try {
            up = &m_matrix.at(row-1).at(col);
            neighbors.push_back(up);
        } catch (out_of_range &exp) {}
        try {
            down = &m_matrix.at(row + 1).at(col);
            neighbors.push_back(down);
        } catch (out_of_range &exp) {}
        try {
            left = &m_matrix.at(row).at(col - 1);
            neighbors.push_back(left);
        } catch (out_of_range &exp) {}
        try {
            right = &m_matrix.at(row).at(col + 1);
            neighbors.push_back(right);
        } catch (out_of_range &exp) {}
        return neighbors;
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
