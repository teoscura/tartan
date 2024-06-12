#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include <string>
#include <vector>

class PlayerList{
    public:
        std::vector<Player> list;
        void insert(Player playerin);
        void remove(std::u16string username);
        bool isonline(std::u16string username);
        auto begin();
        auto end();
};



#endif