#include "blob.hpp"

#include "../entity/player/playerlist.hpp"

Blob::Blob(std::size_t radius) :  WorldBlob(radius){
    this->global_Players = GlobalPlayerList::getGlobalPlayerList();
}



void Blob::welcomePlayer(std::shared_ptr<Player> p){;
    this->local_players.insert(std::move(p));
}

void Blob::goodbyePlayer(std::shared_ptr<Player> p){
    this->local_players.erase(p);
}