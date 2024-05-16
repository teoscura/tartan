#ifndef MC_WORLD_H
#define MC_WORLD_H

#include <cstdint>
#include <map>


//This class represents the saved/loaded world, handles the loading of chunks from memory, and the saving to file
//of the various region files after the server gets called to close.
#include "vector.hpp"
#include "region.hpp"


class World{
    private:
        std::map<v2<int32_t>, Region> regions;
        int64_t seed;
};

#endif