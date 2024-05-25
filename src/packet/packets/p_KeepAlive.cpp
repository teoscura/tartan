#include "p_KeepAlive.hpp"

p_KeepAlive::p_KeepAlive(std::unique_ptr<Packet> pack){
    this->info = pack->info;
}

uint8_t p_KeepAlive::getID(){
    return 0x00;
}

PacketCategories p_KeepAlive::getType(){
    return PLAYER;
}
