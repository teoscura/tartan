#ifndef PP_SPAWNPOSITION
#define PP_SPAWNPOSITION

#include "packet.hpp"
#include <cstdint>
#include <memory>

//OxO6
class p_SpawnPosition : public DsPacket {
    public:
        int32_t x;
        int32_t y;
        int32_t z;
        uint8_t getID() override;
        p_SpawnPosition(std::unique_ptr<Packet> pack);
        std::unique_ptr<Packet> serialize() override; 
        ~p_SpawnPosition() override;
};


#endif