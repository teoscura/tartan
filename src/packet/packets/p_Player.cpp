#include "p_Player.hpp"

#include <bit>
#include <cstdint>
#include <memory>

#include "../../util/byteops.hpp"
#include "packet.hpp"

bool p_PlayerBase::getOnGround(){
    return this->on_ground;
}

p_PlayerBase::p_PlayerBase(PacketReturnInfo inf, bool on_ground) :
    on_ground(on_ground),
    DsPacket(inf){
}

p_PlayerBase::p_PlayerBase(std::unique_ptr<Packet> pack):
    DsPacket(pack->info){
    this->on_ground = pack->bytes[pack->size-1];
}

uint8_t p_PlayerBase::getID(){
    return 0x0A;
}

PacketCategories p_PlayerBase::getType(){
    return PLAYER;
}

std::unique_ptr<Packet> p_PlayerBase::serialize(){
    std::unique_ptr<Packet> result = std::make_unique<Packet>();
    result->bytes = new uint8_t[2];
    result->info = this->getInfo();
    result->bytes[0] = this->getID();
    result->bytes[1] = this->on_ground;
    result->size = 2;
    return result;
}

p_PlayerBase::~p_PlayerBase(){
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

p_Player_Pos::p_Player_Pos(std::unique_ptr<Packet> pack) : 
    p_PlayerBase(pack->info, pack->bytes[33]){
    this->xyz.x = std::bit_cast<double>(read8byteInt_BE(pack->bytes+1));
    this->xyz.y = std::bit_cast<double>(read8byteInt_BE(pack->bytes+9));
    this->stance = std::bit_cast<double>(read8byteInt_BE(pack->bytes+17));
    this->xyz.z = std::bit_cast<double>(read8byteInt_BE(pack->bytes+25));
}

uint8_t p_Player_Pos::getID(){
    return 0x0B;
}

std::unique_ptr<Packet> p_Player_Pos::serialize(){
    Packet pack;
    pack.info = this->getInfo();
    pack.bytes = new uint8_t[34];
    pack.bytes[0] = this->getID();
    writeBytes_from64bit(pack.bytes+1, this->xyz.x);
    writeBytes_from64bit(pack.bytes+9, this->xyz.y);
    writeBytes_from64bit(pack.bytes+17, this->stance);
    writeBytes_from64bit(pack.bytes+25, this->xyz.z);
    pack.bytes[33] = this->getOnGround();
    return std::make_unique<Packet>(pack);
}

p_Player_Pos::~p_Player_Pos(){
}

v2<float> p_Player_Look::getYP(){
    return this->yp;
}

p_Player_Look::p_Player_Look(PacketReturnInfo inf, bool on_ground, v2<float> yp) :
    p_PlayerBase(inf, on_ground),
    yp(yp){
}

p_Player_Look::p_Player_Look(std::unique_ptr<Packet> pack) :
    p_PlayerBase(pack->info, pack->bytes[9]){
    this->yp.x = (float)std::bit_cast<double>(read8byteInt_BE(pack->bytes+1));
    this->yp.z = (float)std::bit_cast<double>(read8byteInt_BE(pack->bytes+5));
}

uint8_t p_Player_Look::getID(){
    return 0x0C;
}

std::unique_ptr<Packet> p_Player_Look::serialize(){
    Packet pack;
    pack.info = this->getInfo();
    pack.size = 10;
    pack.bytes = new uint8_t[10];
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->yp.x);
    writeBytes_from32bit(pack.bytes+5, this->yp.z);
    pack.bytes[9] = this->getOnGround();
    return std::make_unique<Packet>(pack);
}

p_Player_Look::~p_Player_Look(){
}

p_Player_PosLook::p_Player_PosLook(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance, v2<float> yp) :
    p_Player_Pos(inf, on_ground, xyz, stance),
    p_Player_Look(inf, on_ground, yp){
}

p_Player_PosLook::p_Player_PosLook(std::unique_ptr<Packet> pack) :
    p_Player_Look(pack->info, pack->bytes[41], v2<float>(read4byteInt_BE(pack->bytes+33), read4byteInt_BE(pack->bytes+37))),
    p_Player_Pos(pack->info, pack->bytes[41], v3<double>(read8byteInt_BE(pack->bytes+1), read8byteInt_BE(pack->bytes+9), read8byteInt_BE(pack->bytes+17)), read8byteInt_BE(pack->bytes+25)){
}

uint8_t p_Player_PosLook::getID(){
    return 0x0D;
}

