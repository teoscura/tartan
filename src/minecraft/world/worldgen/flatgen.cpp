#include "flatgen.hpp"
#include <memory>


FlatlandGenerator::FlatlandGenerator(){
    this->spawnpoint = v3(0, 10, 0);
}

v3<int32_t> FlatlandGenerator::getSpawnPoint(){
    return this->spawnpoint;
}

std::unique_ptr<Chunk> FlatlandGenerator::generateChunk(v2<int32_t> coords){
    std::unique_ptr<Chunk> newChunk = std::make_unique<Chunk>(coords);
    int y=0;
    while (y < 10) {
		for (int x = 0; x < 16; x++) {
			for (int z= 0; z < 16; z++) {
				if (y < 9) {
					newChunk->setBlockId(v3(x, y, z), 0x03);
				} else {
					newChunk->setBlockId(v3(x, y, z), 0x02);
				}
			}
		}
		y++;
	}
    return newChunk;
}