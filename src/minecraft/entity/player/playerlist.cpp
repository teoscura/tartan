#include "playerlist.hpp"

#include <memory>
#include <optional>
#include <string>

#include "player.hpp"

uint64_t LoginPlayer::howLongAgo(uint64_t current_tick){
    return current_tick-this->login_tick;
}

void PlayerList::insert(std::shared_ptr<Player> player){
    this->list.push_back(player);
}

void PlayerList::insertLogin(std::shared_ptr<LoginPlayer> logplayerin){
    this->login_list.push_back(logplayerin);
}

void PlayerList::remove(std::u16string username){
    for(int i=0;i<this->list.size();i++){
        if(this->list[i]->getUsername()==username){
            int where = i;
            break;
        }
    }
    this->list.erase(this->list.begin());
}

void PlayerList::cleanupLogin(uint64_t current_tick){
    int where;
    for(auto t: list){
        for(int j=0;j<this->login_list.size();j++){
            if(t->getUsername()==login_list[j]->username){
                where = j;
            }
        }
        login_list.erase(login_list.begin()+where);
    }
    for(int j=this->login_list.size()-1;j>=0;j--){
        if(login_list[j]->howLongAgo(current_tick)>400){
            login_list.erase(login_list.begin()+j);
        }
    }
}

const std::vector<std::shared_ptr<Player>>& PlayerList::getList(){
    return this->list;
}

std::optional<std::shared_ptr<Player>> PlayerList::findPlayer(uint32_t eid){
    for(auto t : this->list){
        if(t->getEntityId()==eid){
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

std::optional<std::shared_ptr<LoginPlayer>> PlayerList::findLogin(PacketReturnInfo inf){
    for(auto t : this->login_list){
        if(t->inf.epoll_fd == inf.epoll_fd){
            return t;
        }
    }
    return std::nullopt;
}

bool PlayerList::isOnline(std::u16string username){
    if(this->list.size()==0){
        return false;
    }
    for(auto t : this->list){
        if(t->getUsername() == username){
            return true;
        }
    }
    if(this->login_list.size()==0){
        return false;
    }
    for(auto t : this->login_list){
        if(t->username==username){
            return true;
        }
    }
    return false;
}

bool PlayerList::isLogin(std::u16string username){
    for(auto t: this->login_list){
        if(t->username==username){
            return true;
        }
    }
    return false;
}

// bool PlayerList::ishandshake(std::u16string username){
//     for(auto t: this->login_list){
//         if(t.username==username){
//             return t.handshake;
//         }
//     }
//     return false;
// }