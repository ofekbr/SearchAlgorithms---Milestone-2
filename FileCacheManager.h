//
// Created by shani on 12/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H

using namespace std;

#include <unordered_map>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>

//declaration
template <class T>
bool isItemInFile(string);
template <typename T>
const T getFromFile(string);


template <typename T>
class FileCacheManager{
    unordered_map <string,typename list<pair<string,T>>::iterator> m_cache;
    list<pair<string,T>> m_items;
    unsigned int m_capacity = m_cache.size();
public:

    //FileCacheManager<T>(int size):m_capacity(size) {}
    FileCacheManager<T>(){}
    void insert(string key, const T& item);
    bool existSolution(string key);
    const T get(string key);
    void foreach(const function<void(T&)> func);
};

template <class T>
bool FileCacheManager<T>::existSolution(string key) {
    //check if in cash:
    auto it = m_cache.find(key);
    return (it != m_cache.end());
}

template <class T>
void FileCacheManager<T>::foreach(const function<void(T&)> func){
    typename list<pair<string,T>>::iterator it;
    for(it = m_items.begin(); it != m_items.end(); ++it){
        func(it->second);
    }
}

template <class T>
void FileCacheManager<T>::insert(string key, const T& newItem) {
    m_cache.push_back(newItem);
    updateInFile(key, newItem);
}

template <class T>
const T FileCacheManager<T>::get(string key){
    auto it = m_cache.find(key);
    //check if in cash:
    if (it != m_cache.end()){
        throw "doesn't exist in files";
    } else {
        return getFromFile<T>(key);
    }
}

//file functions
template <class T>
const T getFromFile(string key) {
    T item;
    string s = key +".bin";
    fstream file(s,ios::in | ios::binary);

    //read from file
    if (!file) {
        throw "can't open file";
    } else{
        file.read((char*)&item,sizeof(item));
        return item;
    }
}

template <class T>
void updateInFile(string key, const T& item){
    string s = key +".bin";
    fstream file(s,ios::out | ios::binary);

    //write to file
    if (!file) {
        //the key is not in file
        throw "can't open file";
    } else{
        file.write((char*)& item, sizeof(item));
    }
}


#endif //EX4_FILECACHEMANAGER_H
