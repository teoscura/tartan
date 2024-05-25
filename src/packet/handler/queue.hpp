#ifndef QUEUE_H
#define QUEUE_H

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>

#include "../packets/packet.hpp"

template<class T>
class ThreadSafeQueue{
    private:
        std::queue<T> queue;
        std::mutex mut;
        std::condition_variable var;
    public:
        // Pushes an element to the queue 
        bool isEmpty();
        void push(T item);
        T pop();
        const std::size_t size();
};

template<class T>
void ThreadSafeQueue<T>::push(T item){  
    std::unique_lock<std::mutex> lock(mut); 
    queue.push(std::move(item)); 
    lock.unlock();
    var.notify_one(); 
}

template<class T>
T ThreadSafeQueue<T>::pop(){
    std::unique_lock<std::mutex> lock(mut); 
    var.wait(lock, [this]() { return !queue.empty(); });
    T item = std::move(queue.front()); 
    queue.pop(); 
    return std::move(item); 
}

template<class T>
bool ThreadSafeQueue<T>::isEmpty(){
    bool result;
    std::unique_lock<std::mutex> lock(mut); 
    result = queue.empty();
    lock.unlock();
    var.notify_one();
    return result;
}

template<class T>
const std::size_t ThreadSafeQueue<T>::size(){
    std::size_t res;
    std::unique_lock<std::mutex> lock(mut); 
    res = queue.size();
    lock.unlock();
    var.notify_one();
    return res;
}

using PacketQueue = ThreadSafeQueue<std::unique_ptr<DsPacket>>;

#endif