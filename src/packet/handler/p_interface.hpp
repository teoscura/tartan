#ifndef P_INTERFACE_H
#define P_INTERFACE_H

#include <cstdint>
#include <memory>
#include <vector>


#include "../../headers/defines.hpp"
#include "../packets/packet.hpp"

class PacketInterface{
    private:
        std::array<std::vector<std::unique_ptr<Packet>>, TP_MAX_THREADS> processedPackets;
    public:
        PacketInterface();
        void insert_packet(std::unique_ptr<Packet> p);
        std::vector<std::unique_ptr<Packet>>* get_map(uint32_t n);
        ~PacketInterface();
};

#endif