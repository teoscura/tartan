#include "e_login.hpp"
#include "event.hpp"

Event_LoginLogRequest::Event_LoginLogRequest(uint64_t delivery_tick, PacketReturnInfo inf, uint64_t version) :
    EventBase(delivery_tick),
    inf(inf),
    version(version){
}

void Event_LoginLogRequest::process(ServerState *state){
    if(version!=0x0e){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} tried to join with an incorrect version!", inf.epoll_fd);
        
        return;
    }
    //TODO FINISH
}   