#ifndef MC_PP_PROCESSOR_H
#define MC_PP_PROCESSOR_H

#include <memory>

#include "../../packet/handler/p_deserial.hpp"
#include "../../packet/handler/p_serial.hpp"
#include "../../packet/handler/queue.hpp"

#include "loginhandler.hpp"

class PacketProcessor{
    protected:
        PacketQueue in;
        //FIXME remove deserializer pointer after test
        PacketDeserializer* deserializer;
        PacketSerializer* serializer;
        PlayerList* plist;
        LoginHandler loginhandler;
    public:
        PacketProcessor(PacketDeserializer* deserial, PacketSerializer* pserial, PlayerList* plist);
        void retrieveQueue();
        void queuePacket(std::unique_ptr<DsPacket> p);
        void processPackets();
        ~PacketProcessor();
};

#endif  