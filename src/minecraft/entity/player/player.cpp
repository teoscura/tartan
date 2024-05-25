#include "player.hpp"

#include <string>

uint32_t Player::getEntityId(){
    return this->ID;
}

std::u16string Player::getUsername(){
    return this->username;
}