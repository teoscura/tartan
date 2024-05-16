#include "playerlist.hpp"

GlobalPlayerList::GlobalPlayerList(){
    this->list = new PlayerMap;
}

PlayerMap* GlobalPlayerList::getGlobalPlayerList(){
    return list;
}

GlobalPlayerList::~GlobalPlayerList(){
    delete this->list;
}