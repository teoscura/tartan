#ifndef E_BASE_H
#define E_BASE_H

#include <cstdint>

#include "../../server/serverstate.hpp"

enum EventType{
    BASE = 0x00,
};

enum EventDeliveryType{
    SENDPACKETGLOBAL,
};

class EventBase{
    private:
        uint64_t delivery_tick;
        uint32_t destination_player_id;
    public: 
        const EventDeliveryType delivery_type;
        EventBase(uint64_t, EventDeliveryType delivery_type);
        uint64_t getDeliveryTick();
        uint32_t getDestinationPlayerId();
        virtual void process(ServerState* state);
        virtual ~EventBase() = default;
};

#endif