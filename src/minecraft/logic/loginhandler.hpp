#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H 

#include <memory>
#include <sqlite3.h>

#include "../../packet/packets/p_LoginRequest.hpp"
#include "../../packet/packets/p_HandShake.hpp"
#include "../../packet/packets/packet.hpp"

class LoginHandler{
    protected:
    public:
        std::unique_ptr<DsPacket> handlepacket(std::unique_ptr<DsPacket> p);
        DsPacket* handleHandshake(p_HandShake* pack);
        DsPacket* handleLoginRequest(p_LoginRequest* pack);
};

#endif