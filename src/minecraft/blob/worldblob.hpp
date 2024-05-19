#ifndef MC_BLOB_WORLD_H
#define MC_BLOB_WORLD_H

#include <cstddef>
#include <map>
#include <memory>


#include "../world/worldgen/flatgen.hpp"
#include "../world/chunk.hpp"

class WorldBlob{
    protected:
        std::map<v2<int32_t>, std::unique_ptr<Chunk>> chunks;
        FlatlandGenerator terrain_generator;
        std::size_t radius;
    public:
        void genChunk(v2<int32_t> chunk_coords);
        std::map<v2<int32_t>, std::unique_ptr<Chunk>> moveChunks();
        WorldBlob(std::size_t radius);
        WorldBlob(std::map<v2<int32_t>, std::unique_ptr<Chunk>> chunks, std::size_t radius);
        WorldBlob(v2<int32_t> center_chunk_coords, std::size_t radius);
        ~WorldBlob();
};

#endif