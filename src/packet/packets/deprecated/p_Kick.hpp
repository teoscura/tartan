#ifndef PP_KICK
#define PP_KICK

#include <memory>
#include <string>

#include "packet.hpp"

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