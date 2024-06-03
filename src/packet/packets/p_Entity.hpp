#ifndef PP_ENTITY_ALL
#define PP_ENTITY_ALL

#include <cstdint>
#include <vector>
#include <string>

#include "../../minecraft/world/vector.hpp"
#include "packet.hpp"


class p_EntityBase : public DsPacket{ /* 0x1E */
    private:
        uint32_t eid;
    public:
        p_EntityBase(PacketReturnInfo inf, uint32_t eid);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_EntityBase() override;
};


class p_Entity_Equipment : public p_EntityBase { /* 0x05 */
    private:
        uint16_t slot;
        int16_t item_id; /* -1 for empty slot. */
        uint16_t data;
    public:
        p_Entity_Equipment(PacketReturnInfo inf, uint32_t eid, 
                           uint16_t slot, int16_t item_id, 
                           uint16_t data);
        
        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Equipment() override;
};

class p_Entity_useEntity : public p_EntityBase { /* 0x07 */
    private:
        uint32_t target;
        bool leftclick;
    public:
        p_Entity_useEntity(PacketReturnInfo inf, uint32_t eid, uint32_t target, bool leftclick);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_useEntity() override;
};

class p_Entity_Animation : public p_EntityBase { /* 0x12 */
    private:
        uint8_t animation;
    public:
        p_Entity_Animation(PacketReturnInfo inf, uint32_t eid, uint8_t animation);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Animation() override;
};

class p_Entity_Action : public p_EntityBase { /* 0x13 */
    private:
        uint8_t action;
    public:
        p_Entity_Action(PacketReturnInfo inf, uint32_t eid, uint8_t action);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Action() override;
};

class p_Entity_NamedSpawn : public p_EntityBase { /* 0x14 */
    private:
        std::u16string e_name;
        v3<int32_t> xyz;
        v2<uint8_t> yp;
        uint8_t held_item;
    public:
        p_Entity_NamedSpawn(PacketReturnInfo inf, uint32_t eid, 
                            std::u16string e_name, v3<int32_t> xyz, 
                            v2<uint8_t> yp);
        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_NamedSpawn() override;
};

class p_Entity_SpawnGroundItem : public p_EntityBase { /* 0x15 */
    private:
        uint16_t item_id;
        uint8_t count;
        uint16_t damage_or_metadata;
        v3<int32_t> xyz;
        v3<uint8_t> rpr;
    public:
        p_Entity_SpawnGroundItem(PacketReturnInfo inf, uint32_t eid,
                                 uint16_t item_id, uint8_t count,
                                 uint16_t damage_or_metadata,
                                 v3<int32_t> xyz, v3<int32_t> rpr);
        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_SpawnGroundItem() override;
};

//TODO code mobspawn

enum PaintingDirections{
    NEGZ = 0x00,
    NEGX,
    POSZ,
    POSX,
};

class p_Entity_Painting : p_EntityBase { /* 0x19 */
    private:
        std::u16string painting_name;
        v3<int32_t> center_xyz;
        PaintingDirections direction;
    public:
        p_Entity_Painting(PacketReturnInfo inf, uint32_t eid, 
                          std::u16string painting_name, v3<int32_t> center_xyz, 
                          PaintingDirections direction);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Painting() override;
};

class p_Entity_Velocity : public p_EntityBase { /* 0x1C */
    private:
        v3<int16_t> v_xyz;
    public:
        p_Entity_Velocity(PacketReturnInfo inf, uint32_t eid, v3<int16_t> v_xyz);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Velocity() override;
};

class p_Entity_Delete : public p_EntityBase { /* 0x1D */
    public:
        p_Entity_Delete(PacketReturnInfo inf, uint32_t eid);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Delete() override;   
};

class p_Entity_RelativeMove : public p_EntityBase { /* 0x1F */
    private:
        v3<int8_t> d_xyz;
    public:
        p_Entity_RelativeMove(PacketReturnInfo inf, uint32_t eid, v3<int8_t> d_xyz);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_RelativeMove() override;
};

class p_Entity_Look : public p_EntityBase{ /* 0x20 */
    private:    
        v2<uint8_t> yp;
    public:
        p_Entity_Look(PacketReturnInfo inf, uint32_t eid, v2<uint8_t> yp);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Look() override;
};

class p_Entity_RelMoveLook : public p_Entity_RelativeMove, public p_Entity_Look { /* 0x21 */
    public:
        p_Entity_RelMoveLook(PacketReturnInfo inf, uint32_t eid, v3<int8_t> d_xyz, v2<uint8_t> yp);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_RelMoveLook() override;
};

class p_Entity_Teleport : public p_Entity_RelMoveLook { /* 0x22 */
    public:
        p_Entity_Teleport(PacketReturnInfo inf, uint32_t eid, v3<int8_t> d_xyz, v2<uint8_t> yp);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Teleport() override;
};

class p_Entity_Status : public p_EntityBase{ /* 0x26 */
    private: 
        uint8_t status;
    public:
        p_Entity_Status(PacketReturnInfo inf, uint32_t eid, uint8_t status);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Status() override;
};

class p_Entity_Attach : public p_EntityBase { /* 0x27 */
    private:
        uint32_t vehicle_eid;
    public:
        p_Entity_Attach(PacketReturnInfo inf, uint32_t eid, uint32_t vehicle_eid);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Attach() override;
};

class p_Entity_Metadata : public p_EntityBase { /* 0x28 */
    private:
        std::vector<uint8_t> bytes;
    public:
        p_Entity_Metadata(PacketReturnInfo inf, uint32_t eid, uint32_t vehicle_eid);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_Entity_Metadata() override;
};

#endif