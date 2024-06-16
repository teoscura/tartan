#ifndef PP_MISC_ALL
#define PP_MISC_ALL

#include "packet.hpp"

#include <cstdint>
#include <string>

//TODO packet constructor for the c->s ones

class p_ChatMessage : public DsPacket { /* 0x03 */
    private:
        std::u16string message;
        uint16_t message_len;
    public:
        p_ChatMessage(PacketReturnInfo inf, std::u16string message);
        p_ChatMessage(Packet pack);
        //TODO packet constructor

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_ChatMessage() override;
};  

class p_TimeUpdate : public DsPacket { /* 0x04*/
    private:
        uint64_t time;
    public:
        p_TimeUpdate(PacketReturnInfo inf, uint64_t time);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_TimeUpdate() override;
};

class p_NewState : public DsPacket { /* 0x46 */
    private:
        uint8_t reason;
    public:
        p_NewState(PacketReturnInfo inf, uint8_t reason);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_NewState() override;
};

class p_StatIncrease : public DsPacket { /* 0xC8 */
    private:
        int32_t stat_id;
        int8_t amount;
    public:
        p_StatIncrease(PacketReturnInfo inf, int32_t stat_id, int8_t amount);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_StatIncrease() override;
};

#endif