#ifndef CONN_STRUCTS_H
#define CONN_STRUCTS_H

#include <netinet/in.h>

struct Connection{
    uint32_t socksize = sizeof(sockaddr_in);
    uint32_t sockfd;
    sockaddr_in sock;
};

struct ClientConnection{
    uint32_t socksize = sizeof(sockaddr_in);
    uint32_t sockfd;
    sockaddr_in sock;
};

struct ServerConnection{
    uint32_t socksize = sizeof(sockaddr_in);
    uint32_t sockfd;
    sockaddr_in sock;
};

#endif
