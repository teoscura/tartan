#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include "../../../helpers/ts_set.hpp"
#include <memory>
#include <string>


class PlayerList{
    private:
        std::set<std::shared_ptr<Player>> list;
    public:
        void insert(std::shared_ptr<Player> playerin);
        void remove(std::shared_ptr<Player> playerin);
        bool containsname(std::u16string username);
};



#endif