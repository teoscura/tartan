#include "chunk.hpp"
#include <chrono>
#include <cstdint>
#include <cstring>

Chunk::Chunk(v2<int32_t> coords){
    this->chunkcoords.x = coords.x*this->width;
    this->chunkcoords.z = coords.z*this->depth;
    memset(this->blocks.data(), 0, this->blocks.size());
    memset(this->metadata.data(), 0, this->metadata.size());
    memset(this->block_light.data(), 0, this->block_light.size());
    memset(this->height_map.data(), 0, this->height_map.size());
    memset(this->sky_light.data(), 0, this->sky_light.size());
}

v2<int32_t> Chunk::getChunkCoords(){
    return v2<int32_t>(this->chunkcoords.x, this->chunkcoords.z);
}

void Chunk::setChunkCoords(v2<int32_t> new_coords){
    this->chunkcoords.x = new_coords.x;
    this->chunkcoords.z = new_coords.z;
}

uint8_t Chunk::getMetadata(v3<int32_t> coords){
    this->last_accessed = std::chrono::system_clock::now();
    size_t index = coords.y + (coords.z*this->height) + (coords.x*this->height*this->width);
    return this->metadata[index];
}
uint8_t Chunk::getSkylight(v3<int32_t> coords){
    this->last_accessed = std::chrono::system_clock::now();
    size_t index = coords.y + (coords.z*this->height) + (coords.x*this->height*this->width);
    return this->sky_light[index];
}

uint8_t Chunk::getBlocklight(v3<int32_t> coords){
    this->last_accessed = std::chrono::system_clock::now();
    size_t index = coords.y + (coords.z*this->height) + (coords.x*this->height*this->width);
    return this->block_light[index];
}

void Chunk::setBlockId(const v3<int32_t>& coords, uint8_t b_id){
	v3 cc = coords;
	this->last_accessed = std::chrono::system_clock::now();
    this->isModified = true;
	size_t index = coords.y + (coords.z*this->height) + (coords.x*this->height*this->width);
    this->blocks[index] = b_id;
	uint8_t old_height = this->getHeight(coords);
	if(b_id == 0x00){
		if(old_height<coords.y){
			while (cc.y > 0) {
					cc.y--;
					if (getBlockID(coords) != 0x00) {
						this->setHeight(coords, coords.y);
					}
				}
		}
	}
	else if (old_height < coords.y){
		this->setHeight(coords, coords.y);
	}
}

uint8_t Chunk::getHeight(v3<int32_t> coords){
	this->last_accessed = std::chrono::system_clock::now();
	return this->height_map[coords.z*this->depth + coords.x];
}

uint8_t Chunk::getBlockID(v3<int32_t> coords){
	this->last_accessed = std::chrono::system_clock::now();
	std::size_t index = coords.y + (coords.z*this->height) + (coords.x*this->height*this->width);
	return this->blocks[index];
}

void Chunk::setHeight(v3<int32_t> coords, uint8_t new_hgt){
	this->last_accessed = std::chrono::system_clock::now();
	this->isModified = true;
	this->height_map[coords.z*this->depth + coords.x] = new_hgt;
}

std::string Chunk::serialize(){
	std::string str;
		for (int i = 0; i < this->size; i++) {
			str.push_back(this->blocks[i]);
		}
		for (int i = 0; i < this->size; i++){
			str.push_back(0x00);
		}
		for (int i = 0; i < this->size; i++){
			str.push_back(0xFF);
		}
		for (int i = 0; i < this->size; i++){
			str.push_back(0xFF);
		}
		return str;
}

Chunk::~Chunk(){
	//TODO WRITE TO DATABASE or FILE.
}