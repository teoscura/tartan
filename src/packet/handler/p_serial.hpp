#ifndef P_SERIAL_H
#define P_SERIAL_H

#include "../packets/packet.hpp"
#include <memory>

class PacketSerializer{
    private:
        std::vector<Packet> out;
    public:
        PacketSerializer() = default;
        void serialize(std::shared_ptr<DsPacket> pack);
        std::vector<Packet>* getOut();
        ~PacketSerializer() = default;
};

#endif