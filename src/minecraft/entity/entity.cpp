#include "entity.hpp"

v3<double> Entity::getXYZ(){
    return this->xyz;
}

uint32_t Entity::getEntityId(){
    return this->ID;
}