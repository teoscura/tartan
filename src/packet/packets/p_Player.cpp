#include "p_Player.hpp"
#include "packet.hpp"
#include <memory>

p_PlayerBase::p_PlayerBase(PacketReturnInfo inf, bool on_ground) :
    on_ground(on_ground){
    this->setInfo(inf);
}

p_PlayerBase::p_PlayerBase(std::unique_ptr<Packet> pack){
    this->setInfo(pack->info);
    this->on_ground = pack->bytes[1];
}

uint8_t p_PlayerBase::getID(){
    return 0x0A;
}

PacketCategories p_PlayerBase::getType(){
    return PLAYER;
}

std::unique_ptr<Packet> p_PlayerBase::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    result->bytes = new uint8_t[2];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    result->bytes[1] = this->on_ground;
    result->size = 2;
    return result;
}

p_PlayerBase::~p_PlayerBase(){
}

p_Player_Pos::p_Player_Pos(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance) : 
    p_PlayerBase(inf, on_ground),
    xyz(xyz),
    stance(stance){
}
//TODO continue this