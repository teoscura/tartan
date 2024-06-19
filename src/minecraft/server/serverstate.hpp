#ifndef MC_SERVERSTATE_H
#define MC_SERVERSTATE_H

#include "../entity/player/playerlist.hpp"
#include "../entity/entitylist.hpp"
#include "servertimeutil.hpp"

struct ServerState{
    TimeUtil time;
    PlayerList* global_plist;
    EntityList* global_elist;
    PlayerList local_plist;
    EntityList local_elist;
    uint64_t howmany_sleeping;
};

#endif