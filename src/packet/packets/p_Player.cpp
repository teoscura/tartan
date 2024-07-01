#include "p_Player.hpp"

#include <bit>
#include <cstdint>
#include <vector>

#include "../../helpers/loggerhandler.hpp"
#include "../../util/byteops.hpp"
#include "packet.hpp"

p_KeepAlive::p_KeepAlive(Packet pack){
    this->info = pack.info;
}

uint8_t p_KeepAlive::getID(){
    return 0x00;
}

PacketCategories p_KeepAlive::getType(){
    return PLAYER;
}

p_SpawnPosition::p_SpawnPosition(PacketReturnInfo inf, v3<int32_t> coords) : 
    DsPacket(inf),
    xyz(coords){
}

uint8_t p_SpawnPosition::getID(){
    return 0x06;
}

PacketCategories p_SpawnPosition::getType(){
    return PLAYER;
}


Packet p_SpawnPosition::serialize(){
    Packet result = Packet(std::vector<uint8_t>(13), this->getInfo());
    result.bytes[0] = this->getID();
    writeBytes_fromV3(result.bytes.data()+1, this->xyz);
    return result;
}

bool p_PlayerBase::getOnGround(){
    return this->on_ground;
}

p_PlayerBase::p_PlayerBase(PacketReturnInfo inf, bool on_ground) :
    on_ground(on_ground),
    DsPacket(inf){
}