std::unique_ptr<Packet> p_Player_PosLook::serialize(){
    Packet pack;
    pack.info = this->p_Player_Look::getInfo();
    pack.bytes = new uint8_t[42];
    pack.bytes[0] = this->getID();
    v3<double> xyz; v2<float> yp;
    xyz = this->getXYZ(); yp = this->getYP();
    writeBytes_from64bit(pack.bytes+1, xyz.x);
    writeBytes_from64bit(pack.bytes+9, this->getStance());
    writeBytes_from64bit(pack.bytes+17, xyz.y);
    writeBytes_from64bit(pack.bytes+25, xyz.z);
    writeBytes_from32bit(pack.bytes+33, yp.x);
    writeBytes_from32bit(pack.bytes+37, yp.z);
    pack.bytes[41] = this->p_Player_Look::getOnGround();
    return std::make_unique<Packet>(pack);
}

p_Player_PosLook::~p_Player_PosLook(){
}

p_Player_Dig::p_Player_Dig(std::unique_ptr<Packet> pack):
    DsPacket(pack->info),
    status((P_DigStatus)pack->bytes[1]),
    x(read4byteInt_BE(pack->bytes+2)),
    y(pack->bytes[6]),
    z(read4byteInt_BE(pack->bytes+7)),
    face((Block_Face)pack->bytes[11]){
};

uint8_t p_Player_Dig::getID(){
    return 0x0E;
}

PacketCategories p_Player_Dig::getType(){
    return CHUNK_BLOCK;
}

std::unique_ptr<Packet> p_Player_Dig::serialize(){
    Packet pack;    
    pack.info = this->getInfo();
    pack.size = 12;
    pack.bytes = new uint8_t[12];
    pack.bytes[0] = this->getID();
    pack.bytes[1] = this->status;
    writeBytes_from32bit(pack.bytes+2, this->x);
    pack.bytes[6] = this->y;
    writeBytes_from32bit(pack.bytes+7, this->z);
    pack.bytes[7] = this->face;
    return std::make_unique<Packet>(pack);
}

p_Player_Dig::~p_Player_Dig(){
}

p_Player_BlockPlace::p_Player_BlockPlace(std::unique_ptr<Packet> pack) :
    DsPacket(pack->info),
    x(read4byteInt_BE(pack->bytes+1)),
    y(pack->bytes[5]),
    z(read4byteInt_BE(pack->bytes+6)),
    face((Block_Face)pack->bytes[10]),
    block_id(read2byteInt_BE(pack->bytes+12)){
}

uint8_t p_Player_BlockPlace::getID(){
    return 0x0F;
}

PacketCategories p_Player_BlockPlace::getType(){
    return CHUNK_BLOCK;
}

std::unique_ptr<Packet> p_Player_BlockPlace::serialize(){
    return nullptr;
}

p_Player_BlockPlace::~p_Player_BlockPlace(){
}

p_Player_BlockPlaceItem::p_Player_BlockPlaceItem(std::unique_ptr<Packet> pack) :
    DsPacket(pack->info),
    x(read4byteInt_BE(pack->bytes+1)),
    y(pack->bytes[5]),
    z(read4byteInt_BE(pack->bytes+6)),
    face((Block_Face)pack->bytes[10]),
    block_id(read2byteInt_BE(pack->bytes+12)),
    amount(pack->bytes[14]),
    damage(read2byteInt_BE(pack->bytes+15)){
}

uint8_t p_Player_BlockPlaceItem::getID(){
    return 0x0F;
}

PacketCategories p_Player_BlockPlaceItem::getType(){
    return CHUNK_BLOCK;
}

std::unique_ptr<Packet> p_Player_BlockPlaceItem::serialize(){
    return nullptr;
}

p_Player_BlockPlaceItem::~p_Player_BlockPlaceItem(){
}

p_Player_HoldChange::p_Player_HoldChange(std::unique_ptr<Packet> pack):
    DsPacket(pack->info),
    slot(read2byteInt_BE(pack->bytes+1)){
}

uint8_t p_Player_HoldChange::getID(){
    return 0x11;
}

PacketCategories p_Player_HoldChange::getType(){
    return PLAYER;
}

std::unique_ptr<Packet> p_Player_HoldChange::serialize(){
    return nullptr;
}

p_Player_HoldChange::~p_Player_HoldChange(){
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

std::unique_ptr<Packet> p_Player_UseBed::serialize(){
    Packet pack;
    pack.info = this->getInfo();
    pack.size = 0x0F;
    pack.bytes = new uint8_t[15];
    pack.bytes[0] = this->getID();
    pack.bytes[1] = 0x00;
    writeBytes_from32bit(pack.bytes+2, this->x);
    pack.bytes[6] = this->y;
    writeBytes_from32bit(pack.bytes+7,this->z);
    return std::make_unique<Packet>(pack);
}

p_Player_UseBed::~p_Player_UseBed(){
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

std::unique_ptr<Packet> p_Player_updateHp::serialize(){
    Packet pack;
    pack.info = this->getInfo();
    pack.size = 3;
    pack.bytes = new uint8_t[3];
    pack.bytes[0] = this->getID();
    writeBytes_from16bit(pack.bytes+1, this->new_hp);
    return std::make_unique<Packet>(pack);
}

p_Player_updateHp::~p_Player_updateHp(){
}