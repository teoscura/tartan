#ifndef PP_LOGIN_ALL
#define PP_LOGIN_ALL

#include "packet.hpp"

class p_LoginRequest : public DsPacket {
    public:
        int32_t protocol;
        uint16_t username_len;
        std::u16string username;
        int64_t seed;
        uint8_t dimension;
    
        p_LoginRequest(PacketReturnInfo inf);
        p_LoginRequest(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_LoginRequest() override;
};

class p_HandShake : public DsPacket{
    public:
        uint16_t username_len;
        std::u16string username;

        
        p_HandShake(std::unique_ptr<Packet> pack);
        p_HandShake(std::u16string resp, uint16_t len);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_HandShake() override;
};

class p_Kick : public DsPacket{
    public:
        uint16_t reason_len;
        std::u16string reason;

        p_Kick(std::unique_ptr<Packet> pack);
        p_Kick(std::u16string resp, uint16_t len);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Kick() override;
};

#endif