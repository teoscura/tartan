#ifndef MC_ITEM_H
#define MC_ITEM_H

#include <cstdint>

struct ItemSlotData{
    int16_t item_id;
    uint8_t count;
    uint16_t damage;
};

class ItemSlot{
    private:
        ItemSlotData slot;
    public: 
        ItemSlot();
        ItemSlot(uint8_t item_id, uint8_t count, uint16_t damage);
        ItemSlotData getItemSlotData();
        void modifyID(uint8_t new_id);
        void modifyCount(uint8_t new_count);
        void modifyDamage(uint16_t new_damage);
};

#endif
