#include "blob.hpp"
#include <memory>
#include <utility>

#include "../helpers/settingshandler.hpp"

//TODO finish this

void Blob::welcomePlayer(std::shared_ptr<Player> p){
    auto pair = std::make_pair(p->getEntityId(), std::move(p));
    this->local_players.insert(pair);
}

void Blob::goodbyePlayer(std::shared_ptr<Player> p){
    this->local_players.erase(p->getEntityId());
}

void processPacket(DsPacket* p){

}
void sendPacketToGlobal(DsPacket* p){

}

//TODO make this a promise/future thing, where all but the center chunks 
//are async and handled by a single thread that returns by the end.

Blob::Blob(){
    this->radius = atoi(SettingsHandler::getSettings()->getSettings().at("view_distance").c_str());
    for(int x=-radius+1;x<radius;x++){
        for(int z=-radius+1;z<radius;z++){
            v2<int32_t> coords = v2(x,z);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(this->terrain_generator.generateChunk(coords));
            auto tmp = std::make_pair(coords, std::move(chunk));
            this->chunks.insert(tmp);
        }
    }
}

Blob::Blob(v2<int32_t> center_chunk_coords){
    for(int x=-(this->radius)+1+center_chunk_coords.x; x<radius+center_chunk_coords.x; x++){
        for(int z=-(radius)+1+center_chunk_coords.z; z<radius+center_chunk_coords.z; z++){
            auto coords = v2(x,z);
            std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(this->terrain_generator.generateChunk(coords));
            auto tmp = std::make_pair(coords, std::move(chunk));
            this->chunks.insert(tmp);
        }
    }
}

Blob::~Blob(){

}