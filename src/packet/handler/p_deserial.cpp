#include "p_deserial.hpp"

#include <iostream>
#include <utility>

#include "../../helpers/loggerhandler.hpp"
#include "../packets/p_Login.hpp"
#include "../packets/p_Player.hpp"
// #include "../packets/p_Entity.hpp"
#include "queue.hpp"

PacketDeserializer::PacketDeserializer(){
    this->lg = LoggerHandler::getLogger();
}

PacketDeserializer::~PacketDeserializer(){
}

void PacketDeserializer::addPacket(Packet p){
    DsPacket pack;
    if(!isImplemented(p.bytes[0])){
        lg->LogPrint(ERROR, "Invalid packet recieved >{:0x}< skipping ahead.", (int)p.bytes[0]);
        std::cerr<<"[ERROR] Invalid packet recieved (> "<<std::hex << (int)p.bytes[0]<< std::dec <<" <), skipping ahead.\n";
        return;
    }
    switch(p.bytes[0]){
        case 0x00:
            if(p.size != 1){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x00 packet!\n";
                return;   
            }
            pack = p_KeepAlive(p);
            break;
        case 0x01:
            if(p.size<16 || p.size > 48){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x01 packet!\n";
                return;
            }
            pack = p_LoginRequest(p);
            break;
        case 0x02:
            if(p.size<3){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x02 packet!\n";
                return;
            }
            pack = p_HandShake(p);
            break;
        case 0xFF:
            if(p.size!=1){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0xFF packet!\n";
                return;
            }
            pack = p_Kick(p);
            break;
        default:
            break;
    }
    this->queue.push(std::move(pack));
}

bool PacketDeserializer::isEmpty(){
    return this->queue.isEmpty();
}

DsPacket PacketDeserializer::retrievePacket(){
    if(queue.isEmpty()){
        return DsPacket();
    }
    return this->queue.pop();
}