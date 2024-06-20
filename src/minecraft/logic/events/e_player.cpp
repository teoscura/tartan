#include "e_player.hpp"

#include <cstdint>

#include "../../../packet/packets/p_Entity.hpp"
#include "../../../helpers/loggerhandler.hpp"
#include "event.hpp"

Event_PlayerUpdateBase::Event_PlayerUpdateBase(uint64_t destination_tick, bool on_ground) : 
    EventBase(destination_tick),
    on_ground(on_ground){
}

void Event_PlayerUpdateBase::process(ServerState* state, PacketQueue* queue){
    std::optional<Player*> player = state->global_plist->findPlayer(this->EID);
    if(!player.has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "EID {} is not a player/is present!");
        return;
    }
    player.value()->updateOnGround(this->on_ground);
    auto t =  new p_EntityBase(PacketReturnInfo(), this->EID);
    this->queuePacket_ExPlayer(std::shared_ptr<DsPacket>(t), state, queue, this->EID);
    //FIXME remember to validate changes.
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
    //FIXME remember to validate changes.
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

Event_PlayerUpdate_PosLook::Event_PlayerUpdate_PosLook(uint64_t destination_tick, bool on_ground, v3<double> new_xyz, double stance, v2<float> new_yp) : 
    Event_PlayerUpdate_Look(destination_tick, on_ground, new_yp), 
    Event_PlayerUpdate_Pos(destination_tick, on_ground, new_xyz, stance){
}

void Event_PlayerUpdate_PosLook::process(ServerState* state, PacketQueue* queue){
    //TODO
    //process everything checking correct pitch
    //sendEntityPosLook to everyone
}






