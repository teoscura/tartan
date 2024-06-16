#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include <string>
#include <vector>

struct LoginPlayer{
    std::u16string username;
    PacketReturnInfo inf;
    bool handshake;
};

class PlayerList{
    public:
        std::vector<Player> list;
        std::vector<LoginPlayer> login_list;
        void insert(Player playerin);
        void remove(std::u16string username);
        void cleanupLogin();
        bool isonline(std::u16string username);
        bool isLogin(std::u16string username);
        bool ishandshake(std::u16string username);
};



#endif