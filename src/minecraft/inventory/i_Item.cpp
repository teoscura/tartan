#include "i_Item.hpp"
#include <cstdint>

ItemSlot::ItemSlot() :
    slot({}){
}

ItemSlot::ItemSlot(uint8_t item_id, uint8_t count, uint16_t damage):
    slot(item_id,count,damage){
}

ItemSlotData ItemSlot::getItemSlotData(){
    return this->slot;
}

void ItemSlot::modifyCount(uint8_t new_count){
    this->slot.count = new_count;
}

void ItemSlot::modifyID(uint8_t new_id){
    this->slot.item_id = new_id;
}

void ItemSlot::modifyDamage(uint16_t new_damage){
    this->slot.damage = new_damage;
}