#ifndef E_HANDLER_H
#define E_HANDLER_H

#include "../../packet/handler/p_serial.hpp"
#include "../server/serverstate.hpp"
#include "events/event.hpp"

class EventHandler{
    private:
        ServerState* state;
        std::vector<std::shared_ptr<EventBase>> event_schedule;
        PacketSerializer* serializer;
    public:
        EventHandler(PacketSerializer* serializer, ServerState* state);
        void insertEvent(std::shared_ptr<EventBase> event, uint32_t tick_delay);
        void processEvents();
};



#endif