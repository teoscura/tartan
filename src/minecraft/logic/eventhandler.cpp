#include "eventhandler.hpp"

#include <cstddef>

EventHandler::EventHandler(PacketSerializer* serializer, ServerState* state) : 
    serializer(serializer),
    state(state){
}

void EventHandler::insertEvent(std::shared_ptr<EventBase> event,uint32_t tick_delay){
    auto t = this->state->time.s_tick+tick_delay;
    event->setDeliveryTick(t);
    int i;
    for(i=0; i<this->event_schedule.size();i++){
        if(this->event_schedule.at(i)->getDeliveryTick()>event->getDeliveryTick()){
            
            break;
        }
    }
    this->event_schedule.insert(this->event_schedule.begin()+i, event);
}

void EventHandler::processEvents(){
    std::size_t how_many = 0;
    if(this->event_schedule.empty()){
        return;
    }
    for(auto t : this->event_schedule){
        if(t->getDeliveryTick()>this->state->time.s_tick){
            break;
        }
        t->process(this->state, this->serializer);
        how_many++;
    }
    this->event_schedule.erase(event_schedule.begin(),event_schedule.begin()+how_many);
}