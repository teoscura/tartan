#include "packetprocessor.hpp"

#include "../../helpers/loggerhandler.hpp"
#include "events/eventschedule.hpp"
#include <optional>

PacketProcessor::PacketProcessor(PacketDeserializer* pdeserial) : 
    deserializer(pdeserial){
}

//TEMPORARY
void PacketProcessor::retrieveQueue(){
    std::optional<DsPacket> tmp;
    while((tmp = this->deserializer->retrievePacket()).has_value()){
        this->in.push(std::move(tmp.value()));
    }
}

void PacketProcessor::queuePacket(DsPacket pack){
    this->in.push(pack);
}

void PacketProcessor::processPackets(){
    std::optional<DsPacket> tmp = std::nullopt;
    while((tmp=this->in.pop()).has_value()){
        switch(tmp->getID()){
            case 0x00:
                break;
            case 0x01:
                break;
            case 0x02:
                break;
            case 0x03:
                break;
            case 0x07:
                break;
            case 0x09:
                break;
            case 0x0A:
                break;
            case 0x0B:
                break;
            case 0x0C:
                break;
            case 0x0D:
                break;
            case 0x0E:
                break;
            case 0x0F:
                break;
            case 0x10:
                break;
            case 0x12:
                break;
            case 0x13:
                break;
            case 0x65:
                break;
            case 0x66:
                break;
            case 0x6A:
                break;
            case 0x82:
                break;
            case 0xFF:
                break;
            default:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
        }
    }
    //TODO
}

PacketProcessor::~PacketProcessor(){
}
