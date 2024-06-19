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
        PlayerStances stance = STAND;
        v3<int32_t> respawn_pos = v3<int32_t>(0,10,0);
    public:
        Player(PacketReturnInfo inf, std::u16string username, uint32_t EID);

        uint8_t render_updates;

        void updateBlob(uint8_t new_blob);

        void updatePosLook(v3<double> new_xyz, v2<float> new_yp);

        uint32_t getEntityId() override;
        std::u16string getUsername();
        const PacketReturnInfo& getReturnInfo();

        ~Player();

        //TODO constructor, destructor and methods specify the arguments for each function.
};

#endif