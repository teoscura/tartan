#ifndef TSMAP_H
#define TSMAP_H

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <set>
#include <string>

#include "loggerhandler.hpp"

template<typename O>
class ThreadSafeSet{
    private:
        std::set<O> set;
        std::mutex mut;
        std::condition_variable var;
        Logger* l;
    public:
        ThreadSafeSet<O>();
        bool contains(const O& object);
        bool containsUsername(std::u16string string);
        std::size_t size();
        void erase(const O& obj);
        void insert(const O object);
};

template<typename O>
ThreadSafeSet<O>::ThreadSafeSet(){
    this->l = LoggerHandler::getLogger();
}

template<typename O>
bool ThreadSafeSet<O>::contains(const O& obj){  
    bool isthere;
    std::unique_lock<std::mutex> lock(mut); 
    isthere = this->set.contains(obj); 
    lock.unlock();
    var.notify_one(); 
    return isthere;
};

template<typename O>
bool ThreadSafeSet<O>::containsUsername(std::u16string username){
    bool isthere = false;
    std::unique_lock<std::mutex> lock(mut); 
    for(O tmp: this->set){
        if(tmp.username == username){
            isthere = true;
        }
    }
    lock.unlock();
    var.notify_one(); 
    return isthere;
}


template<typename O>
std::size_t ThreadSafeSet<O>::size(){  
    std::unique_lock<std::mutex> lock(mut);
    lock.unlock();
    var.notify_one(); 
    return this->set.size();
};

template<typename O>
void ThreadSafeSet<O>::erase(const O& obj){  
    std::unique_lock<std::mutex> lock(mut); 
    if(this->contains(obj)){
        this->obj.erase(obj);
        lock.unlock();
        var.notify_one();
        return;        
    }
    l->LogPrint(ERROR, "Attempted to delete object: {} but object didn't exist!\n", obj);
    lock.unlock();
    var.notify_one();
};

template<typename O>
void ThreadSafeSet<O>::insert(const O object){
    std::unique_lock<std::mutex> lock(mut); 
    if(!this->contains(object)){
        this->object.insert(object);
        lock.unlock();
        var.notify_one();
        return;        
    }
    l->LogPrint(ERROR, "Attempted to insert object: {} but object was already present!\n", object);
    lock.unlock();
    var.notify_one();
}

#endif