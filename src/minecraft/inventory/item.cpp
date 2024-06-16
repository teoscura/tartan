#include "item.hpp"
#include <cstdint>

Item::Item() :
    slot({}){
}

Item::Item(int16_t item_id, uint8_t count, uint16_t damage):
    slot(item_id,count,damage){
}

ItemData Item::getItemData(){
    return this->slot;
}

void Item::modifyCount(uint8_t new_count){
    this->slot.count = new_count;
}

void Item::modifyID(uint8_t new_id){
    this->slot.item_id = new_id;
}

void Item::modifyDamage(uint16_t new_damage){
    this->slot.damage = new_damage;
}