#include "epollhandler.hpp"

#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <memory>
#include <sys/epoll.h>

#include "../packet/handler/p_deserhandler.hpp"
#include "../packet/handler/p_serialhandler.hpp"
#include "../helpers/loggerhandler.hpp"
#include "../util/byteops.hpp"
#include "../headers/defines.hpp"

EpollHandler::EpollHandler(uint32_t id) : 
    deserializer(DeserializerHandler::getDeserializer()), 
    serializer(this->serializer = SerializerHandler::getSerializer()),
    lg(LoggerHandler::getLogger()){
    this->info.ID = id;
    this->info.running = true;
    this->info.epoll_fd = epoll_create1(0);
}

void EpollHandler::mainLoop(){
    
    while(this->info.running) {
        this->info.ready = epoll_wait(this->info.epoll_fd, events, FD_FOREACH_THR, TIMEOUT);
        handleEvents();
    }
}
void EpollHandler::handleEvents(){
    int i;
    int fd;
    std::unique_ptr<Packet> ptr;
    std::queue<std::unique_ptr<Packet>>* packetQueue = serializer->get_next()->get_map(this->info.ID);
    for (i = 0; i < this->info.ready; i++) {
        fd = events[i].data.fd;
        if (events[i].events == (EPOLLIN | EPOLLOUT)){
            handleRead(fd);
        } 
    }
    while(packetQueue->size()>0){
        ptr = std::move(packetQueue->front());
        packetQueue->pop();
        handleWrite(ptr->info.epoll_fd, std::move(ptr));
    }
}

void EpollHandler::handleRead(uint32_t fd){
    int nread;
    uint8_t buffer[BUF_MAX_SIZE];
    nread = read(fd, buffer, BUF_MAX_SIZE); 
    if (nread == -1) {
        lg->LogPrint(ERROR, "Couldn't read from FD #{}", fd);
        std::cerr << "[ERROR] Couldn't read from FD #"<<fd<<"\n";
        eventOp(fd, EPOLLIN|EPOLLOUT, EPOLL_CTL_DEL);
        close(fd);
    }
    else if (nread == 0) {
        lg->LogPrint(INFO, "Client #{} closed.", fd);
        std::cout<<"Client closed.\n";
        eventOp(fd, EPOLLIN|EPOLLOUT, EPOLL_CTL_DEL);
        close(fd);
    }
    else {
        lg->LogPrint(DATA, "Incoming Packets from: {}/{}\n[DATA] {}", fd, this->info.ID, hexStr(buffer, nread));
        std::cout<<"Read message from fd: "<<fd<<" from thread: "<< this->info.ID<<"\n";
        std::cout<<"[nread = " << nread <<"]\n";
        PacketReturnInfo info;
        info.epoll_fd = fd;
        info.thread_ID = this->info.ID;

        std::unique_ptr<Packet> pack = std::make_unique<Packet>(buffer, nread, info);
        this->deserializer->addPacket(std::move(pack));
    }
}

void EpollHandler::handleWrite(uint32_t fd, std::unique_ptr<Packet> pack){
    int bytes;
    bytes = send(fd, pack->bytes, pack->size, 0);
    strerror(errno);
    if (bytes == -1) {
        lg->LogPrint(ERROR, "Couldn't write to FD #", fd);
        std::cerr << "[ERROR] Couldn't write to FD #"<<fd<<"\n";
        eventOp(fd, EPOLLIN|EPOLLOUT, EPOLL_CTL_DEL);
    }
    else{
        lg->LogPrint(DATA, "Sent packet to: {}\n{}", fd, hexStr(pack->bytes, pack->size));
        std::cout<<"[INFO] Packet response sent!\n";
    }
}

void EpollHandler::eventOp(uint32_t fd, uint32_t state, uint32_t _op){
    struct epoll_event ev;
    ev.events = state;
    ev.data.fd = fd;
    switch(_op){
        case EPOLL_CTL_ADD:
            if (epoll_ctl(this->info.epoll_fd, EPOLL_CTL_ADD, fd, &ev) < 0) {
                lg->LogPrint(ERROR, "Couldn't add event to EPOLL!");
                std::cerr << "[ERROR] Couldn't add event to epoll! \n";
                close(ev.data.fd);
                return;
            }
            this->allfds.insert(fd);
            break;
        case EPOLL_CTL_DEL:
            if (epoll_ctl(this->info.epoll_fd, EPOLL_CTL_DEL, fd, &ev) < 0) {
                lg->LogPrint(ERROR, "Couldn't remove event from EPOLL!");
                std::cerr << "[ERROR] Couldn't remove event from epoll! \n";
                return;
            }
            close(ev.data.fd);
            this->allfds.erase(fd);
            break;
        case EPOLL_CTL_MOD:
            if (epoll_ctl(this->info.epoll_fd, EPOLL_CTL_MOD, fd, &ev) < 0) {
                lg->LogPrint(ERROR, "Couldn't modify event in EPOLL!");
                std::cerr << "[ERROR] Couldn't modify event in epoll! \n";
                this->allfds.erase(fd);
            }   
            break;
        default:
            break;
    }
}

void EpollHandler::shutdown(){
    this->info.running = false;
}

EpollHandler::~EpollHandler(){
    for(uint32_t fd : allfds){
        close(fd);
    }
}

int EpollHandler::getID(){
    return this->info.ID;
}

int EpollHandler::getHowMany(){
    return this->allfds.size();
}