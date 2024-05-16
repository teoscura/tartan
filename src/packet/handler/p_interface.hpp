#ifndef P_INTERFACE_H
#define P_INTERFACE_H

#include <cstdint>
#include <map>
#include <memory>
#include <queue>

#include "../packets/packet.hpp"

class PacketInterface{
    private:
        std::map<uint32_t, std::queue<std::unique_ptr<Packet>>*> processedPackets;
    public:
        PacketInterface();
        void insert_packet(std::unique_ptr<Packet>);
        std::queue<std::unique_ptr<Packet>>* get_map(uint32_t n);
        ~PacketInterface();
};

#endif