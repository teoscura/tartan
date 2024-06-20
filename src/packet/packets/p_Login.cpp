#include "p_Login.hpp"

#include <iostream>

#include "../../helpers/loggerhandler.hpp"
#include "../../util/byteops.hpp"
#include "packet.hpp"

p_LoginRequest::p_LoginRequest(PacketReturnInfo inf){
    this->setInfo(inf);
    this->dimension=0;
    this->seed = 0;
    this->protocol = 0x0e;
    this->username_len=0;
}

p_LoginRequest::p_LoginRequest(Packet pack){
    Logger* lg = LoggerHandler::getLogger();
    if(pack.bytes.size()<7){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        std::cerr<<"[ERROR] 0x01 Packet invalid!, returning\n";
        return;
    }
    this->info = pack.info;
    this->protocol = read4byteInt_BE(pack.bytes.data()+1);
    this->username_len = read2byteInt_BE(pack.bytes.data()+5);
    if((2*this->username_len+16)!=pack.bytes.size()){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        std::cerr<<"[ERROR] 0x01 Packet invalid!, returning\n";
        return;
    }
    this->username = std::u16string(wstring_fromBytes(pack.bytes.data()+7, this->username_len));
    this->seed = read8byteInt_BE(pack.bytes.data()+(7+this->username_len*2));
    this->dimension = pack.bytes[15+this->username_len*2];
}

uint8_t p_LoginRequest::getID(){
    return 0x01;
}

PacketCategories p_LoginRequest::getType(){
    return LOGIN;
}

Packet p_LoginRequest::serialize(){
    Packet result = Packet(std::vector<uint8_t>(16+2*this->username_len), this->getInfo());
    result.bytes[0] = this->getID();
    writeBytes_from32bit(result.bytes.data()+1, 14);
    writeBytes_from16bit(result.bytes.data()+5, this->username_len);
    writeBytes_fromWstring(result.bytes.data()+7, this->username);
    writeBytes_from64bit(result.bytes.data()+7+2*this->username_len, this->seed);
    result.bytes[15+2*this->username_len] = this->dimension;
    return result;
}

p_HandShake::p_HandShake(Packet pack){
    Logger* lg = LoggerHandler::getLogger();
    this->info = pack.info;
    this->username_len = read2byteInt_BE(pack.bytes.data()+1);
    if((3+2*this->username_len)!=pack.bytes.size()){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        std::cerr<<"[ERROR] 0x02 Packet invalid!, returning\n";
        return;
    }
    this->username = wstring_fromBytes(pack.bytes.data()+3, username_len);
}

p_HandShake::p_HandShake(std::u16string resp, PacketReturnInfo inf) : 
    DsPacket(inf),
    username(resp),
    username_len(resp.length()){
}

uint8_t p_HandShake::getID(){
    return 0x02;
}

PacketCategories p_HandShake::getType(){
    return LOGIN;
}

Packet p_HandShake::serialize(){
    Packet result = Packet(std::vector<uint8_t>(3+2*this->username_len), this->getInfo());
    result.bytes[0] = this->getID();
    writeBytes_from16bit(result.bytes.data()+1, this->username_len);
    writeBytes_fromWstring(result.bytes.data()+3, this->username);
    return result;
} 

p_Kick::p_Kick(Packet pack){
    Logger* lg = LoggerHandler::getLogger();
    this->info = pack.info;
    this->reason_len = read2byteInt_BE(pack.bytes.data()+1);
    if((3+2*this->reason_len)!=pack.bytes.size()){
        lg->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        std::cerr<<"[ERROR] 0xFF Packet invalid!, returning\n";
        return;
    }
    this->reason = wstring_fromBytes(pack.bytes.data()+3, reason_len);
}

p_Kick::p_Kick(PacketReturnInfo inf, std::u16string resp, uint16_t len) : 
    DsPacket(inf), 
    reason(resp),
    reason_len(len){
}

uint8_t p_Kick::getID(){
    return 0xFF;
}

PacketCategories p_Kick::getType(){
    return LOGIN;
}


Packet p_Kick::serialize(){
    Packet result = Packet(std::vector<uint8_t>(3+2*this->reason_len), this->getInfo());
    result.bytes[0] = this->getID();
    writeBytes_from16bit(result.bytes.data()+1, this->reason_len);
    writeBytes_fromWstring(result.bytes.data()+3, this->reason);
    return result;
}
