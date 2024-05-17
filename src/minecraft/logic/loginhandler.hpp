#ifndef MC_PP_LOGINHANDLER_H
#define MC_PP_LOGINHANDLER_H 

#include <memory>

#include "../entity/player/playerlist.hpp"
#include "../../packet/packets/p_LoginRequest.hpp"
#include "../../packet/packets/p_HandShake.hpp"
#include "../../packet/packets/packet.hpp"

class LoginHandler{
    protected:
    public:
        std::unique_ptr<DsPacket> handlepacket(std::unique_ptr<DsPacket> p, PlayerList* plist);
        DsPacket* handleHandshake(p_HandShake* pack, PlayerList* plist);
        DsPacket* handleLoginRequest(p_LoginRequest* pack);
};

#endif