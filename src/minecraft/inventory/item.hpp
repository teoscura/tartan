#ifndef MC_ITEM_H
#define MC_ITEM_H

#include <cstdint>

struct ItemData{
    int16_t item_id;
    uint8_t count;
    uint16_t damage;
};

class Item{
    private:
        ItemData slot;
    public: 
        Item();
        Item(uint8_t item_id, uint8_t count, uint16_t damage);
        ItemData getItemData();
        void modifyID(uint8_t new_id);
        void modifyCount(uint8_t new_count);
        void modifyDamage(uint16_t new_damage);
};

#endif
