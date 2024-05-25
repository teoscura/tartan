#include "threadworker.hpp"
#include "epollhandler.hpp"

ThreadWorker::ThreadWorker(uint32_t id, PacketDeserializer* pdeserial,PacketSerializer*pserial) : 
    e_handler(id, pdeserial, pserial){
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
