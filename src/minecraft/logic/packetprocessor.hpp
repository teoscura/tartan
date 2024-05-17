#ifndef MC_PP_PROCESSOR_H
#define MC_PP_PROCESSOR_H

#include "../../packet/handler/p_serial.hpp"
#include "../../packet/handler/queue.hpp"
#include "entityhandler.hpp"
#include <memory>


class PacketProcessor{
    protected:
        PacketQueue in;
        PacketQueue out;
        PacketSerializer* serializer;
        EntityHandler entityhandler;
    public:
        PacketProcessor();
        void queuePacket(std::unique_ptr<DsPacket> p);
        void processPackets();
        ~PacketProcessor();
};

#endif  