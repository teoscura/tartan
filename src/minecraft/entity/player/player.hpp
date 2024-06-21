#ifndef MC_PLAYER_H
#define MC_PLAYER_H

#include <cstdint>
#include <string>


#include "../../../packet/packets/packet.hpp"
#include "../../entity/entity.hpp"
#include "../../world/vector.hpp"

enum PlayerStances{
    STAND,
    CROUCH,
    SLEEP,
};

struct PlayerConnectionInfo{
    PacketReturnInfo packetinfo;
    uint8_t blob;
};

struct PlayerStats{
    const uint8_t maxhp = 20;
    const double stand_height = 1.62;
    const double width = 0.6;
	const double depth = 0.6;
};

class Player : public Entity{
    private:
        PlayerConnectionInfo info;
    protected:
        static const PlayerStats stats;
        std::u16string username;
        uint8_t hp = 20;
        bool sleeping = false;
        uint16_t held_slot = 0;
        double actual_height;
        uint64_t last_keepalive;
        PlayerStances stance = STAND;
        v3<int32_t> respawn_pos = v3<int32_t>(0,10,0);
    public:
        Player(PacketReturnInfo inf, std::u16string username, uint32_t EID);

        void setBlob(uint8_t new_blob);
        void setHP(uint8_t hp);
        void setSleeping(bool sleeping);
        void setHeldSlot(uint16_t held_slot);
        void setHeight(double height);
        void setKeepAlive(uint64_t keepalive);
        void setStance(PlayerStances stance);
        void setRespawnPos(v3<int32_t> respawn_pos);

        const PacketReturnInfo& getReturnInfo();
        std::u16string getUsername();
        uint8_t getHP();
        bool getSleeping();
        uint16_t getHeldSlot();
        double getHeight();
        uint64_t getLastKeepalive();
        PlayerStances getStance();
        v3<int32_t> getRespawnPos();
        
        ~Player() override;
        //TODO constructor, destructor and methods specify the arguments for each function.
};

#endif