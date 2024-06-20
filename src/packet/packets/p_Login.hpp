#ifndef PP_LOGIN_ALL
#define PP_LOGIN_ALL

#include <string>

#include "packet.hpp"


class p_LoginRequest : public DsPacket { /* 0x01 */
    public:
        int32_t protocol;
        uint16_t username_len;
        std::u16string username;
        int64_t seed;
        uint8_t dimension;
    
        p_LoginRequest(PacketReturnInfo inf);
        p_LoginRequest(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_LoginRequest() override = default;
};

class p_HandShake : public DsPacket{ /* 0x02 */
    public:
        uint16_t username_len;
        std::u16string username;

        
        p_HandShake(Packet pack);
        p_HandShake(std::u16string resp, PacketReturnInfo inf);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_HandShake() override = default;
};

class p_Kick : public DsPacket{ /* 0xFF */
    public:
        uint16_t reason_len;
        std::u16string reason;

        p_Kick(Packet pack);
        p_Kick(PacketReturnInfo inf, std::u16string resp, uint16_t len);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Kick() override = default;
};

#endif