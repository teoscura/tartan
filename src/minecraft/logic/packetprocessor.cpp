#include "packetprocessor.hpp"

#include "../../helpers/loggerhandler.hpp"
#include "events/eventschedule.hpp"

PacketProcessor::PacketProcessor(PacketDeserializer* pdeserial,PacketSerializer* pserial, ServerState* state, EventSchedule* e_schedule) : 
    deserializer(pdeserial),
    serializer(pserial),
    state(state),
    e_schedule(e_schedule){
}

//temporary function for single blob server
//mainserver will do this and send to others one at a time.
//FIXME
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

void PacketProcessor::queuePacket_Global(DsPacket pack){
    auto packet = pack;
    for(auto temp : this->state->global_plist->list){
        pack.setInfo(temp.getReturnInfo());
        this->out.push(pack);
    }
}

void PacketProcessor::queuePacket_ToPlayer(DsPacket pack, uint32_t to_eid){
    for(auto temp : this->state->global_plist->list){
        if(temp.getEntityId()==to_eid){
            pack.setInfo(temp.getReturnInfo());
            this->out.push(std::move(pack));
            return;
        }
    }
    LoggerHandler::getLogger()->LogPrint(ERROR, "Couldn't send pack to {}, EID doesnt exist!", to_eid);
}

void PacketProcessor::processPackets(){

}


void PacketProcessor::sendPackets(){
    DsPacket tmp;
    while(!this->out.isEmpty()){
        tmp = out.pop();
        this->serializer->serialize(tmp);
    }
}

PacketProcessor::~PacketProcessor(){
}
