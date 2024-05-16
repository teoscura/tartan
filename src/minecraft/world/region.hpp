#ifndef MC_REGION_H
#define MC_REGION_H

#include <array>
#include <memory>

#include "chunk.hpp"
#include "vector.hpp"


class Region{
    private:
        std::array<std::shared_ptr<Chunk>, 1024> chunks;
    public:
        v2<int32_t> regioncoords;
};

#endif