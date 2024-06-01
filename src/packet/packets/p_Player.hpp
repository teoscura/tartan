#ifndef PP_PLAYER_BASE
#define PP_PLAYER_BASE

#include <cstdint>
#include <memory>

#include "../../minecraft/world/vector.hpp"
#include "packet.hpp"

class p_PlayerBase : public DsPacket {
    private:
        bool on_ground;
    public:
        p_PlayerBase(PacketReturnInfo inf, bool on_ground);
        p_PlayerBase(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_PlayerBase() override;
};

class p_Player_Pos : public p_PlayerBase {
    private:
        v3<double> xyz;
        double stance;
    public:
        p_Player_Pos(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance);
        p_Player_Pos(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        std::unique_ptr<Packet> serialize() override;
        ~p_Player_Pos() override;
};

class p_Player_Look : public p_PlayerBase {
    private:    
        v2<float> yp;
    public:
        

        p_Player_Look(PacketReturnInfo inf, bool on_ground, v2<float> yp);
        p_Player_Look(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        std::unique_ptr<Packet> serialize() override;
        ~p_Player_Look() override;
};

class p_Player_PosLook : public p_Player_Look, public p_Player_Pos {
    public:
        p_Player_PosLook(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance, v2<float> yp);
        p_Player_PosLook(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        std::unique_ptr<Packet> serialize() override;
        ~p_Player_PosLook() override;
};

#endif