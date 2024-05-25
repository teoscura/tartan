#ifndef PP_HANDSHAKE
#define PP_HANDSHAKE


#include <cstdint>
#include <memory>
#include <string>


#include "packet.hpp"



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

#endif