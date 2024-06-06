#ifndef MC_INVENTORY_H
#define MC_INVENTORY_H

#include <array>

#include "item.hpp"

class InventoryBase{
    //TODO REFACTOR ALL
};

class PlayerInventory{
    private:
        std::array<ItemSlot, 27> inventory;
        std::array<ItemSlot, 9> hotbar;
    public:
        PlayerInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        ItemSlot& getSlot();
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

class ChestInventory{
    private:
        std::array<ItemSlot, 27> inventory;
    public:
        ChestInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        ItemSlot& getSlot();
};

class LargeChestInventory{
    private:
        std::array<ItemSlot, 54> inventory;
    public:
        LargeChestInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        ItemSlot& getSlot();
};

class FurnaceInventory{
    private:
        std::array<ItemSlot, 3> slots; 
    public:
        FurnaceInventory();
        ItemSlot& getSlot();
};

class DispenserInventory{
    private:
        std::array<ItemSlot, 9> slots;
    public:
        DispenserInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        ItemSlot& getSlot();
};

#endif