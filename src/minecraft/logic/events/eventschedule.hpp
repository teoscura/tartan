#ifndef E_SCHEDULE_H
#define E_SCHEDULE_H

#include "event.hpp"
#include <cstdint>
#include <map>
#include <memory>
#include <vector>

class EventSchedule{
    private:
        std::vector<std::shared_ptr<EventBase>> event_schedule;
    public:
        void insert(std::shared_ptr<EventBase> event);
        std::vector<std::shared_ptr<EventBase>> getExpectedEvents(uint64_t delivery_tick);
};

#endif