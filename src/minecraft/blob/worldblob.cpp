#include "worldblob.hpp"

#include <cstddef>
#include <memory>
#include <utility>

//TODO make this a promise/future thing, where all but the center chunks 
//are async and handled by a single thread that returns by the end.


void WorldBlob::genChunk(v2<int32_t> chunk_coords){
    auto tmp = this->terrain_generator.generateChunk(chunk_coords);
    auto pair = std::make_pair(chunk_coords,std::move(tmp));
    this->chunks.insert(std::move(pair));
}

//consumes worldblob
std::map<v2<int32_t>, std::unique_ptr<Chunk>> WorldBlob::moveChunks(){
    return std::move(this->chunks);
}

WorldBlob::WorldBlob(std::size_t radius){
    for(int x=-radius+1;x<radius;x++){
        for(int z=-radius+1;z<radius;z++){
            v2<int32_t> coords = v2(x,z);
            std::unique_ptr<Chunk> chunk = this->terrain_generator.generateChunk(coords);
            auto tmp = std::make_pair(coords, std::move(chunk));
            this->chunks.insert(std::move(tmp));
        }
    }
}

WorldBlob::WorldBlob(std::map<v2<int32_t>, std::unique_ptr<Chunk>> chunks, std::size_t radius):
    chunks(chunks),
    radius(radius){
}

WorldBlob::WorldBlob(v2<int32_t> center_chunk_coords, std::size_t radius){
    for(int x=-(this->radius)+1+center_chunk_coords.x; x<radius+center_chunk_coords.x; x++){
        for(int z=-(radius)+1+center_chunk_coords.z; z<radius+center_chunk_coords.z; z++){
            auto coords = v2(x,z);
            std::unique_ptr<Chunk> chunk = this->terrain_generator.generateChunk(coords);
            auto tmp = std::make_pair(coords, std::move(chunk));
            this->chunks.insert(std::move(tmp));
        }
    }
}

WorldBlob::~WorldBlob(){

}