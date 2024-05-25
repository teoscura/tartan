#include "playerlist.hpp"
#include <memory>
#include <string>

void PlayerList::insert(std::shared_ptr<Player> playerin){
    this->list.insert(std::move(playerin));
}

void PlayerList::remove(std::shared_ptr<Player> playerin){
    this->list.erase(std::move(playerin));
}

bool PlayerList::containsname(std::u16string username){
    for(auto t : this->list){
        if(t->getUsername() == username){
            return true;
        }
    }
    return false;
}