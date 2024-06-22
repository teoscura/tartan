#include "entity.hpp"

DeadEntity::DeadEntity(uint32_t eid) : 
    EID(eid){
}

void DeadEntity::despawn(){
    this->despawned = true;
}

bool DeadEntity::isDespawned(){
    return this->despawned;
}

uint32_t DeadEntity::getEntityId(){
    return this->EID;
}

Entity::Entity(uint32_t eid) :
    DeadEntity(eid){    
}

void Entity::setOnGround(bool new_on_ground){
    this->on_ground = new_on_ground;
}

void Entity::setPosLook(v3<double> new_xyz, v2<float> new_yp){
    this->xyz = new_xyz;
    this->yp = new_yp;
}

bool Entity::getOnGround(){
    return this->on_ground;
}

v3<double> Entity::getXYZ(){
    return this->xyz;
}

v2<float> Entity::getYP(){
    return this->yp;
}