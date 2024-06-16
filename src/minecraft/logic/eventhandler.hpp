#ifndef E_HANDLER_H
#define E_HANDLER_H

#include "../../packet/handler/p_serial.hpp"
#include "events/eventschedule.hpp"

class EventHandler{
    private:
        ServerState* state;
        EventSchedule e_schedule;
        PacketSerializer* serializer;
    public:
        EventHandler(PacketSerializer* serializer, ServerState* state);
        void processEvents();
};



#endif