#ifndef E_BASE_H
#define E_BASE_H

#include <cstdint>

#include "../../../packet/handler/queue.hpp"
#include "../../server/serverstate.hpp"

class EventBase{
    private:
        uint64_t delivery_tick;
    public: 
        EventBase(uint64_t delivery_tick);
        uint64_t getDeliveryTick();
        void queuePacket_Global(DsPacket pack, ServerState* state, PacketQueue* queue);
        void queuePacket_ToPlayer(DsPacket pack, ServerState* state, PacketQueue* queue, uint32_t target_eid);
        void queuePacket_ExPlayer(DsPacket pack, ServerState* state, PacketQueue* queue, uint32_t excluded_eid);
        virtual void process(ServerState* state, PacketQueue* serial);
        virtual ~EventBase() = default;
};

#endif