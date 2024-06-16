#include "p_interface.hpp"


PacketInterface::PacketInterface(){
}

void PacketInterface::insert_packet(Packet p){
    this->processedPackets[p.info.thread_ID].push_back(std::move(p));
}

std::vector<Packet>* PacketInterface::get_map(uint32_t i){
    return &this->processedPackets.at(i);
}

PacketInterface::~PacketInterface(){
}