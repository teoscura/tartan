#include "../../util/byteops.hpp"

#include <iostream>
#include <memory>

#include "../../helpers/loggerhandler.hpp"
#include "p_Kick.hpp"

p_Kick::p_Kick(std::unique_ptr<Packet> pack){
    Logger* lg = LoggerHandler::getLogger();
    this->info = pack->info;
    this->reason_len = read2byteInt_BE(pack->bytes+1);
    if((3+2*this->reason_len)!=pack->size){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack->bytes[0]);
        std::cerr<<"[ERROR] 0xFF Packet invalid!, returning\n";
        return;
    }
    this->reason = wstring_fromBytes(pack->bytes+3, reason_len);
}

p_Kick::p_Kick(std::u16string resp, uint16_t len){
    this->reason = resp;
    this->reason_len = len;
}

uint8_t p_Kick::getID(){
    return 0xFF;
}

PacketCategories p_Kick::getType(){
    return LOGIN;
}


std::unique_ptr<Packet> p_Kick::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    uint16_t size = 3+2*this->reason_len;
    result->size = size;
    result->bytes = new uint8_t[size];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    writeBytes_from16bit(result->bytes+1, this->reason_len);
    writeBytes_fromWstring(result->bytes+3, this->reason);
    return result;
}

p_Kick::~p_Kick(){}

