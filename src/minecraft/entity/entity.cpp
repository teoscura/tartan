#include "entity.hpp"

void Entity::updateOnGround(bool new_on_ground){
    this->on_ground = new_on_ground;
}

v3<double> Entity::getXYZ(){
    return this->xyz;
}

uint32_t Entity::getEntityId(){
    return this->ID;
}