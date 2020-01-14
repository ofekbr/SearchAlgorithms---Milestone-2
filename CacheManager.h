//
// Created by shani on 12/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

using namespace std;

#include <unordered_map>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

//change from string to P-problem

template <typename S>
class CacheManager{
public:
    virtual void insert(string key, const S& item);
    virtual const S get(string key);
    virtual bool existSolution(string key);
    virtual void foreach(const function<void(S&)> func);
};


#endif //EX4_CACHEMANAGER_H
