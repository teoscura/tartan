#include <algorithm>
#include <iostream>
#include <sys/epoll.h>

#include "../helpers/loggerhandler.hpp"
#include "threadpool.hpp"

ThreadPool::ThreadPool(){
    this->lg = LoggerHandler::getLogger();
    for(int i=0;i<TP_MAX_THREADS;i++){
        ThreadWorker *threadworker = new ThreadWorker(i); //starts associated EpollHandler
        if(!(threadworker)){
            lg->LogPrint(ERROR, "Couldn't allocate and construct ThreadWorker #{}", i);
            std::cerr << "[ERROR] Couldn't allocate and construct ThreadWorker #"<<i<<"\n";
            exit(1);
        }
        this->threads[i]=threadworker; //starts everything using the nested costructors
    }
}

void ThreadPool::AllocateJob(uint32_t fd){
    CleanUp();
    threads[0]->getEpollHandler()->eventOp(fd, EPOLLIN | EPOLLOUT, EPOLL_CTL_ADD);
    lg->LogPrint(INFO, "Allocating connection to ThreadWorker number: {}", this->threads[0]->getEpollHandler()->getID());
    std::cout << "Allocating to ThreadWorker number: "<< this->threads[0]->getEpollHandler()->getID() <<std::endl;
}

void ThreadPool::CleanUp(){
    for(ThreadWorker *ptr : this->threads){
        ptr->UpdateState();
    }
    std::sort(this->threads.begin(),this->threads.end(), compareState());
}

ThreadPool::~ThreadPool(){
    for(ThreadWorker *ptr : this->threads){
        delete ptr;
    }
}
