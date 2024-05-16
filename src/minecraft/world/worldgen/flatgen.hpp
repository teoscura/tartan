#ifndef MC_FLATGEN_H
#define MC_FLATGEN_H

#include "../vector.hpp"
#include "../chunk.hpp"
#include <memory>

class FlatlandGenerator{
    private:
        v3<int32_t> spawnpoint;
    public:
		FlatlandGenerator();
		v3<int32_t> getSpawnPoint();
		std::shared_ptr<Chunk> generateChunk(v2<int32_t> coords);
};

#endif