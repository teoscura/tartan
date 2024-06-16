#ifndef E_SCHEDULE_H
#define E_SCHEDULE_H

#include <cstdint>
#include <vector>

#include "event.hpp"

class EventSchedule{
    private:
        std::vector<EventBase> event_schedule;
    public:
        void insert(EventBase event);
        std::vector<EventBase> getExpectedEvents(uint64_t delivery_tick);
};

#endif