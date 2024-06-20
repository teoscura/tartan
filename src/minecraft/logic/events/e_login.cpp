#include "e_login.hpp"

#include "../../../packet/packets/p_Login.hpp"
#include "../../../helpers/loggerhandler.hpp"
#include "event.hpp"
#include <memory>
#include <string>

Event_LoginLogRequest::Event_LoginLogRequest(uint64_t delivery_tick, PacketReturnInfo inf, uint64_t version) :
    EventBase(delivery_tick),
    inf(inf),
    version(version){
}

void Event_LoginLogRequest::process(ServerState *state, PacketQueue* queue){
    std::u16string reason;
    if(version!=0x0e){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} tried to join with an incorrect version!", inf.epoll_fd);
        reason = u"Wrong version!";
        queue->push(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    if(!state->global_plist->findLogin(this->inf).has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a login request while in an invalid state!", inf.epoll_fd);
        reason = u"Player is already online, or never sent a handshake!";
        queue->push(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    auto eid= state->global_elist->allocateEID();
    Player new_user(this->inf, state->global_plist->findLogin(this->inf).value()->username, eid);
    state->global_elist->insert(new_user);
    state->global_plist->insert(new_user); 
    queue->push(std::shared_ptr<p_LoginRequest>(new p_LoginRequest(this->inf)));
}   

Event_LoginHandshake::Event_LoginHandshake(uint64_t delivery_tick, PacketReturnInfo inf, std::u16string username) : 
    EventBase(delivery_tick),
    inf(inf),
    username(username){
}

void Event_LoginHandshake::process(ServerState* state, PacketQueue* queue){
    std::u16string reason;
    if(state->global_plist->isonline(this->username)){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a handshake while already being online!", inf.epoll_fd);
        reason = u"Player is already online!";
        queue->push(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    if(state->global_plist->isLogin(this->username)){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a handshake while already having sent one!", inf.epoll_fd);
        reason = u"Player sent a handshake while already having sent one!";
        queue->push(std::shared_ptr<p_Kick>(new p_Kick(this->inf, reason, reason.length())));
        return;
    }
    state->global_plist->insertLogin(LoginPlayer(this->username, this->inf));
    queue->push(std::shared_ptr<p_HandShake>(new p_HandShake(u"-", this->inf)));
}