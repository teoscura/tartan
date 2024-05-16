#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H 

#include <set>
#include <string>
#include <sqlite3.h>

#include "../../packet/packets/p_LoginRequest.hpp"
#include "../../packet/packets/p_HandShake.hpp"
#include "../../packet/packets/packet.hpp"

class LoginHandler{
    private:
        std::set<std::u16string> usernames;
    public:
        DsPacket* handlepacket(DsPacket* p);
        DsPacket* handleHandshake(p_HandShake* pack);
        p_LoginRequest* handleLoginRequest(p_LoginRequest* pack);
};

#endif