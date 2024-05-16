#ifndef P_DESERIAL_H
#define P_DESERIAL_H

#include "../../helpers/logger.hpp"
#include "../packets/packet.hpp"
#include "queue.hpp"
#include <memory>

class PacketDeserializer{
    private:
        ThreadSafeQueue<std::unique_ptr<DsPacket>> queue;
        Logger* lg;
    public:
        PacketDeserializer();
        void addPacket(std::unique_ptr<Packet> p);
        ~PacketDeserializer();
};

#endif