#ifndef E_LOGINEVENTS_H
#define E_LOGINEVENTS_H

#include "event.hpp"
#include <cstdint>
#include <string>

class Event_LoginLogRequest  : public EventBase {
    private:
        PacketReturnInfo inf;
        uint64_t version;
    public:
        Event_LoginLogRequest(uint64_t delivery_tick, PacketReturnInfo inf, uint64_t version);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_LoginLogRequest() override;
};

class Event_LoginHandshake  : public EventBase {
    private:
        std::u16string username;
        PacketReturnInfo inf;
    public:
        Event_LoginHandshake(uint64_t delivery_tick, std::u16string username, PacketReturnInfo inf);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_LoginHandshake() override;
};



#endif