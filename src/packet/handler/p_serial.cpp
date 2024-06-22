#include "p_serial.hpp"

#include "../../helpers/loggerhandler.hpp"
#include "p_interface.hpp"
#include <memory>

PacketSerializer::PacketSerializer(){
    this->next = new PacketInterface();
}

void PacketSerializer::serialize(std::shared_ptr<DsPacket> p){
    Packet result = p->serialize();
    if(result.bytes.size()==0){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to serialize unimplemented {} packet!", (int)p->getID());
        return;
    }
    this->next->insert_packet(result);
}

PacketInterface* PacketSerializer::get_next(){
    return this->next;
}

PacketSerializer::~PacketSerializer(){
    delete this->next;
}