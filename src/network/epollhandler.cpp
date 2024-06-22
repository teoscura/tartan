#include "epollhandler.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <sys/epoll.h>

#include "../helpers/loggerhandler.hpp"
#include "../util/byteops.hpp"
#include "../headers/defines.hpp"

EpollHandler::EpollHandler(uint32_t id, PacketDeserializer* pdeserial,PacketSerializer*pserial) : 
    deserializer(pdeserial), 
    serializer(pserial),
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
    Packet ptr;
    auto packetQueue = serializer->get_next()->get_map(this->info.ID);
    for (i = 0; i < this->info.ready; i++) {
        fd = events[i].data.fd;
        if (events[i].events == (EPOLLIN | EPOLLOUT)){
            handleRead(fd);
        } 
    }
    while(packetQueue->size()>0){
        ptr = std::move(packetQueue->front());
        auto tmp = ptr.info.epoll_fd;
        packetQueue->erase(packetQueue->begin());
        handleWrite(tmp, ptr);
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
        uint8_t i[] = { 0xFF, 0x00, 0x00};
        this->deserializer->addPacket(Packet(std::vector<uint8_t>(i, i+3), PacketReturnInfo(fd, this->info.ID)));
    }
    else {
        Packet pack = Packet(std::vector<uint8_t>(buffer,buffer+nread), PacketReturnInfo(fd, this->info.ID));
        lg->LogPrint(INFO, "Incoming Packets from: {}/{}\n{}", fd, this->info.ID, hexStr(pack.bytes.data(), nread));
        this->deserializer->addPacket(pack);
    }
}

void EpollHandler::handleWrite(uint32_t fd, Packet pack){
    int bytes = send(fd, pack.bytes.data(), pack.bytes.size(), 0);
    if (bytes == -1) {
        lg->LogPrint(ERROR, "Couldn't write to FD #", fd);
        std::cerr << "[ERROR] Couldn't write to FD #"<<fd<<"\n";
        eventOp(fd, EPOLLIN|EPOLLOUT, EPOLL_CTL_DEL);
    }
    else{
        lg->LogPrint(INFO, "Sent packet to: {}\n{}", fd, hexStr(pack.bytes.data(), pack.bytes.size()));
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