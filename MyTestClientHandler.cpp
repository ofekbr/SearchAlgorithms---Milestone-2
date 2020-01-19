//
// Created by shani on 12/01/2020.
//

#include "CacheManager.h"
#include "ClientHandler.h"
#include "Matrix.h"
#include "Searcher.h"
#include <unistd.h>
#include <deque>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <cstring>

using namespace std;

void MyTestClientHandler::handleClient(int socket) {

//TODO fix getmatrixname - either add it to the searchable interface of keep the name somewhere else
    Searchable<pair<int,int>> *problem = createProblem(socket);

    string solution;
//    if (m_cacheManager.existSolution(problem.getMatrixName())){
//        solution = m_cacheManager.get(problem.getMatrixName());
//    } else {
        //search solution
        //solution = solver.solve(BestFS(),problem);
        //m_cacheManager.insert(problem.getMatrixName(), solution);
 //   }
    sendSolution(socket,"solution----------------555");
    //sendSolution(socket,solution);
    close(socket);
}

Searchable<pair<int,int>>* MyTestClientHandler::createProblem(int socket){

    char buffer[1] = {0}, curNum[100] = {0};
    int numRow=0, numCol = 0, firstNumCol=0;
    int i, value;
    vector<vector<int>> matrix;
    vector<int> curRow;
    vector<int> start;
    vector<int> goal;
    string matrixName;

    //lexing the data from the socket
    while (true) {
        read(socket, buffer, 1);
        for (i = 0; buffer[0] != ','; i++) {
            if (buffer[0] == '\n') {
                matrixName += buffer[0];
                break;
            }
            if (buffer[i] != ' '){
                matrixName += buffer[0];
                curNum[i] = buffer[0];
            } else {
                i--;
            }
            read(socket, buffer, 1);
        }

        value = stoi(curNum);
        numCol++;
        curRow.push_back(value);
        fill(curNum, curNum + i, 0);

        if (buffer[0] == '\n') {
            if (numRow == 0) {
                firstNumCol = numCol;
            }
            if (numCol < firstNumCol) {
                if (start.empty()){
                    start = curRow;
                } else {
                    goal = curRow;
                    break;
                }
            } else {
                matrix.push_back(curRow);
            }
            numCol=0;
            numRow++;
            curRow.clear();
        } else {
            //if it was","
            matrixName += buffer[0];
        }
    }

    vector<vector<State<pair<int,int>>>> matrixOfState = createStateMatrix(matrix, numRow-1,firstNumCol);

    //creating a searchable object- matrix
    State<pair<int,int>> startState(pair<int,int>(start.at(0),start.at(1)));
    State<pair<int,int>> goalState(pair <int, int> (goal.at(0),goal.at(1)));

    //cost is the value in the specific point
    startState.setCost(matrix[start.at(0)][start.at(1)]);
    goalState.setCost(matrix[goal.at(0)][goal.at(1)]);

    auto problem = new Matrix<pair<int,int>>(startState,goalState, matrixOfState);
    hash<string> hashStr;
    std::size_t temp = hashStr(matrixName);
    problem->setMMatrixName(temp);

    return problem;
}


vector<vector<State<pair<int,int>>>> MyTestClientHandler::createStateMatrix(vector<vector<int>> vecMatrix, int numRow, int numCol){
    int i = 0, j=0;

    vector<vector<State<pair<int,int>>>> matrixOfState;
    vector<State<pair<int,int>>> rowOfState;

    //iterating over the vector of vector
    for(auto itRow = vecMatrix.begin(); itRow != vecMatrix.end(); ++itRow) {
        //iterating in row over every number

        for (auto it = itRow->begin(); it != itRow->end(); ++it){
            State<pair<int,int>> state(pair <int, int> (j,i));
            state.setValue(*it);
            state.setCost(0);
            rowOfState.push_back(state);
            ++i;
        }
        matrixOfState.push_back(rowOfState);
        rowOfState.clear();
        i=0;
        ++j;
    }
    return matrixOfState;
}

void MyTestClientHandler::sendSolution(int client_socket, const string& solution) {

    const char* message;
    message = solution.c_str();

    send(client_socket , message , strlen(message) , 0 );
}