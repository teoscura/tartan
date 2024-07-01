#include "p_serial.hpp"

#include "../../helpers/loggerhandler.hpp"
#include <memory>

void PacketSerializer::serialize(std::shared_ptr<DsPacket> p){
    Packet result = p->serialize();
    if(result.bytes.size()==0){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to serialize unimplemented {} packet!", (int)p->getID());
        return;
    }
    this->out.push_back(result);
}

std::vector<Packet>* PacketSerializer::getOut(){
    return &this->out;
}