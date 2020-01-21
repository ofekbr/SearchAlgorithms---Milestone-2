//
// Created by shani on 15/01/2020.
//

#ifndef EX4_MYQUEUE_H
#define EX4_MYQUEUE_H

#include "State.h"
#include <set>
#include <algorithm>
#include <queue>


template<
        class T,
        class Container = std::vector<T>,
        class Compare = std::greater<typename Container::value_type >
> class MyQueue : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
    std::priority_queue<
            T,
            Container,
            Compare>::container_type::const_iterator const_iterator;

    //explicit MyQueue(const Compare &x) : priority_queue<T, Container, Compare>(x) {}

    T find(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return *first;
            ++first;
        }
        return *last;
    }

    bool contains(const T&val) const {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return true;
            ++first;
        }
        return (last != this->c.cend());

    }
};
/*
template <class T>
struct StateCompere {
    bool operator()(const State<T>&left, const State<T>&right) {
        return left.getCost() < right.getCost();
    }
};
*/

/*
class MyPriorityQueue:public priority_queue<pair<int,int>>{
    //multiset<State<pair<int,int>>> m_priorityQueue;
public:
    State<pair<int,int>> find(State<pair<int,int>> state);
    //void insert(State<pair<int,int>> state);
    //State<pair<int,int>> popMin();
    //int size();
    bool contains(State<pair<int,int>> state);
};

*/
#endif //EX4_MYQUEUE_H
