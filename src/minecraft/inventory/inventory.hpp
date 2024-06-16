#ifndef MC_INVENTORY_H
#define MC_INVENTORY_H

#include <cstddef>
#include <vector>

#include "item.hpp"

class InventoryBase{
    //TODO REFACTOR ALL and add args to functions
    private:
        std::size_t inv_size;
        std::vector<Item> inventory;
    public:
        InventoryBase(std::size_t inv_size);
        bool boundsValid(std::size_t pointer);
        virtual std::size_t searchFree();
        virtual std::size_t searchPresent(int16_t item_id);
        Item getItem(std::size_t index);
        void editItem(std::size_t index, Item new_item);
        ~InventoryBase() = default;
};

class PlayerInventory : public InventoryBase {
    private:
        const static std::size_t size = 45;
    public:
        PlayerInventory();
        std::size_t searchFree() override;
        std::size_t searchPresent(int16_t item_id) override;
        ~PlayerInventory() = default;
};

enum FurnaceSlots{
    FURNOUTPUT,
    FURNINPUT,
    FURNFUEL,
};

enum FurnaceBars{
    FURNARROW,
    FURNFLAME,
};

class ChestInventory : public InventoryBase {
    private:
        const static std::size_t size = 27;
    public:
        ChestInventory();
        ~ChestInventory() = default;
};

class LargeChestInventory : public InventoryBase {
    private:
        const static std::size_t size = 54;
    public:
        LargeChestInventory();
        ~LargeChestInventory() = default;
};

class FurnaceInventory : public InventoryBase {
    private:
        const static std::size_t size = 3;
    public:
        FurnaceInventory();
        ~FurnaceInventory() = default;
};

class DispenserInventory : public InventoryBase {
    private:
        const static std::size_t size = 9;
    public:
        DispenserInventory();
        ~DispenserInventory() = default;
};

#endif