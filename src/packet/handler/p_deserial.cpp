#include "p_deserial.hpp"

#include <iostream>
#include <memory>
#include <optional>

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
    switch(p.bytes[0]){
        case 0x00:
            if(p.bytes.size() != 1){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x00 packet!\n";
                return;   
            }
            this->queue.push(std::shared_ptr<DsPacket>(new p_KeepAlive(p)));
            break;
        case 0x01:
            if(p.bytes.size()<16 || p.bytes.size() > 48){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x01 packet!\n";
                return;
            }
            this->queue.push(std::shared_ptr<DsPacket>(new p_LoginRequest(p)));
            break;
        case 0x02:
            if(p.bytes.size()<3){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x02 packet!\n";
                return;
            }
            this->queue.push(std::shared_ptr<DsPacket>(new p_HandShake(p)));
            break;
        case 0x0B:
            if(p.bytes.size()!=34){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0x0B packet!\n";
                return;
            }
            this->queue.push(std::shared_ptr<DsPacket>(new p_Player_Pos(p)));
            break;
        case 0xFF:
            if(p.bytes.size()!=1){
                lg->LogPrint(ERROR, "Data isn't a valid {} packet!", (int)p.bytes[0]);
                std::cerr<<"[ERROR] Data isnt a valid 0xFF packet!\n";
                return;
            }
            this->queue.push(std::shared_ptr<DsPacket>(new p_Kick(p)));
            break;
        default:
            lg->LogPrint(ERROR, "Invalid packet recieved {:0x} skipping ahead.", (int)p.bytes[0]);
            std::cerr<<"[ERROR] Invalid packet recieved (> "<<std::hex << (int)p.bytes[0]<< std::dec <<" <), skipping ahead.\n";
            return;
    }
}

bool PacketDeserializer::isEmpty(){
    return this->queue.isEmpty();
}

std::optional<std::shared_ptr<DsPacket>> PacketDeserializer::retrievePacket(){
    if(queue.isEmpty()){
        return std::nullopt;
    }
    return this->queue.pop().value();
}
