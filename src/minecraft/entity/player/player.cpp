#include "player.hpp"

#include <cstdint>
#include <string>

void Player::updateBlob(uint8_t new_blob){
    this->info.blob = new_blob;
}

void Player::updatePosLook(v3<double> new_xyz, v2<float> new_yp){
    this->xyz = new_xyz;
    this->yp = new_yp;
}

uint32_t Player::getEntityId(){
    return this->ID;
}

std::u16string Player::getUsername(){
    return this->username;
}

const PacketReturnInfo& Player::getReturnInfo(){
    return this->info.packetinfo;
}

Player::~Player(){
    //TODO save data to database
}