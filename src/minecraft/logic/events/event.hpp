#ifndef E_BASE_H
#define E_BASE_H

#include <cstdint>
#include <memory>

#include "../../../helpers/loggerhandler.hpp"
#include "../../server/serverstate.hpp"

class EventBase{
    private:
        uint64_t delivery_tick;
    public: 
        EventBase(uint64_t delivery_tick);
        uint64_t getDeliveryTick();
        virtual void process(ServerState* state);
        virtual ~EventBase() = default;
};

#endif