#ifndef MC_PP_LOGIC_H
#define MC_PP_LOGIC_H

#include <cstdint>

enum PacketCategories{
    NOT_IMPLEMENTED,
    PLAYER,
    ENTITY,
    CHUNK_BLOCK,
    MISC,
};

PacketCategories whatCategory(uint8_t ID);


#endif