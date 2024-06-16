#include "event.hpp"

#include "../../../helpers/loggerhandler.hpp"

EventBase::EventBase(uint64_t delivery_tick) : 
    delivery_tick(delivery_tick){
}

uint64_t EventBase::getDeliveryTick(){
    return this->delivery_tick;
}

void EventBase::process(ServerState *state){
    LoggerHandler::getLogger()->LogPrint(INFO, "<!>Please dont queue up base events<!>");
    return;
}