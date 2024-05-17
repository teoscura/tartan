#include <iostream>
#include <memory>
#include <utility>

#include "../../helpers/loggerhandler.hpp"
#include "p_deserial.hpp"

#include "../packets/p_KeepAlive.hpp"
#include "../packets/p_LoginRequest.hpp"
#include "../packets/p_HandShake.hpp"
#include "../packets/p_Kick.hpp"


PacketDeserializer::PacketDeserializer(){
    this->lg = LoggerHandler::getLogger();
}

PacketDeserializer::~PacketDeserializer(){
    
}

void PacketDeserializer::addPacket(std::unique_ptr<Packet> p){
    std::unique_ptr<DsPacket> pack;
    if(!isImplemented(p->bytes[0])){
        lg->LogPrint(ERROR, "Invalid packet recieved >{:0x}< skipping ahead.", (int)p->bytes[0]);
        std::cerr<<"[ERROR] Invalid packet recieved (> "<<std::hex << (int)p->bytes[0]<< std::dec <<" <), skipping ahead.\n";
        return;
    }
    switch(p->bytes[0]){
        case 0x00:
            if(p->size != 1){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p->bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x00 packet!\n";
                return;   
            }
            pack = std::make_unique<DsPacket>(p_KeepAlive(std::move(p)));
            break;
        case 0x01:
            if(p->size<16 || p->size > 48){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p->bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x01 packet!\n";
                return;
            }
            pack = std::make_unique<DsPacket>(p_LoginRequest(std::move(p)));
            break;
        case 0x02:
            if(p->size<3){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p->bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x02 packet!\n";
                return;
            }
            pack = std::make_unique<DsPacket>(p_HandShake(std::move(p)));
            break;
        case 0xFF:
            if(p->size!=1){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p->bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0xFF packet!\n";
                return;
            }
            pack = std::make_unique<DsPacket>(p_Kick(std::move(p)));
            break;
        default:
            break;
    }
    this->queue.push(std::move(pack));
}

