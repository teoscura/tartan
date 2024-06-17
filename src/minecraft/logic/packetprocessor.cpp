#include "packetprocessor.hpp"

#include "../../helpers/loggerhandler.hpp"
#include "events/eventschedule.hpp"

PacketProcessor::PacketProcessor(PacketDeserializer* pdeserial) : 
    deserializer(pdeserial){
}

//TEMPORARY
void PacketProcessor::retrieveQueue(){
    DsPacket tmp;
    while(!this->deserializer->isEmpty()){
        tmp = this->deserializer->retrievePacket();
        this->in.push(std::move(tmp));
    }
}

void PacketProcessor::queuePacket(DsPacket pack){
    this->in.push(pack);
}

void PacketProcessor::processPackets(){
    //TODO
}

PacketProcessor::~PacketProcessor(){
}
