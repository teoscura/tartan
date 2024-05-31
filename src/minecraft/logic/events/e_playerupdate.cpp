#include "e_playerupdate.hpp"
#include "event.hpp"

Event_PlayerUpdateBase::Event_PlayerUpdateBase(uint64_t destination_tick, bool on_ground) : 
    EventBase(destination_tick),
    on_ground(on_ground){
}

void Event_PlayerUpdateBase::process(ServerState* state){
    //TODO:
    //update onground on the player
    //send everyone entity base packet.
}

Event_PlayerUpdateBase::~Event_PlayerUpdateBase(){
}
