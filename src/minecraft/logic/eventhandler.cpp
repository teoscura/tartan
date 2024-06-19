#include "eventhandler.hpp"

EventHandler::EventHandler(PacketSerializer* serializer, ServerState* state) : 
    serializer(serializer),
    state(state){
}

void EventHandler::insertEvent(EventBase event,uint32_t tick_delay){
    auto t = this->state->time.s_tick+tick_delay;
    event.setDeliveryTick(t);
    this->e_schedule.insert(event);
}

void EventHandler::processEvents(){
    for(auto t : this->e_schedule.getExpectedEvents(this->state->time.s_tick)){
        t.process(this->state, &this->out);
    }
}

void EventHandler::sendPackets(){
    auto tmpsz = out.size();
    for(int i=0;i<tmpsz;i++){
        this->serializer->serialize(out.pop().value());
    }
}