#ifndef MC_SERVERSTATE_H
#define MC_SERVERSTATE_H

#include "../entity/player/playerlist.hpp"

struct ServerState{
    PlayerList* global_plist;
    PlayerList local_plist;
    uint64_t howmany_sleeping;
};

#endif