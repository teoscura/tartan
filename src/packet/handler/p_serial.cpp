#include "p_serial.hpp"

#include "../../helpers/loggerhandler.hpp"
#include "p_interface.hpp"

PacketSerializer::PacketSerializer(){
    this->next = new PacketInterface();
}

void PacketSerializer::serialize(DsPacket p){
    if(!isImplemented(p.getID())){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to serialize unimplemented {} packet!", (int)p.getID());
        return;
    }
    Packet result = p.serialize();
    this->next->insert_packet(std::move(result));
}

PacketInterface* PacketSerializer::get_next(){
    return this->next;
}

PacketSerializer::~PacketSerializer(){
    delete this->next;
}