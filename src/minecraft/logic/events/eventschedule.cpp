#include "eventschedule.hpp"

#include <optional>
#include <vector>

#include "event.hpp"

void EventSchedule::insert(std::shared_ptr<EventBase> event){
    for(int i=0; i<this->event_schedule.size();i++){
        if(this->event_schedule.at(i)->getDeliveryTick()>event->getDeliveryTick()){
            this->event_schedule.insert(this->event_schedule.begin()+i, event);
            break;
        }
    }
}

std::optional<std::shared_ptr<EventBase>> EventSchedule::getLateEvent(uint64_t delivery_tick){
    if(this->event_schedule.empty()){
        return std::nullopt;
    }
    if(this->event_schedule.at(0)->getDeliveryTick()<delivery_tick){
        std::shared_ptr<EventBase> tmp = this->event_schedule.at(0);
        this->event_schedule.erase(event_schedule.begin());
        return tmp;
    }
    return std::nullopt;
}