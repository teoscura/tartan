#ifndef PP_LOGINREQUEST
#define PP_LOGINREQUEST

#include "packet.hpp"

#include <cstdint>
#include <memory>
#include <string>

class p_LoginRequest : public DsPacket {
    public:
        int32_t protocol;
        uint16_t username_len;
        std::u16string username;
        int64_t seed;
        uint8_t dimension;
    
        p_LoginRequest() = default;
        uint8_t getID() override;
        p_LoginRequest(std::unique_ptr<Packet> pack);
        std::unique_ptr<Packet> serialize() override; 
        ~p_LoginRequest() override;
};

#endif