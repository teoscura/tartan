#include "player.hpp"

#include <cstdint>
#include <string>

Player::Player(PacketReturnInfo inf, std::u16string username, uint32_t eid) : 
    Entity(eid),
    info(PlayerConnectionInfo(inf, 0)),
    username(username){
}

void Player::updateBlob(uint8_t new_blob){
    this->info.blob = new_blob;
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