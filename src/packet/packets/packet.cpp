#include "packet.hpp"

#include <vector>

Packet::Packet(PacketReturnInfo in):
    info(in){
}

// Packet::~Packet(){
// }

Packet::Packet(std::vector<uint8_t> array, PacketReturnInfo in):
    info(in),

    bytes(array){
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



