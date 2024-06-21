#ifndef PP_PLAYER_ALL
#define PP_PLAYER_ALL

#include <cstdint>

#include "../../minecraft/world/vector.hpp"
#include "packet.hpp"

class p_KeepAlive: public DsPacket{ /* 0x00 */
    public:
        p_KeepAlive(Packet pack);
        uint8_t getID() override;
        PacketCategories getType() override;
        ~p_KeepAlive() override = default;
};

class p_SpawnPosition : public DsPacket { /* 0x06 */
    private:
        v3<int32_t> xyz;
    public:    
        p_SpawnPosition(PacketReturnInfo inf, v3<int32_t> coords);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_SpawnPosition() override = default;
};

class p_Player_updateHp : DsPacket{ /* 0x08 */
    private:
        uint16_t new_hp;
    public:
        p_Player_updateHp(PacketReturnInfo inf, uint16_t new_hp);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Player_updateHp() override = default;
};

class p_Player_Respawn : public DsPacket { /* 0x09 */
    private:
        int8_t dimension;
    public:
        p_Player_Respawn(PacketReturnInfo inf, int8_t dimension);
        p_Player_Respawn(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_Player_Respawn() override = default;
};

class p_PlayerBase : public DsPacket { /* 0x0A */
    private:
        bool on_ground;
    public:
        bool getOnGround();

        p_PlayerBase(PacketReturnInfo inf, bool on_ground);
        p_PlayerBase(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override; 
        ~p_PlayerBase() override = default;
};

class p_Player_Pos : public p_PlayerBase { /* 0x0B */
    private:
        v3<double> xyz;
        double stance;
    public:
        v3<double> getXYZ();
        double getStance();

        p_Player_Pos(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance);
        p_Player_Pos(Packet pack);

        uint8_t getID() override;
        Packet serialize() override;
        ~p_Player_Pos() override = default;
};

class p_Player_Look : public p_PlayerBase { /* 0x0C */
    private:    
        v2<float> yp;
    public:
        v2<float> getYP();

        p_Player_Look(PacketReturnInfo inf, bool on_ground, v2<float> yp);
        p_Player_Look(Packet pack);

        uint8_t getID() override;
        Packet serialize() override;
        ~p_Player_Look() override = default;
};

class p_Player_PosLook : public p_Player_Look, public p_Player_Pos { /* 0x0D */
    public:
        p_Player_PosLook(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance, v2<float> yp);
        p_Player_PosLook(Packet pack);

        uint8_t getID() override;
        Packet serialize() override;
        ~p_Player_PosLook() override = default;
};

enum P_DigStatus{
    STARTED = 0x00,
    FINISHED = 0x02,
    DROP = 0x04,
};

enum Block_Face{
    NEGY = 0x00,
    POSY,
    NEGZ,
    POSZ,
    NEGX,
    POSX,
};

class p_Player_Dig : public DsPacket{ /* 0x0E */
    private:
        P_DigStatus status;
        int32_t x,z;
        uint8_t y;
        Block_Face face;
    public:
        p_Player_Dig(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override;
        ~p_Player_Dig() override = default;
};

class p_Player_BlockPlace : public DsPacket{ /* 0x0F */
    private:
        int32_t x,z;
        uint8_t y;
        Block_Face face;
        uint16_t block_id;
    public:
        p_Player_BlockPlace(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override;
        ~p_Player_BlockPlace() override = default;
};


class p_Player_BlockPlaceItem : public DsPacket{ /* 0x0F */
    private:
        double x,z;
        uint8_t y;
        Block_Face face;
        uint16_t block_id;
        uint8_t amount;
        uint16_t damage; //??????? wtf notch
    public:
        p_Player_BlockPlaceItem(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override;
        ~p_Player_BlockPlaceItem() override = default;
};

class p_Player_HoldChange : public DsPacket{ /* 0x10 */
    private:
        uint16_t slot;
    public:
        p_Player_HoldChange(Packet pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override;
        ~p_Player_HoldChange() override = default;
};

class p_Player_UseBed : public DsPacket { /* 0x11 */
    private:
        int32_t eid;
        int8_t in_bed;
        int32_t x,z;
        uint8_t y;
    public:
        p_Player_UseBed(PacketReturnInfo inf, int32_t eid, v3<int32_t> xyz);

        uint8_t getID() override;
        PacketCategories getType() override;
        Packet serialize() override;
        ~p_Player_UseBed() override = default;
};

#endif