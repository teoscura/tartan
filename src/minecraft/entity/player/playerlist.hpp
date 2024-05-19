#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include "../../../helpers/ts_set.hpp"
#include <memory>


class PlayerList{
    public:
        ThreadSafeSet<std::shared_ptr<Player>> list;
        std::set<v2<double>> getCoordList();
};

class GlobalPlayerList{
    private:
        static inline PlayerList *list;
    public:
        GlobalPlayerList();
        static PlayerList* getGlobalPlayerList();
        ~GlobalPlayerList();
};

#endif