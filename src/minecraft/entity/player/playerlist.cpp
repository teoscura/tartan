#include "playerlist.hpp"

GlobalPlayerList::GlobalPlayerList(){
    this->list = new PlayerList;
}

PlayerList* GlobalPlayerList::getGlobalPlayerList(){
    return list;
}

GlobalPlayerList::~GlobalPlayerList(){
    delete this->list;
}