#ifndef MC_SERVERSTATE_H
#define MC_SERVERSTATE_H

#include "../entity/player/playerlist.hpp"

struct ServerState{
    PlayerList* global_plist;
    //UNUSED FOR NOW
    PlayerList local_plist;
    uint64_t howmany_sleeping;
    //WILL IMPLEMENT
    // EntityList local_elist;
};

#endif