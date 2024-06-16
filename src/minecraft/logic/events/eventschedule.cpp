#include "eventschedule.hpp"

#include <vector>

#include "event.hpp"

void EventSchedule::insert(EventBase event){
    for(int i=0; i<this->event_schedule.size();i++){
        if(this->event_schedule.at(i).getDeliveryTick()>event.getDeliveryTick()){
            this->event_schedule.insert(this->event_schedule.begin()+i, event);
            break;
        }
    }
}

std::vector<EventBase> EventSchedule::getExpectedEvents(uint64_t delivery_tick){
    std::vector<EventBase> res;
    std::size_t where;
    bool found;
    for(int i=0;i<this->event_schedule.size();i++){
        EventBase& t = this->event_schedule[i];
        if(t.getDeliveryTick()>delivery_tick){
            found = true;
            where=i;
            break;
        }
        res.push_back(std::move(t));
    }
    if(found){
        this->event_schedule.erase(this->event_schedule.begin(), this->event_schedule.begin()+where+1);
    }
    return res;
}