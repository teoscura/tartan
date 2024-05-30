#ifndef MC_SERVERSTATE_H
#define MC_SERVERSTATE_H

#include "../entity/player/playerlist.hpp"

struct ServerState{
    PlayerList* global_plist;
    //UNUSED FOR NOW
    PlayerList local_plist; 
    //WILL IMPLEMENT
    // EntityList local_elist;
};

#endif