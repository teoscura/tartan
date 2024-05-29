#include "e_playerupdate.hpp"
#include "event.hpp"

Event_PlayerUpdate::Event_PlayerUpdate(/*TODO fields*/uint64_t destination_tick, EventDeliveryType delivery_type) : 
    EventBase(destination_tick, delivery_type){

}