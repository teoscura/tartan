#ifndef MC_PP_PROCESSOR_H
#define MC_PP_PROCESSOR_H

#include "../../packet/handler/queue.hpp"
#include "eventhandler.hpp"

class PacketProcessor{
    protected:
        PacketQueue* in;
    public:
        PacketProcessor(PacketQueue* deserial);
        void processPackets(ServerState* state, EventHandler* handler);
        ~PacketProcessor() = default;
};

#endif  