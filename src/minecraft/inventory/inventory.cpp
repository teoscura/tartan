#include "inventory.hpp"

#include <cstddef>
#include <cstdint>
#include <vector>

InventoryBase::InventoryBase(std::size_t inv_size) : 
    inventory(std::vector<Item>(inv_size, Item(-1,0,0))){
}

bool InventoryBase::boundsValid(std::size_t index){
    return index > this->inv_size ? false : true;
}

std::size_t InventoryBase::searchFree(){
    for(int i=0; i<this->inventory.size();i++){
        if(inventory[i].getItemData().item_id==-1){
            return i;
        }
    }
    return -1;
}

std::size_t InventoryBase::searchPresent(int16_t item_id){
    for(int i=0; i<this->inventory.size();i++){
        if(inventory[i].getItemData().item_id==item_id){
            return i;
        }
    }
    return -1;
}

Item InventoryBase::getItem(std::size_t index){
    if(!boundsValid(index)){
        return Item(-999,0,0);
    }
    return this->inventory[index];
}

void InventoryBase::editItem(std::size_t index, Item new_item){
    if(!boundsValid(index)){
        return;
    }
    this->inventory[index] = new_item;
}


