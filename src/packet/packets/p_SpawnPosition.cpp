#include "p_SpawnPosition.hpp"

#include <iostream>
#include <memory>

#include "../../helpers/loggerhandler.hpp"
#include "../../util/byteops.hpp"
#include "packet.hpp"



p_SpawnPosition::p_SpawnPosition(PacketReturnInfo inf, v3<int32_t> coords){
    this->setInfo(inf);
    this->x = coords.x;
    this->y = coords.y;
    this->z = coords.z;
}

uint8_t p_SpawnPosition::getID(){
    return 0x06;
}

PacketCategories p_SpawnPosition::getType(){
    return PLAYER;
}


std::unique_ptr<Packet> p_SpawnPosition::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    uint16_t size = 13;
    result->size = size;
    result->bytes = new uint8_t[size];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    writeBytes_from32bit(result->bytes+1, this->x);
    writeBytes_from32bit(result->bytes+5, this->y);
    writeBytes_from32bit(result->bytes+9, this->z);
    return result;
}

p_SpawnPosition::~p_SpawnPosition(){}