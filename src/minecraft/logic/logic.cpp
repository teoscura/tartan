#include "logic.hpp"

#include <set>

PacketCategories whatCategory(uint8_t ID){
    std::set<uint8_t> PlayerPackets = {};
    std::set<uint8_t> EntityPackets = {};
    std::set<uint8_t> ChunkBlockPackets = {};
    std::set<uint8_t> MiscPackets = {};
    if (PlayerPackets.contains(ID)){
        return PLAYER;
    } else if (EntityPackets.contains(ID)){
        return ENTITY;
    } else if (ChunkBlockPackets.contains(ID)){
        return CHUNK_BLOCK;
    } else if (MiscPackets.contains(ID)){
        return MISC;
    } else {
        return NOT_IMPLEMENTED;
    }
}