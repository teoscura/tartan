#ifndef QUEUE_H
#define QUEUE_H

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <optional>

#include "../packets/packet.hpp"

template<class T>
class ThreadSafeQueue{
    private:
        std::vector<T> vector;
        std::mutex mut;
        std::condition_variable var;
    public:
        // Pushes an element to the queue 
        bool isEmpty();
        void push(T item);
        std::optional<T> pop();
        const std::size_t size();
};

template<class T>
void ThreadSafeQueue<T>::push(T item){  
    std::unique_lock<std::mutex> lock(mut); 
    vector.push_back(item); 
    lock.unlock();
    var.notify_one(); 
}

template<class T>
std::optional<T> ThreadSafeQueue<T>::pop(){
    std::unique_lock<std::mutex> lock(mut); 
    if(vector.empty()){
        return std::nullopt;
    }
    T item = vector.front();
    vector.erase(vector.begin());
    var.notify_one();
    return item;
}

template<class T>
bool ThreadSafeQueue<T>::isEmpty(){
    return vector.empty();
}

template<class T>
const std::size_t ThreadSafeQueue<T>::size(){
    return vector.size();
}

using PacketQueue = ThreadSafeQueue<std::shared_ptr<DsPacket>>;

#endif