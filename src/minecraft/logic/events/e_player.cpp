#include "e_player.hpp"

#include <cstdint>
#include <memory>

#include "../../../packet/packets/p_Entity.hpp"
#include "../../../packet/packets/p_Login.hpp"
#include "../../../packet/packets/p_Player.hpp"
#include "../../../helpers/loggerhandler.hpp"
#include "event.hpp"

//FIXME remember to validate changes.

Event_PlayerUpdateBase::Event_PlayerUpdateBase(uint64_t destination_tick, uint32_t EID, bool on_ground) : 
    EventBase(destination_tick),
    EID(EID),
    on_ground(on_ground){
}

void Event_PlayerUpdateBase::process(ServerState* state, PacketSerializer* serial){
    std::optional<std::shared_ptr<Player>> player = state->global_plist->findPlayer(this->EID);
    if(!player.has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "EID {} is not a player/is present!", this->EID);
        return;
    }
    player.value()->setOnGround(this->on_ground);
    auto t =  new p_EntityBase(PacketReturnInfo(), this->EID);
    this->queuePacket_ExPlayer(std::shared_ptr<p_EntityBase>(t), state, serial, this->EID);
}

Event_PlayerUpdate_Pos::Event_PlayerUpdate_Pos(uint64_t destination_tick, uint32_t EID, bool on_ground, v3<double> new_xyz, double stance):
    Event_PlayerUpdateBase(destination_tick, EID, on_ground),
    new_xyz(new_xyz),
    stance(stance){
}

void Event_PlayerUpdate_Pos::process(ServerState* state, PacketSerializer* serial){
    std::u16string reason;
    std::optional<std::shared_ptr<Player>> player = state->global_plist->findPlayer(this->EID);
    if(!player.has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "EID {} is not a player/is present!", this->EID);
        return;
    }
    auto xyz = player.value()->getXYZ();
    v3<double> diff(xyz.x-this->new_xyz.x,xyz.y-this->new_xyz.y,xyz.z-this->new_xyz.z);
    if(diff.norm()>16.0){
        LoggerHandler::getLogger()->LogPrint(ERROR, "EID {} is flying!", this->EID);
        reason = u"Flying is not allowed!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(player.value()->getReturnInfo(), reason, reason.length())));
        state->global_plist->remove(player.value()->getUsername());
        return;
    }
    auto relmove = v3<int8_t>(diff.x*32,diff.y*32,diff.z*32);
    auto t =  new p_Entity_RelativeMove(PacketReturnInfo(), this->EID, relmove);
    player.value()->setPosLook(this->new_xyz, player.value()->getYP());
    player.value()->setHeight(this->stance);
    serial->serialize(std::shared_ptr<p_Player_Pos>(new p_Player_Pos(player.value()->getReturnInfo(), player.value()->getOnGround(), xyz, player.value()->getStance())));
    this->queuePacket_ExPlayer(std::shared_ptr<p_Entity_RelativeMove>(t), state, serial, this->EID);
}

Event_PlayerUpdate_Look::Event_PlayerUpdate_Look(uint64_t destination_tick, uint32_t EID, bool on_ground, v2<float> new_yp) :
    Event_PlayerUpdateBase(destination_tick, EID, on_ground),
    new_yp(new_yp){
}

void Event_PlayerUpdate_Look::process(ServerState* state, PacketSerializer* serial){
    //TODO 
    //process look and on ground check pitch.
    //send entitylook packet to everyone
}

Event_PlayerUpdate_PosLook::Event_PlayerUpdate_PosLook(uint64_t destination_tick, uint32_t EID, bool on_ground, v3<double> new_xyz, double stance, v2<float> new_yp) : 
    Event_PlayerUpdate_Look(destination_tick, EID, on_ground, new_yp), 
    Event_PlayerUpdate_Pos(destination_tick, EID, on_ground, new_xyz, stance){
}

void Event_PlayerUpdate_PosLook::process(ServerState* state, PacketSerializer* serial){
    //TODO
    //process everything checking correct pitch
    //sendEntityPosLook to everyone
}






