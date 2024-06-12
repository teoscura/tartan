#include "packetprocessor.hpp"

#include <memory>

#include "../../helpers/loggerhandler.hpp"

PacketProcessor::PacketProcessor(PacketDeserializer* pdeserial,PacketSerializer* pserial, ServerState* state) : 
    deserializer(pdeserial),
    serializer(pserial),
    state(state){
}

//temporary function for single blob server
//mainserver will do this and send to others one at a time.
//FIXME
void PacketProcessor::retrieveQueue(){
    std::unique_ptr<DsPacket> tmp;
    while((tmp = std::move(this->deserializer->retrievePacket()))!=nullptr){
        this->in.push(std::move(tmp));
    }
}

void PacketProcessor::queuePacket(std::unique_ptr<DsPacket> pack){
    this->in.push(std::move(pack));
}

void PacketProcessor::queuePacket_Global(std::unique_ptr<DsPacket> pack){
    DsPacket packet = *pack.get();
    for(auto temp : this->state->global_plist->list){
        packet.setInfo(temp.getReturnInfo());
        this->out.push(std::make_unique<DsPacket>(packet));
    }
}

void PacketProcessor::queuePacket_ToPlayer(std::unique_ptr<DsPacket> pack, uint32_t to_eid){
    for(auto temp : this->state->global_plist->list){
        if(temp.getEntityId()==to_eid){
            pack->setInfo(temp.getReturnInfo());
            this->out.push(std::move(pack));
            return;
        }
    }
    LoggerHandler::getLogger()->LogPrint(ERROR, "Couldn't send pack to {}, EID doesnt exist!", to_eid);
}

void PacketProcessor::processPackets(){
    std::unique_ptr<DsPacket> tmp;
    while(!in.isEmpty()){
        tmp = std::move(this->in.pop());
        switch(tmp->getType()){
            //TODO
            case LOGIN:
                tmp = loginhandler.handlepacket(std::move(tmp), state->global_plist);
                this->out.push(std::move(tmp));
                break;
            case PLAYER:
                break;
            case ENTITY:
                break;
            case CHUNK_BLOCK:
                break;
            case MISC:
                break;
            case NOT_IMPLEMENTED:
                LoggerHandler::getLogger()->LogPrint(ERROR, "Unimplemented packet recieved! ID: {}", tmp->getID());
                break;
        }
    }
}


void PacketProcessor::sendPackets(){
    std::unique_ptr<DsPacket> tmp;
    while(!this->out.isEmpty()){
        tmp = std::move(out.pop());
        this->serializer->serialize(std::move(tmp));
    }
}

PacketProcessor::~PacketProcessor(){

}
