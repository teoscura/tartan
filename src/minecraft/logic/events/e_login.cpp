#include "e_login.hpp"

#include <codecvt>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

#include "../../../packet/packets/p_Entity.hpp"
#include "../../../packet/packets/p_Login.hpp"
#include "../../../packet/packets/p_Player.hpp"
#include "../../../packet/packets/p_Misc.hpp"
#include "../../../helpers/loggerhandler.hpp"
#include "event.hpp"


Event_LoginLogRequest::Event_LoginLogRequest(uint64_t delivery_tick, PacketReturnInfo inf, uint64_t version) :
    EventBase(delivery_tick),
    inf(inf),
    version(version){
}

void Event_LoginLogRequest::process(ServerState *state, PacketSerializer* serial){
    std::u16string reason;
    auto tmpplayer = state->global_plist->findPlayer(this->inf);
    if(!tmpplayer.has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} is not in the player list!", inf.epoll_fd);
        reason = u"Player is not in the player list!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    auto player = tmpplayer.value();
    if(player->assertStatus(L_PLAYING)){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a loginrequest while already being online!", inf.epoll_fd);
        reason = u"Player is already online!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    if(!player->assertStatus(L_HANDSHAKE)){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a login request while in an invalid state!", inf.epoll_fd);
        reason = u"Player is already online, or never sent a handshake!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, std::u16string(reason), reason.length())));
        return;
    }
    if(version!=0x0e){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} tried to join with an incorrect version!", inf.epoll_fd);
        reason = u"Wrong version!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, std::u16string(reason), reason.length())));
        return;
    }
    player->setState(L_PLAYING);
    state->global_elist->insert(player);
    serial->serialize(std::shared_ptr<p_LoginRequest>(new p_LoginRequest(this->inf)));
    serial->serialize(std::shared_ptr<p_SpawnPosition>(new p_SpawnPosition(this->inf, player->getRespawnPos())));
    //TODO the rest2
    auto sp = v3<double>(player->getRespawnPos().x, player->getRespawnPos().y, player->getRespawnPos().z);
    serial->serialize(std::shared_ptr<p_Player_PosLook>(new p_Player_PosLook(this->inf, true, sp, player->getHeight(), v2<float>(0,0))));
    this->queuePacket_Global(std::shared_ptr<p_ChatMessage>(new p_ChatMessage(PacketReturnInfo(), 
                               std::u16string(u"§6"+player->getUsername() + u" logged in the server.§r§f"))), 
                               state, serial);
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
    std::cout<<converter.to_bytes(player->getUsername()) << " logged in the server.\n";
    //TODO: load entire world around, and entities around it.
}

Event_LoginHandshake::Event_LoginHandshake(uint64_t delivery_tick, PacketReturnInfo inf, std::u16string username) : 
    EventBase(delivery_tick),
    inf(inf),
    username(username){
}

void Event_LoginHandshake::process(ServerState* state, PacketSerializer* serial){
    std::u16string reason;
    auto tmpplayer = state->global_plist->findPlayer(username);
    if(tmpplayer.has_value()){
        if(tmpplayer.value()->assertStatus(L_HANDSHAKE)){
            LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a handshake while already having sent one!", inf.epoll_fd);
            reason = u"Player sent a handshake while already having sent one!";
            serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
            return;
        }
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a handshake while already being online!", inf.epoll_fd);
        reason = u"Player is already online!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    Player* player = new Player(this->inf, this->username, state->global_elist->allocateEID());
    player->setState(L_HANDSHAKE);
    state->global_plist->insert(std::shared_ptr<Player>(player));
    serial->serialize(std::shared_ptr<p_HandShake>(new p_HandShake(u"-", this->inf)));
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
}

Event_PlayerDisconnect::Event_PlayerDisconnect(uint64_t delivery_tick, PacketReturnInfo inf) : 
    EventBase(delivery_tick),
    inf(inf){
}

void Event_PlayerDisconnect::process(ServerState* state, PacketSerializer* serial){
    auto tmpplayer = state->global_plist->findPlayer(this->inf);
    if(!state->global_plist->isOnline()
    player->setState(S_TODESPAWN);
    this->queuePacket_Global(std::shared_ptr<p_Entity_Delete>(new p_Entity_Delete(PacketReturnInfo(0), player->getEntityId())), state, serial);
    this->queuePacket_Global(std::shared_ptr<p_ChatMessage>(new p_ChatMessage(PacketReturnInfo(), 
                               std::u16string(u"§c"+player->getUsername() + u" left the server.§r§f"))), 
                               state, serial);
}

