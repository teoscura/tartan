#include "../../util/byteops.hpp"

#include <iostream>
#include <memory>

#include "../../helpers/loggerhandler.hpp"
#include "p_HandShake.hpp"

p_HandShake::p_HandShake(std::unique_ptr<Packet> pack){
    Logger* lg = LoggerHandler::getLogger();
    this->info = pack->info;
    this->username_len = read2byteInt_BE(pack->bytes+1);
    if((3+2*this->username_len)!=pack->size){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack->bytes[0]);
        std::cerr<<"[ERROR] 0x02 Packet invalid!, returning\n";
        return;
    }
    this->username = wstring_fromBytes(pack->bytes+3, username_len);
    pack = nullptr;
}

p_HandShake::p_HandShake(std::u16string resp, uint16_t len){
    this->username = resp;
    this->username_len = len;
}

uint8_t p_HandShake::getID(){
    return 0x02;
}

PacketCategories p_HandShake::getType(){
    return LOGIN;
}

std::unique_ptr<Packet> p_HandShake::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    uint16_t size = 3+2*this->username_len;
    result->size = size;
    result->bytes = new uint8_t[size];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    writeBytes_from16bit(result->bytes+1, this->username_len);
    writeBytes_fromWstring(result->bytes+3, this->username);
    return result;
} 

p_HandShake::~p_HandShake(){}

