#include "packet.hpp"

#include <vector>

//FIXME remember to update this
std::vector<uint8_t> implemented_pps = { 0x00, 0x01, 0x02, 0x06, 0xFF };

bool isImplemented(uint8_t id){
    for(auto n : implemented_pps){
        if(n==id){
            return true;
        }
    }
    return false;
}

Packet::Packet(){
    this->info.epoll_fd = 0;
    this->info.thread_ID = 0;

}

Packet::Packet(PacketReturnInfo in):
    info(in){
}

Packet::Packet(std::vector<uint8_t> array, PacketReturnInfo in):
    info(in),

    bytes(array){
}

Packet::~Packet(){
}

DsPacket::DsPacket(){
}

DsPacket::DsPacket(PacketReturnInfo inf):
    info(inf){
}

uint8_t DsPacket::getID(){
    return 0x00;
}

PacketCategories DsPacket::getType(){
    return NOT_IMPLEMENTED;
}

PacketReturnInfo DsPacket::getInfo(){
    return this->info;
}

void DsPacket::setInfo(PacketReturnInfo inf){
    this->info = inf;
}

Packet DsPacket::serialize(){
    return Packet(std::vector<uint8_t>(),this->getInfo());
}



