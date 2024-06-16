#include "p_Entity.hpp"

#include <cstdint>


#include "../../util/byteops.hpp"
#include "packet.hpp"

p_EntityBase::p_EntityBase(PacketReturnInfo inf, uint32_t eid) :
    DsPacket(inf),
    eid(eid){
}

uint32_t p_EntityBase::getEID(){
    return this->getEID();
}

uint8_t p_EntityBase::getID(){
    return 0x1E;
}

PacketCategories p_EntityBase::getType(){
    return ENTITY;
}

Packet p_EntityBase::serialize(){
    Packet pack(new uint8_t[5], 5, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->eid);
    return pack;
}

p_EntityBase::~p_EntityBase(){
}

p_Entity_Equipment::p_Entity_Equipment(PacketReturnInfo inf, uint32_t eid, uint16_t slot, int16_t item_id, uint16_t data) :
    p_EntityBase(inf, eid),
    slot(slot),
    item_id(item_id),
    data(data){
}

uint8_t p_Entity_Equipment::getID(){
    return 0x05;
}

PacketCategories p_Entity_Equipment::getType(){
    return ENTITY;
}

Packet p_Entity_Equipment::serialize(){
    Packet pack(new uint8_t[11], 11, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_from16bit(pack.bytes+5, this->slot);
    writeBytes_from16bit(pack.bytes+7, this->item_id);
    writeBytes_from16bit(pack.bytes+9, this->data);
    return pack;
}

p_Entity_Equipment::~p_Entity_Equipment(){
}

p_Entity_useEntity::p_Entity_useEntity(PacketReturnInfo inf, uint32_t eid, uint32_t target, bool leftclick):
    p_EntityBase(inf, eid),
    target(target),
    leftclick(leftclick){
}

uint8_t p_Entity_useEntity::getID(){
    return 0x07;
}

PacketCategories p_Entity_useEntity::getType(){
    return ENTITY;
}

Packet p_Entity_useEntity::serialize(){
    Packet pack(new uint8_t[10], 10, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_from32bit(pack.bytes+5, this->target);
    pack.bytes[9] = this->leftclick;
    return pack;
}

p_Entity_useEntity::~p_Entity_useEntity(){
}

p_Entity_Animation::p_Entity_Animation(PacketReturnInfo inf, uint32_t eid, uint8_t animation) : 
    p_EntityBase(inf, eid),
    animation(animation){
}

uint8_t p_Entity_Animation::getID(){
    return 0x12;
}

PacketCategories p_Entity_Animation::getType(){
    return ENTITY;
}

Packet p_Entity_Animation::serialize(){
    Packet pack(new uint8_t[6], 6, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    pack.bytes[5] = this->animation;
    return pack;
}

p_Entity_Animation::~p_Entity_Animation(){
}

p_Entity_Action::p_Entity_Action(PacketReturnInfo inf, uint32_t eid, uint8_t action) :
    p_EntityBase(inf, eid),
    action(action){
}

uint8_t p_Entity_Action::getID(){
    return 0x13;
}

PacketCategories p_Entity_Action::getType(){
    return ENTITY;
}

Packet p_Entity_Action::serialize(){
    Packet pack(new uint8_t[6], 6, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    pack.bytes[5] = this->action;
    return pack;
}

p_Entity_Action::~p_Entity_Action(){
}

p_Entity_NamedSpawn::p_Entity_NamedSpawn(PacketReturnInfo inf, uint32_t eid, std::u16string e_name, v3<int32_t> xyz, v2<int8_t> yp, uint8_t held_item) : 
    p_EntityBase(inf, eid),
    e_name(e_name),
    xyz(xyz),
    yp(yp),
    held_item(held_item){
}

uint8_t p_Entity_NamedSpawn::getID(){
    return 0x14;
}

PacketCategories p_Entity_NamedSpawn::getType(){
    return ENTITY;
}

Packet p_Entity_NamedSpawn::serialize(){
    Packet pack(new uint8_t[23+2*e_name.length()], 23+2*e_name.length(), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from16bit(pack.bytes+1, this->e_name.length());
    writeBytes_fromWstring(pack.bytes+3, this->e_name);
    writeBytes_fromV3(pack.bytes+3+2*e_name.length(), this->xyz);
    writeBytes_fromV2(pack.bytes+15+2*e_name.length(), this->yp);
    pack.bytes[17+2*e_name.length()] = held_item;
    return pack;
}

p_Entity_NamedSpawn::~p_Entity_NamedSpawn(){
}

p_Entity_SpawnGroundItem::p_Entity_SpawnGroundItem(PacketReturnInfo inf, uint32_t eid, uint16_t item_id, uint8_t count, uint16_t damage_or_metadata, v3<int32_t> xyz, v3<int8_t> rpr) : 
    p_EntityBase(inf, eid),
    item_id(item_id),
    count(count),
    damage_or_metadata(damage_or_metadata),
    xyz(xyz),
    rpr(rpr){
}

uint8_t p_Entity_SpawnGroundItem::getID(){
    return 0x15;
}

PacketCategories p_Entity_SpawnGroundItem::getType(){
    return ENTITY;
}

Packet p_Entity_SpawnGroundItem::serialize(){
    Packet pack(new uint8_t[25], 25, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_from16bit(pack.bytes+5, this->item_id);
    pack.bytes[7] = this->count;
    writeBytes_from16bit(pack.bytes+8, this->damage_or_metadata);
    writeBytes_fromV3(pack.bytes+10, this->xyz);
    writeBytes_fromV3(pack.bytes+22, this->rpr);
    return pack;
}

p_Entity_SpawnGroundItem::~p_Entity_SpawnGroundItem(){
}

p_Entity_Collect::p_Entity_Collect(PacketReturnInfo inf, uint32_t eid, uint32_t collector_id) :
    p_EntityBase(inf, eid),
    collector_id(collector_id){
}

uint8_t p_Entity_Collect::getID(){
    return 0x16;
}

PacketCategories p_Entity_Collect::getType(){
    return ENTITY;
}

Packet p_Entity_Collect::serialize(){
    Packet pack(new uint8_t[9], 9, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_from32bit(pack.bytes+5, this->collector_id);
    return pack;
}

p_Entity_Collect::~p_Entity_Collect(){
}

p_Entity_SpawnVehicle::p_Entity_SpawnVehicle(PacketReturnInfo inf, uint32_t eid, uint8_t type, v3<int32_t> xyz, int32_t unknown, v3<int16_t> unknowns) :
    p_EntityBase(inf, eid),
    type(type),
    xyz(xyz),
    unknown(unknown),
    unknowns(unknowns){
}

uint8_t p_Entity_SpawnVehicle::getID(){
    return 0x17;
}

PacketCategories p_Entity_SpawnVehicle::getType(){
    return ENTITY;
}

Packet p_Entity_SpawnVehicle::serialize(){
    Packet pack(new uint8_t[28], 28, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    pack.bytes[5] = this->type;
    writeBytes_fromV3(pack.bytes+6, this->xyz);
    writeBytes_from32bit(pack.bytes+18, this->unknown);
    writeBytes_fromV3(pack.bytes+22, this->unknowns);
    return pack;
}

p_Entity_SpawnVehicle::~p_Entity_SpawnVehicle(){
}

p_Entity_SpawnMob::p_Entity_SpawnMob(PacketReturnInfo inf, uint32_t eid, uint8_t mob_type, v3<int32_t> xyz, v2<int8_t> yp, std::vector<uint8_t> metadata) : 
    p_EntityBase(inf, eid),
    mob_type(mob_type),
    xyz(xyz),
    yp(yp),
    metadata(metadata){
}

uint8_t p_Entity_SpawnMob::getID(){
    return 0x18;
}

PacketCategories p_Entity_SpawnMob::getType(){
    return ENTITY;
}

Packet p_Entity_SpawnMob::serialize(){
    Packet pack(new uint8_t[20+metadata.size()], 20+metadata.size(), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, getEID());
    pack.bytes[5] = this->mob_type;
    writeBytes_fromV3(pack.bytes+6, this->xyz);
    writeBytes_fromV2(pack.bytes+18, this->yp);
    writeBytes_fromVector(pack.bytes+20, this->metadata);
    return pack;
}

p_Entity_SpawnMob::~p_Entity_SpawnMob(){
}

p_Entity_Painting::p_Entity_Painting(PacketReturnInfo inf, uint32_t eid, std::u16string painting_name, v3<int32_t> center_xyz, PaintingDirections direction) : 
    p_EntityBase(inf, eid),
    painting_name(painting_name),
    center_xyz(center_xyz),
    direction(direction){
}

uint8_t p_Entity_Painting::getID(){
    return 0x19;
}

PacketCategories p_Entity_Painting::getType(){
    return ENTITY;
}

Packet p_Entity_Painting::serialize(){
    Packet pack(new uint8_t[22+2*painting_name.length()], 22+2*painting_name.length(), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_from16bit(pack.bytes+5, this->painting_name.length());
    writeBytes_fromWstring(pack.bytes+7, this->painting_name);
    writeBytes_fromV3(pack.bytes+9+2*painting_name.length(), this->center_xyz);
    writeBytes_from32bit(pack.bytes+21+2*painting_name.length(), this->direction);
    return pack;
}

p_Entity_Painting::~p_Entity_Painting(){
}

p_Entity_Velocity::p_Entity_Velocity(PacketReturnInfo inf, uint32_t eid, v3<int16_t> v_xyz) : 
    p_EntityBase(inf, eid),
    v_xyz(v_xyz){
}

uint8_t p_Entity_Velocity::getID(){
    return 0x1C;
}

PacketCategories p_Entity_Velocity::getType(){
    return ENTITY;
}

Packet p_Entity_Velocity::serialize(){
    Packet pack(new uint8_t[11], 11, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_fromV3(pack.bytes+5, v_xyz);
    return pack;
}

p_Entity_Velocity::~p_Entity_Velocity(){
}

p_Entity_Delete::p_Entity_Delete(PacketReturnInfo inf, uint32_t eid) :
    p_EntityBase(inf, eid){
}

uint8_t p_Entity_Delete::getID(){
    return 0x1D;
}

PacketCategories p_Entity_Delete::getType(){
    return ENTITY;
}

Packet p_Entity_Delete::serialize(){
    Packet pack(new uint8_t[5], 5, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    return pack;
}

p_Entity_Delete::~p_Entity_Delete(){
}

p_Entity_RelativeMove::p_Entity_RelativeMove(PacketReturnInfo inf, uint32_t eid, v3<int8_t> d_xyz) :
    p_EntityBase(inf, eid),
    d_xyz(d_xyz){
}

v3<int8_t> p_Entity_RelativeMove::getXYZ(){
    return this->d_xyz;
}

uint8_t p_Entity_RelativeMove::getID(){
    return 0x1F;
}

PacketCategories p_Entity_RelativeMove::getType(){
    return ENTITY;
}

Packet p_Entity_RelativeMove::serialize(){
    Packet pack(new uint8_t[8], 8, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_fromV3(pack.bytes+5, this->d_xyz);
    return pack;
}

p_Entity_RelativeMove::~p_Entity_RelativeMove(){
}

p_Entity_Look::p_Entity_Look(PacketReturnInfo inf, uint32_t eid, v2<int8_t> yp) :
    p_EntityBase(inf, eid),
    yp(yp){
}

v2<int8_t> p_Entity_Look::getYP(){
    return this->yp;
}

uint8_t p_Entity_Look::getID(){
    return 0x20;
}

PacketCategories p_Entity_Look::getType(){
    return ENTITY;
}

Packet p_Entity_Look::serialize(){
    Packet pack(new uint8_t[7], 7, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_fromV2(pack.bytes+5, this->yp);
    return pack;
}

p_Entity_Look::~p_Entity_Look(){
}

p_Entity_RelMoveLook::p_Entity_RelMoveLook(PacketReturnInfo inf, uint32_t eid, v3<int8_t> d_xyz, v2<int8_t> yp) :
    p_Entity_Look(inf, eid, yp),
    p_Entity_RelativeMove(inf, eid, d_xyz){
}

uint8_t p_Entity_RelMoveLook::getID(){
    return 0x21;
}

PacketCategories p_Entity_RelMoveLook::getType(){
    return ENTITY;
}

Packet p_Entity_RelMoveLook::serialize(){
    Packet pack(new uint8_t[10], 10, this->p_Entity_Look::getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->p_Entity_Look::getEID());
    writeBytes_fromV3(pack.bytes+5, this->getXYZ());
    writeBytes_fromV2(pack.bytes+8, this->getYP());
    return pack;
}

p_Entity_RelMoveLook::~p_Entity_RelMoveLook(){
}

p_Entity_Teleport::p_Entity_Teleport(PacketReturnInfo inf, uint32_t eid, v3<int32_t> xyz, v2<int8_t> yp) :
    p_Entity_Look(inf, eid, yp),
    xyz(xyz){
}

uint8_t p_Entity_Teleport::getID(){
    return 0x22;
}

PacketCategories p_Entity_Teleport::getType(){
    return ENTITY;
}

Packet p_Entity_Teleport::serialize(){
    Packet pack(new uint8_t[19],19,this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_fromV3(pack.bytes+5, xyz);
    writeBytes_fromV2(pack.bytes+17, this->getYP());
    return pack;
}

p_Entity_Teleport::~p_Entity_Teleport(){    
}

p_Entity_Status::p_Entity_Status(PacketReturnInfo inf, uint32_t eid, uint8_t status): 
    p_EntityBase(inf, eid),
    status(status){
}

uint8_t p_Entity_Status::getID(){
    return 0x26;
}

PacketCategories p_Entity_Status::getType(){
    return ENTITY;
}

Packet p_Entity_Status::serialize(){
    Packet pack(new uint8_t[6], 6, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    pack.bytes[5] = this->status;
    return pack;
}

p_Entity_Status::~p_Entity_Status(){
}

p_Entity_Attach::p_Entity_Attach(PacketReturnInfo inf, uint32_t eid, uint32_t vehicle_eid):
    p_EntityBase(inf, eid),
    vehicle_eid(vehicle_eid){
}

uint8_t p_Entity_Attach::getID(){
    return 0x27;
}

PacketCategories p_Entity_Attach::getType(){
    return ENTITY;
}

Packet p_Entity_Attach::serialize(){
    Packet pack(new uint8_t[9], 9, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    writeBytes_from32bit(pack.bytes+5, this->vehicle_eid);
    return pack;
}

p_Entity_Attach::~p_Entity_Attach(){
}

p_Entity_Metadata::p_Entity_Metadata(PacketReturnInfo inf, uint32_t eid, std::vector<uint8_t> bytes) :
    p_EntityBase(inf, eid),
    bytes(bytes){
}

uint8_t p_Entity_Metadata::getID(){
    return 0x28;
}

PacketCategories p_Entity_Metadata::getType(){
    return ENTITY;
}

Packet p_Entity_Metadata::serialize(){
    Packet pack(new uint8_t[5+bytes.size()], 5+bytes.size(), this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getID());
    writeBytes_fromVector(pack.bytes+5, this->bytes);
    return pack;
}

p_Entity_Metadata::~p_Entity_Metadata(){ 
}

p_Entity_Thunderbolt::p_Entity_Thunderbolt(PacketReturnInfo inf, uint32_t eid, v3<int32_t> xyz) :
    p_EntityBase(inf, eid),
    xyz(xyz){
}

uint8_t  p_Entity_Thunderbolt::getID(){
    return 0x47;
}

PacketCategories p_Entity_Thunderbolt::getType(){
    return ENTITY;
}

Packet p_Entity_Thunderbolt::serialize(){
    Packet pack(new uint8_t[18], 18, this->getInfo());
    pack.bytes[0] = this->getID();
    writeBytes_from32bit(pack.bytes+1, this->getEID());
    pack.bytes[5] = this->t;
    writeBytes_fromV3(pack.bytes+6, this->xyz);
    return pack;
}

p_Entity_Thunderbolt::~p_Entity_Thunderbolt(){
}