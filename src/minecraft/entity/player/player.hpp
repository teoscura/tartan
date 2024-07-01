#ifndef MC_PLAYER_H
#define MC_PLAYER_H

#include <cstdint>
#include <string>


#include "../../../packet/packets/packet.hpp"
#include "../../entity/entity.hpp"
#include "../../world/vector.hpp"

enum PlayerStates{
    L_OFFLINE= 0<<0,
    L_HANDSHAKE= 1<<0,
    L_PLAYING = 1<<1,
    PS_STAND = 0<<2,
    PS_CROUCH = 1<<2,
    PS_SLEEP  = 1<<4,
    S_TODESPAWN = 1<<5,
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
        std::u16string username = u"PlayerEntity";
        bool sleeping = false;
        double actual_height;
        uint8_t hp = 20;
        uint16_t held_slot = 0;
        uint64_t login_tick = 0;
        uint64_t last_keepalive = 0;
        uint8_t state = 0b0000000;
        v3<int32_t> respawn_pos = v3<int32_t>(8,10,8);
    public:
        Player(PacketReturnInfo inf, std::u16string username, uint32_t EID);

        bool assertStatus(uint8_t status);
        bool assertStatus(PlayerStates state);

        void setBlob(uint8_t new_blob);
        void setHP(uint8_t hp);
        void setSleeping(bool sleeping);
        void setHeldSlot(uint16_t held_slot);
        void setHeight(double height);
        void setKeepAlive(uint64_t keepalive);
        void setLoginTick(uint64_t tick);
        void setState(PlayerStates new_state);
        void setRespawnPos(v3<int32_t> respawn_pos);

        const PacketReturnInfo& getReturnInfo();
        std::u16string getUsername();
        uint8_t getHP();
        bool getSleeping();
        uint16_t getHeldSlot();
        double getHeight();
        uint64_t getLastKeepalive();
        uint64_t getLoginTick();
        uint8_t getState();
        v3<int32_t> getRespawnPos();

        ~Player() override;
        //TODO constructor, destructor and methods specify the arguments for each function.
};

#endif