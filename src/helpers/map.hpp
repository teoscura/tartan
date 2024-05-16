#ifndef TSMAP_H
#define TSMAP_H

#include <condition_variable>
#include <cstddef>
#include <map>
#include <mutex>
#include <utility>

#include "loggerhandler.hpp"

template<typename K, typename O>
class ThreadSafeMap{
    private:
        std::map<K, O> map;
        std::mutex mut;
        std::condition_variable var;
        Logger* l;
    public:
        ThreadSafeMap<K, O>();
        bool contains(const K& key);
        std::size_t size();
        void erase(const K& key);
        void insert(const std::pair<K,O>& pair);
};

template<typename K, typename O>
ThreadSafeMap<K, O>::ThreadSafeMap(){
    this->l = LoggerHandler::getLogger();
}

template<typename K, typename O>
bool ThreadSafeMap<K,O>::contains(const K& key){  
    bool isthere;
    std::unique_lock<std::mutex> lock(mut); 
    isthere = this->map.contains(key); 
    lock.unlock();
    var.notify_one(); 
    return isthere;
};

template<typename K, typename O>
std::size_t ThreadSafeMap<K,O>::size(){  
    std::unique_lock<std::mutex> lock(mut);
    lock.unlock();
    var.notify_one(); 
    return this->map.size();
};

template<typename K, typename O>
void ThreadSafeMap<K,O>::erase(const K& key){  
    std::unique_lock<std::mutex> lock(mut); 
    if(this->contains(key)){
        this->map.erase(key);
        lock.unlock();
        var.notify_one();
        return;        
    }
    l->LogPrint(ERROR, "Attempted to delete key: {} but key didn't exist!\n", key);
    lock.unlock();
    var.notify_one();
};

template<typename K, typename O>
void ThreadSafeMap<K,O>::insert(const std::pair<K,O>& pair){
    std::unique_lock<std::mutex> lock(mut); 
    if(!this->contains(pair.first)){
        this->map.insert(pair);
        lock.unlock();
        var.notify_one();
        return;        
    }
    l->LogPrint(ERROR, "Attempted to insert key: {} but key was already present!\n", pair.first);
    lock.unlock();
    var.notify_one();
}

#endif