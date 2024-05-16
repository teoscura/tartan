#include "p_SpawnPosition.hpp"

#include <iostream>
#include <memory>

#include "../../helpers/loggerhandler.hpp"
#include "../../util/byteops.hpp"

uint8_t p_SpawnPosition::getID(){
    return 0x06;
}

p_SpawnPosition::p_SpawnPosition(std::unique_ptr<Packet> pack){
    auto lg = LoggerHandler::getLogger();
    if((1+3*sizeof(int32_t))!=pack->size){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack->bytes[0]);
        std::cerr<<"[ERROR] 0x06 Packet invalid!, returning\n";
        return;
    }
    this->x = read4byteInt_BE(pack->bytes+1);
    this->y = read4byteInt_BE(pack->bytes+5);
    this->z = read4byteInt_BE(pack->bytes+9);
}

std::unique_ptr<Packet> p_SpawnPosition::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    uint16_t size = 13;
    result->size = size;
    result->bytes = new uint8_t[size];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    writeBytes_from32bit(result->bytes+1, this->x);
    writeBytes_from32bit(result->bytes+5, this->y);
    writeBytes_from32bit(result->bytes+9, this->z);
    return result;
}

p_SpawnPosition::~p_SpawnPosition(){}