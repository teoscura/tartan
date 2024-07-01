#ifndef P_DESERIAL_H
#define P_DESERIAL_H

#include "../../helpers/logger.hpp"
#include "../packets/packet.hpp"
#include "queue.hpp"

class PacketDeserializer{
    private:
        PacketQueue* deserialized;
        Logger* lg;
    public:
        PacketDeserializer(PacketQueue* deserialized);
        void addPacket(Packet p);
        ~PacketDeserializer();
};

#endif