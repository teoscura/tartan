#include "tmpmcserver.hpp"
#include "logic/packetprocessor.hpp"
#include <iostream>


//TODO dependency injection
TempServer::TempServer(PacketDeserializer* pdeserial, PacketSerializer* pserial):
    pp_processor(pdeserial, pserial, &this->global_plist),
    motherchunk(v2(0,0)){
};

void TempServer::loop(){
    while(1){
        this->pp_processor.retrieveQueue();
        this->pp_processor.processPackets();
    }
}