#ifndef MC_PP_PROCESSOR_H
#define MC_PP_PROCESSOR_H

#include <memory>

#include "../../packet/handler/p_deserial.hpp"
#include "../../packet/handler/p_serial.hpp"
#include "../../packet/handler/queue.hpp"
#include "../server/serverstate.hpp"
#include "events/eventschedule.hpp"
#include "loginhandler.hpp"

class PacketProcessor{
    protected:
        PacketQueue in;
        PacketQueue out;
        //FIXME remove deserializer pointer after test
        PacketDeserializer* deserializer;
        PacketSerializer* serializer;
        ServerState* state;
        EventSchedule e_schedule;
        LoginHandler loginhandler;
    public:
        PacketProcessor(PacketDeserializer* deserial, PacketSerializer* pserial, ServerState* state);
        void retrieveQueue();
        
        void queuePacket(std::unique_ptr<DsPacket> pack);
        void queuePacket_Global(std::unique_ptr<DsPacket> pack);
        void queuePacket_ToPlayer(std::unique_ptr<DsPacket> pack, uint32_t target_eid);
        void queuePacket_ExPlayer(std::unique_ptr<DsPacket> pack, uint32_t excluded_eid);

        void processPackets();
        void sendPackets();

        ~PacketProcessor();
};

#endif  