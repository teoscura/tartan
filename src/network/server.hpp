#ifndef SERVER_H
#define SERVER_H

#include "epollhandler.hpp"
#include <netinet/in.h>
#include <thread>

struct Connection{
    uint32_t socksize = sizeof(sockaddr_in);
    uint32_t sockfd;
    sockaddr_in sock;
};

class Server{
    private:
        EpollHandler e_handler;
        std::jthread e_handler_thr;
        Connection listener;
    public:
        Server(PacketDeserializer* pdeserial,PacketSerializer*pserial);
        ~Server();
        void listen_loop();
        void addFileDescriptor(uint32_t fd);
};

#endif
