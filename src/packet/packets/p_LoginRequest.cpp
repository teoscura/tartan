#include <iostream>
#include <memory>

#include "../../helpers/loggerhandler.hpp"
#include "../../util/byteops.hpp"
#include "p_LoginRequest.hpp"

p_LoginRequest::p_LoginRequest(){
    this->dimension=0;
    this->seed = 0;
    this->protocol = 0x0e;
    this->username_len=0;
}

p_LoginRequest::p_LoginRequest(std::unique_ptr<Packet> pack){
    Logger* lg = LoggerHandler::getLogger();
    this->info = pack->info;
    this->protocol = read4byteInt_BE(pack->bytes+1);
    this->username_len = read2byteInt_BE(pack->bytes+5);
    if((2*this->username_len+16)!=pack->size){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack->bytes[0]);
        std::cerr<<"[ERROR] 0x01 Packet invalid!, returning\n";
        return;
    }
    this->username = std::u16string(wstring_fromBytes(pack->bytes+7, this->username_len));
    this->seed = read8byteInt_BE(pack->bytes+(7+this->username_len*2));
    this->dimension = pack->bytes[15+this->username_len*2];
}

uint8_t p_LoginRequest::getID(){
    return 0x01;
}

PacketCategories p_LoginRequest::getType(){
    return LOGIN;
}

std::unique_ptr<Packet> p_LoginRequest::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    uint16_t size = 16+2*this->username_len;
    result->bytes = new uint8_t[size];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    result->size = size;
    writeBytes_from32bit(result->bytes+1, 14);
    writeBytes_from16bit(result->bytes+5, this->username_len);
    writeBytes_fromWstring(result->bytes+7, this->username);
    writeBytes_from64bit(result->bytes+7+2*this->username_len, this->seed);
    result->bytes[15+2*this->username_len] = this->dimension;
    return result;
}

p_LoginRequest::~p_LoginRequest(){}

