#ifndef P_SERIAL_H
#define P_SERIAL_H

#include "p_interface.hpp"
#include "../packets/packet.hpp"

class PacketSerializer{
    private:
        PacketInterface* next;
    public:
        PacketSerializer();
        void serialize(DsPacket pack);
        PacketInterface* get_next();
        ~PacketSerializer();
};

#endif