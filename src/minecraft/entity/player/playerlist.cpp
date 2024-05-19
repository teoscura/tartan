#include "playerlist.hpp"

std::set<v2<double>> PlayerList::getCoordList(){
    std::set<v2<double>> cl;
    for(auto p: this->list){
        cl.insert(conv3d_2d(p->getXYZ()));
    }
    return cl;
}

GlobalPlayerList::GlobalPlayerList(){
    this->list = new PlayerList;
}

PlayerList* GlobalPlayerList::getGlobalPlayerList(){
    return list;
}

GlobalPlayerList::~GlobalPlayerList(){
    delete this->list;
}