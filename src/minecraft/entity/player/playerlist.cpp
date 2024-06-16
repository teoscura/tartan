#include "playerlist.hpp"
#include "player.hpp"
#include <string>

void PlayerList::insert(Player player){
    this->list.push_back(player);
}

void PlayerList::remove(std::u16string username){
    for(int i=0;i<this->list.size();i++){
        if(this->list[i].getUsername()==username){
            int where = i;
            break;
        }
    }
    this->list.erase(this->list.begin());
}

void PlayerList::cleanupLogin(){
    int where;
    for(auto t: list){
        for(int j=0;j<this->login_list.size();j++){
            if(t.getUsername()==login_list[j].username){
                where = j;
            }
        }
        login_list.erase(login_list.begin()+where);
    }
}

bool PlayerList::isonline(std::u16string username){
    for(auto t : this->list){
        if(t.getUsername() == username){
            return true;
        }
    }
    for(auto t: this->login_list){
        if(t.username==username){
            return true;
        }
    }
    return false;
}

bool PlayerList::isLogin(std::u16string username){
    for(auto t: this->login_list){
        if(t.username==username){
            return true;
        }
    }
    return false;
}

bool PlayerList::ishandshake(std::u16string username){
    for(auto t: this->login_list){
        if(t.username==username){
            return t.handshake;
        }
    }
    return false;
}