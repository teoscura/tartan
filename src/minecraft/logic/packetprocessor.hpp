#ifndef MC_PP_PROCESSOR_H
#define MC_PP_PROCESSOR_H


#include "../../packet/handler/p_deserial.hpp"
#include "../../packet/handler/queue.hpp"
#include "eventhandler.hpp"

class PacketProcessor{
    protected:
        PacketQueue in;
        /*FIXME remove deserializer pointer after test*/
        PacketDeserializer* deserializer;
    public:
        PacketProcessor(PacketDeserializer* deserial);
        void queuePacket(DsPacket pack);
        void retrieveQueue();
        void processPackets(EventHandler* handler);
        ~PacketProcessor();
};

#endif  