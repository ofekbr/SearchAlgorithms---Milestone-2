//
// Created by shani on 12/01/2020.
//

#ifndef EX4_CFCASHMANAGER_H
#define EX4_CFCASHMANAGER_H

#include "CacheManager.h"
//declaration
template <class S>
bool isItemInFile(string);
template <typename S>
const S getFromFile(string);


template <typename P,typename S>
class CFClassManager: public CacheManager<P,S>{
    unordered_map <string,typename list<pair<string,S>>::iterator> m_cache;
    //list of keys 1st-MSU , last-LRU
    list<pair<string,S>> m_items;
    unsigned int m_capacity;
public:
    CFClassManager<S>(int size): m_capacity(size) {}
    void insert(string key, const S& item);
    const S get(string key);
    void foreach(const function<void(S&)> func);
};


template <typename P,typename S>
void CFClassManager<P,S>::foreach(const function<void(S&)> func){
    typename list<pair<string,S>>::iterator it;
    for(it = m_items.begin(); it != m_items.end(); ++it){
        func(it->second);
    }
}


template <typename P,typename S>
void CFClassManager<P,S>::insert(string key, const S& newItem) {

    auto it = m_cache.find(key);

    //if key exist
    if (it != m_cache.end()){
        m_items.erase(it->second);
        m_items.push_front(pair <string, S>(key, newItem));
        m_cache[key] = m_items.begin();
        updateInFile(key, newItem);
    } else{
        //if there is place for the new item
        if(m_items.size() < m_capacity) {
            m_items.push_front(pair <string, S>(key,newItem));
            m_cache[key] = m_items.begin();
            updateInFile(key, newItem);
        } else {
            string lastKey = m_items.back().first;
            m_items.pop_back();
            m_items.push_front(pair <string, S>(key, newItem));
            m_cache.erase(m_cache.find(lastKey));
            m_cache[key] = m_items.begin();
            updateInFile(key, newItem);
        }
    }
}

template <typename P,typename S>
const S CFClassManager<P,S>::get(string key){
    auto it = m_cache.find(key);
    //check if in cash:
    if (it != m_cache.end()){
        m_items.erase(it->second);
        m_items.push_front(pair <string, S>(key, it->second->second));
        m_cache[key] = m_items.begin();
        return m_cache.begin()->second->second;
    } else if (isItemInFile<S>(key)) {
        string lastKey = m_items.back().first;
        m_items.pop_back();
        m_cache.erase(m_cache.find(lastKey));
        m_items.push_front(pair <string, S>(key, getFromFile<S>(key)));
        m_cache[key] = m_items.begin();
        return getFromFile<S>(key);
    } else {
        //not in cache nor file
        throw "an error";
    }
}

//file functions
template <typename P,typename S>
const S getFromFile(string key) {
    S item;
    string s = item.class_name + "_" + key +".bin";
    fstream file(s,ios::in | ios::binary);

    //read from file
    if (!file) {
        throw "can't open file";
    } else{
        file.read((char*)&item,sizeof(item));
        return item;
    }
}

template <typename P,typename S>
void updateInFile(string key, const S& item){
    string s = item.class_name + "_" + key +".bin";
    fstream file(s,ios::out | ios::binary);

    //write to file
    if (!file) {
        //the key is not in file
        throw "can't open file";
    } else{
        file.write((char*)& item, sizeof(item));
    }
}

template <typename P,typename S>
bool isItemInFile(string key) {
    S item;
    string s = item.class_name + "_" + key +".bin";
    fstream file(s,ios::in | ios::binary);

    return file.is_open();
}

#endif //EX4_CFCASHMANAGER_H
