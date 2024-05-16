#include "p_interface.hpp"
#include "../../headers/defines.hpp"
#include <memory>

PacketInterface::PacketInterface(){
    std::queue<std::unique_ptr<Packet>>* ptr;
    for(int i=0; i<TP_MAX_THREADS;i++){
        ptr = new std::queue<std::unique_ptr<Packet>>();
        this->processedPackets.insert(std::make_pair(i, ptr));
    }
}

void PacketInterface::insert_packet(std::unique_ptr<Packet> p){
    this->processedPackets.at(p->info.thread_ID)->push(std::move(p));
}

std::queue<std::unique_ptr<Packet>>* PacketInterface::get_map(uint32_t i){
    return this->processedPackets.at(i);
}

PacketInterface::~PacketInterface(){
    for(auto i : this->processedPackets){
        delete i.second;
    }
}