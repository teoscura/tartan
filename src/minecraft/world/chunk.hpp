#ifndef MC_CHUNK
#define MC_CHUNK

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <string>

#include "vector.hpp"

enum ChunkState{
    UNSAVED,
    SAVED,
    UNLOADED,
    LOADED,
};

class Chunk{
    public:
	    const std::size_t width = 16;
	    const std::size_t height = 128;
	    const std::size_t depth = 16;
	    const std::size_t size = 32768;

	    bool isModified;
        std::chrono::time_point<std::chrono::system_clock> last_accessed;
	    std::array<uint8_t, 32768> blocks;
	    std::array<uint8_t, 16384> metadata;
	    std::array<uint8_t, 16384> block_light;
        std::array<uint8_t, 16384> sky_light;
	    std::array<uint8_t, 256> height_map;
	    std::array<uint8_t, 256> biome_map;
        v2<int32_t> chunkcoords;

        Chunk(v2<int32_t> coords);
        v2<int32_t> getChunkCoords();
        void setChunkCoords(v2<int32_t> new_coords);
        uint8_t getMetadata(v3<int32_t> coords);
        uint8_t getSkylight(v3<int32_t> coords);
        uint8_t getBlocklight(v3<int32_t> coords);
        void setBlockId(const v3<int32_t>& coords, uint8_t b_id);
        uint8_t getHeight(v3<int32_t> coords);
        uint8_t getBlockID(v3<int32_t> coords);
        void setHeight(v3<int32_t> coords, uint8_t new_hgt);
        std::string serialize();
};

struct ChunkInstance{
    std::shared_ptr<Chunk> chunk;
    ChunkState state;
};

#endif