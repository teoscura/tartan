#ifndef E_BASE_H
#define E_BASE_H

#include <cstdint>

#include "../../../packet/handler/p_serial.hpp"
#include "../../server/serverstate.hpp"

class EventBase{
    private:
        uint64_t delivery_tick;
    public: 
        EventBase(uint64_t delivery_tick);
        void setDeliveryTick(uint64_t delivery_tick); /* this function is only to be inside of event scheduler functions. nowhere else.*/
        uint64_t getDeliveryTick();
        void queuePacket_Global(std::shared_ptr<DsPacket> pack, ServerState* state, PacketSerializer* serial);
        void queuePacket_ToPlayer(std::shared_ptr<DsPacket> pack, ServerState* state, PacketSerializer* serial, uint32_t target_eid);
        void queuePacket_ExPlayer(std::shared_ptr<DsPacket> pack, ServerState* state, PacketSerializer* serial, uint32_t excluded_eid);
        virtual void process(ServerState* state, PacketSerializer* serial);
        virtual ~EventBase() = default;
};

#endif