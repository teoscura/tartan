#include "packetprocessor.hpp"

#include <memory>

#include "../../packet/handler/p_serialhandler.hpp"
#include "../../helpers/loggerhandler.hpp"
#include "logic.hpp"

PacketProcessor::PacketProcessor() : 
    serializer(SerializerHandler::getSerializer()){
}


void PacketProcessor::queuePacket(std::unique_ptr<DsPacket> p ){
    this->in.push(std::move(p));
}
//remember, never add packets and process at the same time.
void PacketProcessor::processPackets(){
    std::unique_ptr<DsPacket> tmp;
    while(!in.isEmpty()){
        tmp = std::move(this->in.front());
        this->in.pop();
        switch(whatCategory(tmp->getID())){
            //TODO remove continues when fixed
            case PLAYER:
                continue;
                break;
            case ENTITY:
                tmp = entityhandler.processPacket(std::move(tmp));
                break;
            case CHUNK_BLOCK:
                continue;
                break;
            case MISC:
                continue;
                break;
            case NOT_IMPLEMENTED:
                LoggerHandler::getLogger()->LogPrint(ERROR, "Unimplemented packet recieved! ID: {}", tmp->getID());
                break;
        }
        this->serializer->serialize(std::move(tmp));
    }
}