p_PlayerBase::p_PlayerBase(Packet pack):
    DsPacket(pack.info){
    if(pack.bytes.size()<2){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
    this->on_ground = pack.bytes[pack.bytes.size()-1];
}

uint8_t p_PlayerBase::getID(){
    return 0x0A;
}

PacketCategories p_PlayerBase::getType(){
    return PLAYER;
}

Packet p_PlayerBase::serialize(){
    Packet result = Packet(std::vector<uint8_t>(2),this->getInfo());
    result.bytes[0] = this->getID();
    result.bytes[1] = this->on_ground;
    return result;
}

v3<double> p_Player_Pos::getXYZ(){
    return this->xyz;
}

double p_Player_Pos::getStance(){
    return this->stance;
}

p_Player_Pos::p_Player_Pos(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance) : 
    p_PlayerBase(inf, on_ground),
    xyz(xyz),
    stance(stance){
}

p_Player_Pos::p_Player_Pos(Packet pack) : 
    p_PlayerBase(pack.info, pack.bytes[33]){
    if(pack.bytes.size()!=34){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
    this->xyz.x = std::bit_cast<double>(read8byteInt_BE(pack.bytes.data()+1));
    this->xyz.y = std::bit_cast<double>(read8byteInt_BE(pack.bytes.data()+9));
    this->stance = std::bit_cast<double>(read8byteInt_BE(pack.bytes.data()+17));
    this->xyz.z = std::bit_cast<double>(read8byteInt_BE(pack.bytes.data()+25));
}

uint8_t p_Player_Pos::getID(){
    return 0x0B;
}

Packet p_Player_Pos::serialize(){
    Packet pack(std::vector<uint8_t>(34),this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from64bit(pack.bytes.data()+1, this->xyz.x);
    writeBytes_from64bit(pack.bytes.data()+9, this->xyz.y);
    writeBytes_from64bit(pack.bytes.data()+17, this->stance);
    writeBytes_from64bit(pack.bytes.data()+25, this->xyz.z);
    pack.bytes[33] = this->getOnGround();
    return pack;
}

v2<float> p_Player_Look::getYP(){
    return this->yp;
}

p_Player_Look::p_Player_Look(PacketReturnInfo inf, bool on_ground, v2<float> yp) :
    p_PlayerBase(inf, on_ground),
    yp(yp){
}

p_Player_Look::p_Player_Look(Packet pack) :
    p_PlayerBase(pack.info, pack.bytes[9]){
    if(pack.bytes.size()!=10){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
    this->yp.x = read4byteInt_BE(pack.bytes.data()+1);
    this->yp.z = read4byteInt_BE(pack.bytes.data()+5);
}

uint8_t p_Player_Look::getID(){
    return 0x0C;
}

Packet p_Player_Look::serialize(){
    Packet pack = Packet(std::vector<uint8_t>(10),this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes.data()+1, this->yp.x);
    writeBytes_from32bit(pack.bytes.data()+5, this->yp.z);
    pack.bytes[9] = this->getOnGround();
    return pack;
}

p_Player_PosLook::p_Player_PosLook(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance, v2<float> yp) :
    p_Player_Pos(inf, on_ground, xyz, stance),
    yp(yp){
}

p_Player_PosLook::p_Player_PosLook(Packet pack) :
    p_Player_Pos(pack.info, pack.bytes[41], v3<double>(read8byteInt_BE(pack.bytes.data()+1), read8byteInt_BE(pack.bytes.data()+9), read8byteInt_BE(pack.bytes.data()+17)), read8byteInt_BE(pack.bytes.data()+25)){
    if(pack.bytes.size()!=42){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
    this->yp = v2<float>(read4byteInt_BE(pack.bytes.data()+33), read4byteInt_BE(pack.bytes.data()+37));
}

uint8_t p_Player_PosLook::getID(){
    return 0x0D;
}

Packet p_Player_PosLook::serialize(){
    Packet pack(std::vector<uint8_t>(42), this->getInfo());
    pack.bytes[0] = this->getID();
    v3<double> xyz;
    xyz = this->getXYZ(); 
    writeBytes_from64bit(pack.bytes.data()+1, xyz.x);
    writeBytes_from64bit(pack.bytes.data()+9, this->getStance());
    writeBytes_from64bit(pack.bytes.data()+17, xyz.y);
    writeBytes_from64bit(pack.bytes.data()+25, xyz.z);
    writeBytes_fromV2(pack.bytes.data()+33, this->yp);
    pack.bytes[41] = this->getOnGround();
    return pack;
}

p_Player_Dig::p_Player_Dig(Packet pack):
    DsPacket(pack.info),
    status((P_DigStatus)pack.bytes[1]),
    x(read4byteInt_BE(pack.bytes.data()+2)),
    y(pack.bytes[6]),
    z(read4byteInt_BE(pack.bytes.data()+7)),
    face((Block_Face)pack.bytes[11]){
    if(pack.bytes.size()!=12){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
};

uint8_t p_Player_Dig::getID(){
    return 0x0E;
}

PacketCategories p_Player_Dig::getType(){
    return CHUNK_BLOCK;
}

Packet p_Player_Dig::serialize(){
    Packet pack(std::vector<uint8_t>(12),this->getInfo());
    pack.bytes[0] = this->getID();
    pack.bytes[1] = this->status;
    writeBytes_from32bit(pack.bytes.data()+2, this->x);
    pack.bytes[6] = this->y;
    writeBytes_from32bit(pack.bytes.data()+7, this->z);
    pack.bytes[7] = this->face;
    return pack;
}

p_Player_BlockPlace::p_Player_BlockPlace(Packet pack) :
    DsPacket(pack.info),
    x(read4byteInt_BE(pack.bytes.data()+1)),
    y(pack.bytes[5]),
    z(read4byteInt_BE(pack.bytes.data()+6)),
    face((Block_Face)pack.bytes[10]),
    block_id(read2byteInt_BE(pack.bytes.data()+12)){
    if(pack.bytes.size()!=13){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
}

uint8_t p_Player_BlockPlace::getID(){
    return 0x0F;
}

PacketCategories p_Player_BlockPlace::getType(){
    return CHUNK_BLOCK;
}

Packet p_Player_BlockPlace::serialize(){
    return Packet(std::vector<uint8_t>(0),this->getInfo());
}

p_Player_BlockPlaceItem::p_Player_BlockPlaceItem(Packet pack) :
    DsPacket(pack.info),
    x(read4byteInt_BE(pack.bytes.data()+1)),
    y(pack.bytes[5]),
    z(read4byteInt_BE(pack.bytes.data()+6)),
    face((Block_Face)pack.bytes[10]),
    block_id(read2byteInt_BE(pack.bytes.data()+12)),
    amount(pack.bytes[14]),
    damage(read2byteInt_BE(pack.bytes.data()+15)){
    if(pack.bytes.size()!=16){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
}

uint8_t p_Player_BlockPlaceItem::getID(){
    return 0x0F;
}

PacketCategories p_Player_BlockPlaceItem::getType(){
    return CHUNK_BLOCK;
}

Packet p_Player_BlockPlaceItem::serialize(){
    return Packet(std::vector<uint8_t>(0), this->getInfo());
}

p_Player_HoldChange::p_Player_HoldChange(Packet pack):
    DsPacket(pack.info),
    slot(read2byteInt_BE(pack.bytes.data()+1)){
    if(pack.bytes.size()!=3){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
}

uint8_t p_Player_HoldChange::getID(){
    return 0x11;
}

PacketCategories p_Player_HoldChange::getType(){
    return PLAYER;
}

Packet p_Player_HoldChange::serialize(){
    return Packet(std::vector<uint8_t>(0),this->getInfo());
}

p_Player_UseBed::p_Player_UseBed(PacketReturnInfo inf, int32_t eid, v3<int32_t> xyz):
    eid(eid),
    x(xyz.x),
    z(xyz.z),
    y(xyz.y){
    this->setInfo(inf);
}

uint8_t p_Player_UseBed::getID(){
    return 0x11;
}

PacketCategories p_Player_UseBed::getType(){
    return PLAYER;
}

Packet p_Player_UseBed::serialize(){
    Packet pack(std::vector<uint8_t>(15),this->getInfo());
    pack.bytes[0] = this->getID();
    pack.bytes[1] = 0x00;
    writeBytes_from32bit(pack.bytes.data()+2, this->x);
    pack.bytes[6] = this->y;
    writeBytes_from32bit(pack.bytes.data()+7,this->z);
    return pack;
}

p_Player_updateHp::p_Player_updateHp(PacketReturnInfo inf, uint16_t new_hp) :
    DsPacket(inf),
    new_hp(new_hp){
}

uint8_t p_Player_updateHp::getID(){
    return 0x08;
}

PacketCategories p_Player_updateHp::getType(){
    return PLAYER;
}

Packet p_Player_updateHp::serialize(){
    Packet pack(std::vector<uint8_t>(3),this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from16bit(pack.bytes.data()+1, this->new_hp);
    return pack;
}

p_Player_Respawn::p_Player_Respawn(PacketReturnInfo inf, int8_t dimension) :
    DsPacket(inf),
    dimension(dimension){
}

p_Player_Respawn::p_Player_Respawn(Packet pack) :
    DsPacket(pack.info){
    if(pack.bytes.size()!=2){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{:0x} Packet invalid!", (int)pack.bytes[0]);
        return;
    }
    this->dimension = pack.bytes[1];
}

uint8_t p_Player_Respawn::getID(){
    return 0x09;
}

PacketCategories p_Player_Respawn::getType(){
    return PLAYER;
}

Packet p_Player_Respawn::serialize(){
    Packet pack(std::vector<uint8_t>(2), this->getInfo());
    pack.bytes[0] = this->getID();
    pack.bytes[1] = this->getID();
    return pack;
}