#ifndef P_SERIAL_H
#define P_SERIAL_H

#include "../packets/packet.hpp"
#include <condition_variable>
#include <memory>
#include <mutex>

class PacketSerializer{
    private:
        std::mutex mut;
        std::condition_variable cond_var;
        std::vector<Packet> out;
    public:
        PacketSerializer() = default;
        void serialize(std::shared_ptr<DsPacket> pack);
        void eraseVector();
        std::vector<Packet> getPacketVector();
        ~PacketSerializer() = default;
};

#endif