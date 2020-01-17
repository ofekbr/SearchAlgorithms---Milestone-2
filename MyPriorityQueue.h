//
// Created by shani on 15/01/2020.
//

#ifndef EX4_MYPRIORITYQUEUE_H
#define EX4_MYPRIORITYQUEUE_H

#include "State.h"
#include <queue>
#include <set>
template <typename T>
class MyPriorityQueue : public priority_queue<State<T>> {

    multiset<State<T>> m_priorityQueue;

public:
    State<T> find(State<T> state) {
        return *m_priorityQueue.find(state);
    };

    void insert(State<T> state){
        m_priorityQueue.insert(state);
    };
    State<T> topMin(State<T>) {
        // Get the minimum element
        typename multiset<State<T>>::iterator minElement = m_priorityQueue.begin();
        typename multiset<State<T>>::iterator it;

        for(it = m_priorityQueue.begin(); it != m_priorityQueue.end(); ++it) {
            if (*it < *minElement){
                minElement = it;
            }
        }

        // return the minimum element
        return *minElement;
    };
    State<T> popMin(State<T> state) {
        typename multiset<State<T>>::iterator minElement = m_priorityQueue.begin();
        typename multiset<State<T>>::iterator it;

        for(it = m_priorityQueue.begin(); it != m_priorityQueue.end(); ++it) {
            if (*it < *minElement){
                minElement = it;
            }
        }
        //delete from queue
        m_priorityQueue.erase(it);
        //return min
        return *minElement;
    };
    int size(){
        return m_priorityQueue.size();
    }
    bool contains(State<T> state) {
        auto it = m_priorityQueue.find(state);
        return (it != m_priorityQueue.end());
    }

};


#endif //EX4_MYPRIORITYQUEUE_H
