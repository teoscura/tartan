#ifndef P_DESERIAL_H
#define P_DESERIAL_H

#include "../../helpers/logger.hpp"
#include "../packets/packet.hpp"
#include "queue.hpp"


class PacketDeserializer{
    private:
        ThreadSafeQueue<DsPacket> queue;
        Logger* lg;
    public:
        PacketDeserializer();
        void addPacket(Packet p);
        bool isEmpty();
        std::optional<DsPacket> retrievePacket();
        ~PacketDeserializer();
};

#endif