#include "p_Misc.hpp"

#include "../../util/byteops.hpp"
#include "packet.hpp"
#include <string>
#include <vector>

p_ChatMessage::p_ChatMessage(PacketReturnInfo inf, std::u16string message) :
    DsPacket(inf),
    message(message){
}

p_ChatMessage::p_ChatMessage(Packet pack) : 
    DsPacket(pack.info){
    this->message_len = read2byteInt_BE(pack.bytes.data()+1);
    this->message = wstring_fromBytes(pack.bytes.data()+3, this->message_len);
}

std::u16string p_ChatMessage::getMessage(){
    return this->message;
}

uint8_t p_ChatMessage::getID(){
    return 0x03;
}

PacketCategories p_ChatMessage::getType(){
    return MISC;
}

Packet p_ChatMessage::serialize(){
    Packet pack(std::vector<uint8_t>(3+2*message.length()), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from16bit(pack.bytes.data()+1, message.length());
    writeBytes_fromWstring(pack.bytes.data()+3, message);
    return pack;
}

p_TimeUpdate::p_TimeUpdate(PacketReturnInfo inf, uint64_t time) : 
    DsPacket(inf),
    time(time){
}

uint8_t p_TimeUpdate::getID(){
    return 0x04;
}

PacketCategories p_TimeUpdate::getType(){
    return MISC;
}

Packet p_TimeUpdate::serialize(){
    Packet pack(std::vector<uint8_t>(9), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from64bit(pack.bytes.data()+1, this->time);
    return pack;
}

p_NewState::p_NewState(PacketReturnInfo inf, uint8_t reason) :
    DsPacket(inf),
    reason(reason){
}

uint8_t p_NewState::getID(){
    return 0x04;
}

PacketCategories p_NewState::getType(){
    return MISC;
}

Packet p_NewState::serialize(){
    Packet pack(std::vector<uint8_t>(2), this->getInfo());
    pack.bytes[0] = this->getID();
    pack.bytes[1] = this->reason;
    return Packet(pack);
}

p_StatIncrease::p_StatIncrease(PacketReturnInfo inf, int32_t stat_id, int8_t amount) :
    DsPacket(inf),
    stat_id(stat_id),
    amount(amount){
}

uint8_t p_StatIncrease::getID(){
    return 0xC8;
}

PacketCategories p_StatIncrease::getType(){
    return MISC;
}

Packet p_StatIncrease::serialize(){
    Packet pack(std::vector<uint8_t>(6), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes.data()+1, this->stat_id);
    pack.bytes[5] = this->amount;
    return pack;
}
