#ifndef PP_ITEM_ALL
#define PP_ITEM_ALL 

#include <cstdint>
#include <string>
#include <vector>

#include "../../minecraft/inventory/inventory.hpp"
#include "../../minecraft/inventory/item.hpp"
#include "packet.hpp"

class p_WindowOpBase : public DsPacket { /* Not a protocol packet. */
    private:
        uint8_t window_id;
    public:
        p_WindowOpBase(PacketReturnInfo inf, uint8_t window_id);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_WindowOpBase() override;
};

class p_Item_OpenWindow : public p_WindowOpBase { /* 0x64 */
    private:
        uint8_t inv_type;
        std::string window_title;
        uint8_t slots;
    public:
        p_Item_OpenWindow(PacketReturnInfo inf, uint8_t window_id,
                          std::string window_title, uint8_t slots);
        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_OpenWindow() override;
};

class p_Item_CloseWindow : p_WindowOpBase { /* 0x65 */
    private:
    public:
        p_Item_CloseWindow(PacketReturnInfo inf, uint8_t window_id);
        p_Item_CloseWindow(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_CloseWindow() override;
};

class p_Item_WindowClick : p_WindowOpBase { /* 0x66 */
    private:
        int16_t slot;
        bool rightclick;
        uint16_t action_number;
        bool shift;
        int16_t item_id; //TO CHECK
        uint8_t count;
        int16_t damage;
    public:
        p_Item_WindowClick(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_WindowClick() override;
};

class p_Item_SetSlot : public p_WindowOpBase { /* 0x67 */
    private:
        int16_t slot;
        Item item;
    public:
        p_Item_SetSlot(PacketReturnInfo inf, uint8_t window_id, int16_t slot, Item item);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_SetSlot() override;
};

class p_Item_WindowItemData : public p_WindowOpBase { /* 0x68 */
    private:
        uint16_t count;
        std::vector<uint8_t> data_payload;
    public:
        p_Item_WindowItemData(PacketReturnInfo inf, uint8_t window_id, 
                              uint16_t count, std::vector<uint8_t> payload);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_WindowItemData() override;
};

class p_Item_ProgressBarUpdate : p_WindowOpBase { /* 0x69 */
    private:
        FurnaceBars progress_bar;
        uint16_t value;
    public:
        p_Item_ProgressBarUpdate(PacketReturnInfo inf, uint8_t window_id,
                                 FurnaceBars progress_bar, uint16_t value);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_ProgressBarUpdate() override;    
};

class p_Item_TransactionResponse : public p_WindowOpBase { /* 0x6A */
    private:
        int16_t action_number;
        bool accepted;
    public:
        p_Item_TransactionResponse(PacketReturnInfo inf, uint8_t window_id,
                                   int16_t action_number, bool accepted);
        p_Item_TransactionResponse(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_TransactionResponse() override;
};

class p_Item_ItemData : public DsPacket { /* 0x83 */
    private:
        int16_t item_type;
        int16_t item_id;
        uint8_t lenght;
        std::vector<uint8_t> payload;
    public:
        p_Item_ItemData(PacketReturnInfo inf, int16_t item_type,
                        int16_t item_id, uint8_t lenght);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Item_ItemData() override;
};

#endif