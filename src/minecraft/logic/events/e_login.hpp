#ifndef E_LOGINEVENTS_H
#define E_LOGINEVENTS_H

#include <cstdint>
#include <string>

#include "event.hpp"

class Event_LoginLogRequest  : public EventBase {
    private:
        PacketReturnInfo inf;
        uint64_t version;
    public:
        Event_LoginLogRequest(uint64_t delivery_tick, PacketReturnInfo inf, uint64_t version);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_LoginLogRequest() override = default;
};

class Event_LoginHandshake  : public EventBase {
    private:
        PacketReturnInfo inf;
        std::u16string username;
    public:
        Event_LoginHandshake(uint64_t delivery_tick,PacketReturnInfo inf, std::u16string username);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_LoginHandshake() override = default;
};

#endif