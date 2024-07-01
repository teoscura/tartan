#include "eventhandler.hpp"

#include <optional>

EventHandler::EventHandler(PacketSerializer* serializer, ServerState* state) : 
    serializer(serializer),
    state(state){
}

void EventHandler::insertEvent(std::shared_ptr<EventBase> event,uint32_t tick_delay){
    
    auto t = this->state->time.s_tick+tick_delay;
    event->setDeliveryTick(t);
    this->e_schedule.insert(event);
}

void EventHandler::processEvents(){
    std::optional<std::shared_ptr<EventBase>> t;
    while((t=this->e_schedule.getLateEvent(this->state->time.s_tick)).has_value()){
        t.value()->process(this->state, this->serializer);
    }
}