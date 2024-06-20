#ifndef P_DESERIAL_H
#define P_DESERIAL_H

#include "../../helpers/logger.hpp"
#include "../packets/packet.hpp"
#include "queue.hpp"
#include <memory>


class PacketDeserializer{
    private:
        PacketQueue queue;
        Logger* lg;
    public:
        PacketDeserializer();
        void addPacket(Packet p);
        bool isEmpty();
        std::optional<std::shared_ptr<DsPacket>> retrievePacket();
        ~PacketDeserializer();
};

#endif