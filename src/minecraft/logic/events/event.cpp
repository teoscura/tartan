#include "event.hpp"

#include "../../../helpers/loggerhandler.hpp"

EventBase::EventBase(uint64_t delivery_tick) : 
    delivery_tick(delivery_tick){
}

uint64_t EventBase::getDeliveryTick(){
    return this->delivery_tick;
}

void EventBase::queuePacket_Global(DsPacket pack, ServerState* state, PacketQueue* queue){
    auto packet = pack;
    for(auto temp : state->global_plist->list){
        pack.setInfo(temp.getReturnInfo());
        queue->push(pack);
    }
}

void EventBase::queuePacket_ToPlayer(DsPacket pack, ServerState* state, PacketQueue* queue, uint32_t target_eid){
    for(auto temp : state->global_plist->list){
        if(temp.getEntityId()==target_eid){
            pack.setInfo(temp.getReturnInfo());
            queue->push(pack);
            return;
        }
    }
    LoggerHandler::getLogger()->LogPrint(ERROR, "Couldn't send pack to {}, EID doesnt exist!", target_eid);
}

void EventBase::queuePacket_ExPlayer(DsPacket pack, ServerState* state, PacketQueue* queue, uint32_t excluded_eid){
    for(auto temp : state->global_plist->list){
        if(temp.getEntityId()!=excluded_eid){
            pack.setInfo(temp.getReturnInfo());
            queue->push(pack);
        }
    }
}

void EventBase::process(ServerState *state, PacketQueue* queue){
    LoggerHandler::getLogger()->LogPrint(INFO, "<!>Please dont queue up base events<!>");
    return;
}