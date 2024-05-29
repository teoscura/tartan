#ifndef E_PLAYERUPDATE_H
#define E_PLAYERUPDATE_H

#include "event.hpp"

class Event_PlayerUpdate : public EventBase{
    private:
        uint64_t EID;
        //TODO fields.
    public:
        Event_PlayerUpdate(/*TODO fields*/uint64_t destination_tick, EventDeliveryType delivery_type);
        EventType getType() override;
        ~Event_PlayerUpdate() override;
};

#endif


