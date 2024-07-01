#include <arpa/inet.h>
#include <cstdint>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>

#include "../helpers/settingshandler.hpp"
#include "../helpers/loggerhandler.hpp"
#include "epollhandler.hpp"
#include "server.hpp"


Server::Server(PacketDeserializer* pdeserial, PacketSerializer* pserial) : 
    e_handler(pdeserial, pserial){

    uint32_t port = atoi(SettingsHandler::getSettings()->getSettings().at("server_port").c_str());
    if((listener.sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Couldn't create main entry socket!");
        std::cerr<<"[ERROR] Couldn't create main entry socket\n";
        exit(1);
    }
    bzero(&listener.sock, listener.socksize);
    listener.sock.sin_family = AF_INET;

    //FIXME REWORK WHEN CHANGES TO SETTINGS IN SERVERSETTINGS
    inet_pton(AF_INET, SettingsHandler::getSettings()->getSettings().at("server_ip").c_str(), &listener.sock.sin_addr);
    listener.sock.sin_port = htons(port);
    if (bind(listener.sockfd, (struct sockaddr*)&listener.sock, listener.socksize) == -1) {
        LoggerHandler::getLogger()->LogPrint(ERROR, "Couldn't bind to port{}!", port);
        std::cerr << "[ERROR] Couldn't bind to port " << port <<std::endl;
        exit(1);
    }
    LoggerHandler::getLogger()->LogPrint(INFO, "Bound to port: {}", port);
    std::cout << "[INFO] Bound to port: " << port <<std::endl;
    this->e_handler_thr = std::jthread(&EpollHandler::mainLoop, this->e_handler);
}

void Server::listen_loop(){
    sockaddr_in c_sock;
    uint32_t c_sockfd;
    uint32_t size = listener.socksize;
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    char buf[INET_ADDRSTRLEN];
    uint8_t msg[0x1000];
    std::stringstream str;

    while(true){
        listen(listener.sockfd, 0x1000);
        if ((c_sockfd = accept(listener.sockfd, (sockaddr*)&c_sock, &size)) < 0) {
            LoggerHandler::getLogger()->LogPrint(ERROR, "Couldn't accept connection!");
            std::cerr << "[ERROR] Couldn't accept connection!\n";
            exit(-1);
        }
        getnameinfo((sockaddr*)&c_sock, size, host, NI_MAXHOST, svc, NI_MAXSERV, 0);
        str << "Client: ("
              << inet_ntop(AF_INET, &c_sock.sin_addr, buf, INET_ADDRSTRLEN) << ":"
              << ntohs(c_sock.sin_port) << ")";   
        this->addFileDescriptor(c_sockfd);
        LoggerHandler::getLogger()->LogPrint(INFO, "{}", str.str());
        std::cout<<str.str()<<std::endl;
        c_sockfd = 0;
        std::stringstream().swap(str);
    }
}

void Server::addFileDescriptor(uint32_t fd){
    this->e_handler.eventOp(fd, EPOLLIN | EPOLLOUT , EPOLL_CTL_ADD);
}

Server::~Server(){
    close(listener.sockfd);
    bzero(&listener.sock, listener.socksize);
}