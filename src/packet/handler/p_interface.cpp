#include "p_interface.hpp"

#include <memory>

PacketInterface::PacketInterface(){
}

void PacketInterface::insert_packet(std::unique_ptr<Packet> p){
    this->processedPackets[p->info.thread_ID].push_back(std::move(p));
}

std::vector<std::unique_ptr<Packet>>* PacketInterface::get_map(uint32_t i){
    return &this->processedPackets.at(i);
}

PacketInterface::~PacketInterface(){
}