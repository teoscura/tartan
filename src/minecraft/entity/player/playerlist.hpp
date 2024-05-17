#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include "../../../helpers/ts_set.hpp"
#include <memory>

typedef ThreadSafeSet<std::shared_ptr<Player>> PlayerList;

class GlobalPlayerList{
    private:
        static inline PlayerList *list;
    public:
        GlobalPlayerList();
        static PlayerList* getGlobalPlayerList();
        ~GlobalPlayerList();
};

#endif