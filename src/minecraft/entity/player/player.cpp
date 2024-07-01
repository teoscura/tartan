#include "player.hpp"

#include <cstdint>
#include <string>

Player::Player(PacketReturnInfo inf, std::u16string username, uint32_t eid) : 
    Entity(eid),
    info(PlayerConnectionInfo(inf, 0)),
    username(username){
}

bool Player::assertStatus(uint8_t status){
    if(this->state==status){
        return true;
    }
    return false;
}

bool Player::assertStatus(PlayerStates state){
    if(this->state&state){
        return true;
    }
    return false;
}

void Player::setBlob(uint8_t new_blob){
    this->info.blob = new_blob;
}

void Player::setHP(uint8_t hp){
    this->hp = hp;
}

void Player::setSleeping(bool sleeping){
    this->sleeping = sleeping;
}

void Player::setHeldSlot(uint16_t held_slot){
    this->held_slot = held_slot;
}

void Player::setHeight(double height){
    this->actual_height = height;
}

void Player::setKeepAlive(uint64_t keepalive){
    this->last_keepalive = keepalive;
}

void Player::setLoginTick(uint64_t tick){
    this->login_tick = tick;
}

void Player::setState(PlayerStates new_state){
    if(this->assertStatus(new_state)){
        return;
    }
    this->state |= new_state;
}

void Player::setRespawnPos(v3<int32_t> respawn_pos){
    this->respawn_pos = respawn_pos;
}

const PacketReturnInfo& Player::getReturnInfo(){
    return this->info.packetinfo;
}

std::u16string Player::getUsername(){
    return this->username;
}

uint8_t Player::getHP(){
    return this->hp;
}

bool Player::getSleeping(){
    return this->sleeping;
}

uint16_t Player::getHeldSlot(){
    return this->held_slot;
}

double Player::getHeight(){
    return this->actual_height;
}

uint64_t Player::getLastKeepalive(){
    return this->last_keepalive;
}

uint64_t Player::getLoginTick(){
    return this->login_tick;
}

uint8_t Player::getState(){
    return this->state;
}

v3<int32_t> Player::getRespawnPos(){
    return this->respawn_pos;
}

Player::~Player(){
    //TODO save data to database
}