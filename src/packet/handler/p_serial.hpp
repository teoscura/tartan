#ifndef P_SERIAL_H
#define P_SERIAL_H

#include "p_interface.hpp"
#include "../packets/packet.hpp"
#include <memory>

class PacketSerializer{
    private:
        PacketInterface* next;
    public:
        PacketSerializer();
        void serialize(std::shared_ptr<DsPacket> pack);
        PacketInterface* get_next();
        ~PacketSerializer();
};

#endif