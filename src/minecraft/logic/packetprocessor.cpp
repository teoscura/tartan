#include "packetprocessor.hpp"

#include <iostream>
#include <memory>

#include "../../helpers/loggerhandler.hpp"

PacketProcessor::PacketProcessor(PacketDeserializer* pdeserial,PacketSerializer* pserial, PlayerList* plist) : 
    deserializer(pdeserial),
    serializer(pserial),
    plist(plist){}

//temporary function for single blob server
//mainserver will do this and send to others one at a time.
//FIXME
void PacketProcessor::retrieveQueue(){
    std::unique_ptr<DsPacket> tmp;
    while((tmp = std::move(this->deserializer->retrievePacket()))!=nullptr){
        this->in.push(std::move(tmp));
    }
}

void PacketProcessor::queuePacket(std::unique_ptr<DsPacket> p ){
    this->in.push(std::move(p));
}

void PacketProcessor::processPackets(){
    std::unique_ptr<DsPacket> tmp;
    while(!in.isEmpty()){
        std::cout<<"sheesh3333\n";
        tmp = std::move(this->in.pop());
        std::cout<<"sheesh3333\n";
        switch(tmp->getType()){
            //TODO
            case LOGIN:
                std::cout<<"sheesh\n";
                tmp = loginhandler.handlepacket(std::move(tmp), plist);
                this->serializer->serialize(std::move(tmp));
                std::cout<<"sent packet!\n";
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

PacketProcessor::~PacketProcessor(){

}
