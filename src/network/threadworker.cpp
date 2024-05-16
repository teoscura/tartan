#include "threadworker.hpp"

ThreadWorker::ThreadWorker(){
    thr = std::jthread(&EpollHandler::mainLoop, &e_handler);
}

int ThreadWorker::UpdateState(){
    this->how_full = this->e_handler.getHowMany();
    return this->how_full;
}

EpollHandler* ThreadWorker::getEpollHandler(){
    return &e_handler;
}

ThreadWorker::~ThreadWorker(){
    e_handler.shutdown();
    e_handler.~EpollHandler();
    thr.join();
}
