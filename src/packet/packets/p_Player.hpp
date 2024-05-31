#ifndef PP_PLAYER_BASE
#define PP_PLAYER_BASE

#include <cstdint>
#include <memory>

#include "../../minecraft/world/vector.hpp"
#include "packet.hpp"

class p_PlayerBase : public DsPacket {
    public:
        bool on_ground;
    
        p_PlayerBase(PacketReturnInfo inf, bool on_ground);
        p_PlayerBase(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        PacketCategories getType() override;
        std::unique_ptr<Packet> serialize() override; 
        ~p_PlayerBase() override;
};

class p_Player_Pos : public p_PlayerBase {
    public:
        v3<double> xyz;
        double stance;

        p_Player_Pos(PacketReturnInfo inf, bool on_ground, v3<double> xyz, double stance);
        p_Player_Pos(std::unique_ptr<Packet> pack);

        uint8_t getID() override;
        std::unique_ptr<Packet> serialize() override;
        ~p_Player_Pos() override;
};

#endif