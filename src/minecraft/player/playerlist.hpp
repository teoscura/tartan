#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include "../../helpers/map.hpp"
#include <memory>

typedef ThreadSafeMap<int32_t, std::shared_ptr<Player>> PlayerMap;

class GlobalPlayerList{
    private:
        static inline PlayerMap *list;
    public:
        GlobalPlayerList();
        static PlayerMap* getGlobalPlayerList();
        ~GlobalPlayerList();
};

#endif