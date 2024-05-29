#include "event.hpp"

EventBase::EventBase(uint64_t delivery_tick, EventDeliveryType delivery_type) : delivery_tick(delivery_tick), delivery_type(delivery_type){
}

uint64_t EventBase::getDeliveryTick(){
    return this->delivery_tick;
}

EventType EventBase::getType(){
    return BASE;
}