#ifndef P_INTERFACE_H
#define P_INTERFACE_H

#include <cstdint>

#include <array>
#include <vector>

#include "../../headers/defines.hpp"
#include "../packets/packet.hpp"

class PacketInterface{
    private:
        std::array<std::vector<Packet>, TP_MAX_THREADS> processedPackets;
    public:
        PacketInterface();
        void insert_packet(Packet p);
        std::vector<Packet>* get_map(uint32_t n);
        ~PacketInterface();
};

#endif