#ifndef EPOLL_HANDLER_H
#define EPOLL_HANDLER_H

#include <set>
#include <sys/epoll.h>

#include "../packet/handler/p_deserial.hpp"
#include "../packet/handler/p_serial.hpp"
#include "../helpers/logger.hpp"

struct HandlerState{
    uint32_t epoll_fd;
    uint32_t ready;
};

class EpollHandler{
    private:
        HandlerState info;
        epoll_event events[0x1000];
        std::set<uint32_t> allfds;
        PacketDeserializer* deserializer;
        PacketSerializer* serializer;
        Logger* lg;
    public:    //done
        void mainLoop();
        void shutdown();

        void handleEvents();
        void handleRead(uint32_t fd);
        void handleWrite(uint32_t fd, Packet);
        void eventOp(uint32_t fd, uint32_t state, uint32_t _op);
        
        int getHowMany();
        int getID();
        
        EpollHandler(PacketDeserializer* pdeserial, PacketSerializer*pserial);
        ~EpollHandler(); 
};

#endif