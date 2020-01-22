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
    State<T> *m_initialState;
    State<T> *m_goalState;
    vector<vector<State<T>>> m_matrix;

public:
    //interface function
    Matrix(vector<vector<State<T>>> matrix){
        m_matrix = matrix;
    }

    void setStartGoal(State<T> *initialState, State<T> *goalState) {
        m_initialState = initialState;
        m_goalState = goalState;
    }

    vector<vector<State<T>>>* getMatrix() {
        return &m_matrix;
    }

    State<T>* getInitialState(){
        return m_initialState;
    }

    bool isGoalState(State<T> state){
        return m_goalState->equals(state);
    }

    State<T>* getGoalState() override {
        return m_goalState;
    }


    vector<State<T>*> getAllPossibleStates(State<T> state) override{
        vector<State<T>*> neighbors;
        State<T> *up, *down, *left, *right;
        int row = state.getPos().first;
        int col = state.getPos().second;
        try {
            up = &m_matrix.at(row-1).at(col);
            up->setCameFromPlacement("UP");
            if (up->getValue() >= 0){
                neighbors.push_back(up);
            }
        } catch (out_of_range &exp) {}
        try {
            down = &m_matrix.at(row + 1).at(col);
            down->setCameFromPlacement("DOWN");
            if (down->getValue() >= 0){
                neighbors.push_back(down);
            }
        } catch (out_of_range &exp) {}
        try {
            left = &m_matrix.at(row).at(col - 1);
            left->setCameFromPlacement("LEFT");
            if (left->getValue() >= 0){
                neighbors.push_back(left);
            }
        } catch (out_of_range &exp) {}
        try {
            right = &m_matrix.at(row).at(col + 1);
            right->setCameFromPlacement("RIGHT");
            if (right->getValue() >= 0){
                neighbors.push_back(right);
            }
        } catch (out_of_range &exp) {}
        return neighbors;
    }

    void setMatrixName(const size_t &mMatrixName) {
        m_matrixName = to_string(mMatrixName);
    }

    //class function
    string getName(){
        return m_matrixName;
    }

    string serialize(const string& str){
        //hash to matrix
        hash<string> hashStr;
        m_matrixName = hashStr(str);
        int f = 5;
    }

    void updateCost(int cost){

        //iterating over the vector of vector
        for(auto itRow = m_matrix.begin(); itRow != m_matrix.end(); ++itRow) {
            //iterating in row over every number
            for (auto it = itRow->begin(); it != itRow->end(); ++it){
                (*it).setCost(cost);
            }
        }

    };

};
#endif //EX4_MATRIX_H
