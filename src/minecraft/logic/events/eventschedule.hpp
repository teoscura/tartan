#ifndef E_SCHEDULE_H
#define E_SCHEDULE_H

#include <cstdint>
#include <memory>
#include <vector>

#include "event.hpp"

class EventSchedule{
    private:
        std::vector<std::shared_ptr<EventBase>> event_schedule;
    public:
        void insert(std::shared_ptr<EventBase> event);
        std::optional<std::shared_ptr<EventBase>> getLateEvent(uint64_t delivery_tick);
};

#endif