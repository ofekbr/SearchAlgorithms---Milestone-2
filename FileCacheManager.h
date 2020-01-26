//
// Created by shani on 12/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

using namespace std;

#include <unordered_set>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <mutex>

template <typename T>
T getFromFile(const string&);
template <typename T>
void updateInFile(const string& key, const T& item);


template <typename T>
class FileCacheManager: public CacheManager<T> {
    unordered_set <string> m_cache;
    unsigned int m_capacity = m_cache.size();
public:
    FileCacheManager<T>()= default;
    void insert(string key, const T& item);
    bool solutionExist(string key);
    T get(string key);
};

template <class T>
bool FileCacheManager<T>::solutionExist(string key) {
    //check if in cash:
    auto it = m_cache.find(key);
    return (it != m_cache.end());
}


template <class T>
void FileCacheManager<T>::insert(string key, const T& newItem) {
    m_cache.insert(key);
    updateInFile(key, newItem);
}

template <class T>
T FileCacheManager<T>::get(string key){
    auto it = m_cache.find(key);
    //check if in cash:
    if (it == m_cache.end()){
        throw "doesn't exist in files";
    } else {
        return getFromFile<T>(key);
    }
}

//file functions
template <class T>
T getFromFile(const string& key) {
    T item;
    string s = key +".txt";
    fstream file(s,ios::in);
    //read from file
    if (!file) {
        throw "can't open file";
    } else{
        std::ifstream stream(s);
        std::getline(stream, item);
        return item;
    }
}

template <class T>
void updateInFile(const string& key, const T& item){
    string s = key +".txt";
    fstream file(s,ios::out);

    //write to file
    if (!file) {
        //the key is not in file
        throw "can't open file";
    } else{
        std::ofstream out(s);
        out << item.c_str();
    }
}

#endif //EX4_FILECACHEMANAGER_H
