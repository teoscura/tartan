#ifndef E_BASE_H
#define E_BASE_H

#include <cstdint>

enum EventType{
    BASE = 0x00,
};

enum EventDeliveryType{
    SENDPACKETGLOBAL,
};

class EventBase{
    private:
        uint64_t delivery_tick;
    public: 
        const EventDeliveryType delivery_type;
        EventBase(uint64_t, EventDeliveryType delivery_type);
        uint64_t getDeliveryTick();
        virtual EventType getType();
        virtual ~EventBase() = default;
};

#endif