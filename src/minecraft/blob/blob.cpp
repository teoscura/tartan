#include "blob.hpp"

#include "../entity/player/playerlist.hpp"
#include <functional>
#include <memory>

Blob::Blob(std::size_t radius) : 
    WorldBlob(radius), 
    global_Players(GlobalPlayerList::getGlobalPlayerList()), 
    blob_thread(&Blob::eventLoop, this){
}

Blob::Blob(v2<int32_t> center_chunk_coords, std::size_t radius) :
    WorldBlob(center_chunk_coords, radius), 
    global_Players(GlobalPlayerList::getGlobalPlayerList()), 
    blob_thread(&Blob::eventLoop, this){

}

Blob::Blob(WorldBlob blob, PlayerList& new_local):
    WorldBlob(blob){
    for(auto t: new_local){
        this->local_players.insert(std::move(t));
    }
}

PlayerList& Blob::getLocalPlayers(){
    return std::ref(this->local_players);
}

void Blob::welcomePlayer(std::shared_ptr<Player> p){;
    this->local_players.insert(std::move(p));
}

void Blob::goodbyePlayer(std::shared_ptr<Player> p){
    this->local_players.erase(p);
}

void Blob::processPacket(std::unique_ptr<DsPacket> p){
    this->blob_packprocessor.queuePacket(std::move(p));
}