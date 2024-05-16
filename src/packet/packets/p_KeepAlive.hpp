#ifndef PP_KEEPALIVE
#define PP_KEEPALIVE

#include "packet.hpp"

#include <memory>

class p_KeepAlive: public DsPacket{
    public:
        p_KeepAlive(std::unique_ptr<Packet> pack);
        uint8_t getID() override;
};

#endif