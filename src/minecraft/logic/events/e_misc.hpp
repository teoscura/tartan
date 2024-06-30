#ifndef E_MISC_H
#define E_MISC_H

#include <cstdint>
#include <string>

#include "event.hpp"


class Event_ChatMessage  : public EventBase {
    private:
        PacketReturnInfo inf;
        std::u16string message;
    public:
        Event_ChatMessage(uint64_t delivery_tick, PacketReturnInfo inf, std::u16string message);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_ChatMessage() override = default;
};

#endif