#ifndef T_WORKER_H
#define T_WORKER_H

#include <thread>
#include <unistd.h>

#include "epollhandler.hpp"

class ThreadWorker{
    private:
        std::jthread thr;
        EpollHandler e_handler;
        int how_full; //out of 0..FD_FOREACH_THR;
    public:
        ThreadWorker();
        ~ThreadWorker(); 
        int UpdateState();
        EpollHandler *getEpollHandler();
};

struct compareState{
        bool operator()(ThreadWorker* a, ThreadWorker* b) const { return a->UpdateState() < b->UpdateState(); }
};

#endif