#include "packetprocessor.hpp"

#include <optional>

#include "../../packet/packets/p_Login.hpp"
#include "../../helpers/loggerhandler.hpp"
#include "events/e_login.hpp"
#include "events/e_player.hpp"

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

void PacketProcessor::processPackets(EventHandler* handler){
    std::optional<DsPacket> tmp = std::nullopt;
    while((tmp=this->in.pop()).has_value()){
        switch(tmp->getID()){
            case 0x00:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x01:
                {auto t = static_cast<p_LoginRequest&>(tmp.value());
                handler->insertEvent(Event_LoginLogRequest(0, t.getInfo(), t.protocol), 1);
                break;}
            case 0x02:
                {auto t = static_cast<p_HandShake&>(tmp.value());
                handler->insertEvent(Event_LoginHandshake(0, t.getInfo(), t.username), 1);
                break;}
            case 0x03:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x07:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x09:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x0A:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x0B:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x0C:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x0D:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x0E:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x0F:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x10:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x12:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x13:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x65:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x66:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x6A:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0x82:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
                break;
            case 0xFF:
                LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", tmp->getID());
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
