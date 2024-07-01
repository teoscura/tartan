#include "e_login.hpp"

#include <codecvt>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

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
    std::cout<<"Recieved logreq!\n";
    std::u16string reason;
    if(!state->global_plist->findLogin(this->inf).has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a login request while in an invalid state!", inf.epoll_fd);
        reason = u"Player is already online, or never sent a handshake!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, std::u16string(reason), reason.length())));
        state->global_plist->cleanupLogin(state->time.s_tick);
        return;
    }
    if(version!=0x0e){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} tried to join with an incorrect version!", inf.epoll_fd);
        reason = u"Wrong version!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, std::u16string(reason), reason.length())));
        state->global_plist->cleanupLogin(state->time.s_tick);
        return;
    }
    auto eid= state->global_elist->allocateEID();
    Player new_user(this->inf, state->global_plist->findLogin(this->inf).value()->username, eid);
    auto t = std::make_shared<Player>(new_user);
    state->global_elist->insert(t);
    state->global_plist->insert(t); 
    state->global_plist->cleanupLogin(state->time.s_tick);
    serial->serialize(std::shared_ptr<p_LoginRequest>(new p_LoginRequest(this->inf)));
    serial->serialize(std::shared_ptr<p_SpawnPosition>(new p_SpawnPosition(this->inf, t->getRespawnPos())));
    //TODO the rest2
    auto sp = v3<double>(new_user.getRespawnPos().x, new_user.getRespawnPos().y, new_user.getRespawnPos().z);
    serial->serialize(std::shared_ptr<p_Player_PosLook>(new p_Player_PosLook(this->inf, true, sp, STAND, v2<float>(0,0))));
    this->queuePacket_ExPlayer(std::shared_ptr<p_ChatMessage>(new p_ChatMessage(PacketReturnInfo(), 
                               std::u16string(u"§p"+t->getUsername() + u" logged in the server.§r§f"))), 
                               state, serial, t->getEntityId());
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
    std::cout<<converter.to_bytes(t->getUsername()) << " logged in the server.\n";
}

Event_LoginHandshake::Event_LoginHandshake(uint64_t delivery_tick, PacketReturnInfo inf, std::u16string username) : 
    EventBase(delivery_tick),
    inf(inf),
    username(username){
}

void Event_LoginHandshake::process(ServerState* state, PacketSerializer* serial){
    std::u16string reason;
    if(state->global_plist->isOnline(this->username)){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a handshake while already being online!", inf.epoll_fd);
        reason = u"Player is already online!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    if(state->global_plist->isLogin(this->username)){
        auto t = state->global_plist->findLogin(this->inf);
        if(t.has_value()&&(state->time.s_tick-t.value()->login_tick < 400)){
            LoggerHandler::getLogger()->LogPrint(ERROR, "{} is already logging in!", inf.epoll_fd);
            reason = u"Player is already logging in!";
            serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
            return;
        }
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a handshake while already having sent one!", inf.epoll_fd);
        reason = u"Player sent a handshake while already having sent one!";
        serial->serialize(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    auto newplayer = new LoginPlayer(state->time.s_tick, this->username, this->inf);
    state->global_plist->insertLogin(std::shared_ptr<LoginPlayer>(newplayer));
    serial->serialize(std::shared_ptr<p_HandShake>(new p_HandShake(u"-", this->inf)));
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
    std::cout<<converter.to_bytes(newplayer->username) << " sent a handshake.\n";
}


