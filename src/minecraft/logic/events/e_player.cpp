#include "e_player.hpp"

#include <cstdint>

#include "../../../packet/packets/p_Entity.hpp"
#include "event.hpp"

Event_PlayerUpdateBase::Event_PlayerUpdateBase(uint64_t destination_tick, bool on_ground) : 
    EventBase(destination_tick),
    on_ground(on_ground){
}

void Event_PlayerUpdateBase::process(ServerState* state, PacketQueue* queue){
    //TODO:
    //update onground on the player
    //send everyone entity base packet.
    PacketReturnInfo a;
    auto t = p_EntityBase(a, this->EID);
    this->queuePacket_ExPlayer(t, state, queue, this->EID);
}

Event_PlayerUpdateBase::~Event_PlayerUpdateBase(){
}

Event_PlayerUpdate_Pos::Event_PlayerUpdate_Pos(uint64_t destination_tick, bool on_ground, v3<double> new_xyz, double stance):
    Event_PlayerUpdateBase(destination_tick, on_ground),
    new_xyz(new_xyz),
    stance(stance){
}

void Event_PlayerUpdate_Pos::process(ServerState* state, PacketQueue* queue){
    //TODO  
    //then process stance, on ground and xyz, 
    //send entity pos packet to everyone
}

Event_PlayerUpdate_Pos::~Event_PlayerUpdate_Pos(){
}

Event_PlayerUpdate_Look::Event_PlayerUpdate_Look(uint64_t destination_tick, bool on_ground, v2<float> new_yp) :
    Event_PlayerUpdateBase(destination_tick, on_ground),
    new_yp(new_yp){
}

void Event_PlayerUpdate_Look::process(ServerState* state, PacketQueue* queue){
    //TODO 
    //process look and on ground check pitch.
    //send entitylook packet to everyone
}

Event_PlayerUpdate_Look::~Event_PlayerUpdate_Look(){
}

Event_PlayerUpdate_PosLook::Event_PlayerUpdate_PosLook(uint64_t destination_tick, bool on_ground, v3<double> new_xyz, double stance, v2<float> new_yp) : 
    Event_PlayerUpdate_Look(destination_tick, on_ground, new_yp), 
    Event_PlayerUpdate_Pos(destination_tick, on_ground, new_xyz, stance){
}

void Event_PlayerUpdate_PosLook::process(ServerState* state, PacketQueue* queue){
    //TODO
    //process everything checking correct pitch
    //sendEntityPosLook to everyone
}

Event_PlayerUpdate_PosLook::~Event_PlayerUpdate_PosLook(){
}





