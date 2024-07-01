#include "playerlist.hpp"

#include <memory>
#include <optional>
#include <string>

#include "player.hpp"

void PlayerList::insert(std::shared_ptr<Player> player){
    this->list.push_back(player);
}

void PlayerList::remove(std::u16string username){
    for(int i = list.size()-1; i>=0; i--){
        if(this->list[i]->getUsername()==username){
            list.erase(list.begin()+i);
            break;
        }
    }
}

void PlayerList::cleanupList(uint64_t current_tick){
    for(int i = list.size()-1; i>=0; i--){
        if(list.at(i)->assertStatus(S_TODESPAWN)){
            list.erase(list.begin()+i);
        }
    }
}

const std::vector<std::shared_ptr<Player>>& PlayerList::getList(){
    return this->list;
}

std::optional<std::shared_ptr<Player>> PlayerList::findPlayer(uint32_t eid){
    std::optional<uint32_t> findEID(PacketReturnInfo info);
    for(auto t : this->list){
        if(t->getEntityId()==eid){
            return t;
        }
    }
    return std::nullopt;
}

std::optional<std::shared_ptr<Player>> PlayerList::findPlayer(PacketReturnInfo inf){
    for(auto t : this->list){
        if(t->getReturnInfo().epoll_fd==inf.epoll_fd){
            return t;
        }
    }
    return std::nullopt;
}

std::optional<std::shared_ptr<Player>> PlayerList::findPlayer(std::u16string username){
    for(auto t : this->list){
        if(t->getUsername()==username){
            return t;
        }
    }
    return std::nullopt;
}

bool PlayerList::isOnline(std::u16string username){
    uint8_t state;
    if(this->list.size()==0){
        return false;
    }
    for(auto t : this->list){
        state = t->getState();
        if(t->getUsername()==username && state&L_PLAYING){
            return true;
        }
    }
    return false;
}