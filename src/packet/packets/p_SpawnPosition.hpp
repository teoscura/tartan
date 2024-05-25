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
        
        p_SpawnPosition(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_SpawnPosition() override;
};


#endif