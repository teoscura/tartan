#ifndef MC_PP_PROCESSOR_H
#define MC_PP_PROCESSOR_H

#include "../../packet/handler/p_deserial.hpp"
#include "../../packet/handler/p_serial.hpp"
#include "../../packet/handler/queue.hpp"
#include "../server/serverstate.hpp"
#include "events/eventschedule.hpp"

class PacketProcessor{
    protected:
        PacketQueue in;
        PacketQueue out;
        //FIXME remove deserializer pointer after test
        PacketDeserializer* deserializer;
        PacketSerializer* serializer;
        ServerState* state;
        EventSchedule* e_schedule;
    public:
        PacketProcessor(PacketDeserializer* deserial, PacketSerializer* pserial, ServerState* state, EventSchedule* e_schedule);
        void retrieveQueue();
        
        void queuePacket(DsPacket pack);
        void queuePacket_Global(DsPacket pack);
        void queuePacket_ToPlayer(DsPacket pack, uint32_t target_eid);
        void queuePacket_ExPlayer(DsPacket pack, uint32_t excluded_eid);

        void processPackets();
        void sendPackets();

        ~PacketProcessor();
};

#endif  