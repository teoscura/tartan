#ifndef MC_PP_LOGINHANDLER_H
#define MC_PP_LOGINHANDLER_H 

#include <memory>

#include "../../packet/packets/packet.hpp"
#include "../entity/player/playerlist.hpp"

class LoginHandler{
    protected:
    public:
        std::unique_ptr<DsPacket> handlepacket(std::unique_ptr<DsPacket> p, PlayerList* plist);
        std::unique_ptr<DsPacket> handleLoginRequest(std::unique_ptr<DsPacket> pack);
        std::unique_ptr<DsPacket> handleHandshake(std::unique_ptr<DsPacket>, PlayerList* plist);
};

#endif