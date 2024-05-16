#ifndef T_POOL_H
#define T_POOL_H

#include <array>

#include "../headers/defines.hpp"
#include "../helpers/logger.hpp"
#include "threadworker.hpp"


class ThreadPool{
    private:
        Logger* lg;
        std::array<ThreadWorker*, TP_MAX_THREADS> threads;
    public:
        ThreadPool();
        ~ThreadPool();
        void close();
        void AllocateJob(uint32_t fd);
        void CleanUp(); 
};

#endif