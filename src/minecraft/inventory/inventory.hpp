#ifndef MC_INVENTORY_H
#define MC_INVENTORY_H

#include <array>

#include "item.hpp"

class InventoryBase{
    //TODO REFACTOR ALL and add args to functions
};

class PlayerInventory{
    private:
        std::array<Item, 27> inventory;
        std::array<Item, 9> hotbar;
    public:
        PlayerInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        Item& getItem();
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
        std::array<Item, 27> inventory;
    public:
        ChestInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        Item& getItem();
};

class LargeChestInventory{
    private:
        std::array<Item, 54> inventory;
    public:
        LargeChestInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        Item& getItem();
};

class FurnaceInventory{
    private:
        std::array<Item, 3> slots; 
    public:
        FurnaceInventory();
        Item& getItem();
};

class DispenserInventory{
    private:
        std::array<Item, 9> slots;
    public:
        DispenserInventory();
        std::size_t searchFree();
        std::size_t searchPresent();
        Item& getItem();
};

#endif