#ifndef MC_SERVERSTATE_H
#define MC_SERVERSTATE_H

#include "../entity/player/playerlist.hpp"
#include "servertimeutil.hpp"

struct ServerState{
    TimeUtil time;
    PlayerList* global_plist;
    PlayerList local_plist;
    uint64_t howmany_sleeping;
};

#endif