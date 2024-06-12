#include "playerlist.hpp"
#include "player.hpp"
#include <string>

void PlayerList::insert(Player player){
    this->list.push_back(player);
}

void PlayerList::remove(std::u16string username){
    for(auto i=0;i<this->list.size();i++){
        if(this->list[i].getUsername()==username){
            auto where = i;
            break;
        }
    }
    this->list.erase(this->list.begin());
}

bool PlayerList::isonline(std::u16string username){
    for(auto t : this->list){
        if(t.getUsername() == username){
            return true;
        }
    }
    return false;
}