#ifndef MC_PLAYER_H
#define MC_PLAYER_H

#include <string>

#include "../../../packet/packets/packet.hpp"
#include "../../entity/entity.hpp"
#include "../../world/vector.hpp"

enum PlayerStances{
    STAND,
    CROUCH,
    SLEEP,
};

enum PlayerState{
    FIRSTCONN = 0x00,
    LOGGING,
    PLAYING,
};

struct PlayerConnectionInfo{
    PacketReturnInfo packetinfo;
    PlayerState state;
};

class Player : public Entity{
    private:
        PlayerConnectionInfo info;
    protected:
        std::u16string username;
        const uint8_t maxhp = 20;
        uint8_t hp;
	    const double stand_height = 1.62;
        double actual_height;
        const double width = 0.6;
	    const double depth = 0.6;
        PlayerStances stance;
        v2<int32_t> respawn_pos;
    public:
        uint8_t updated_stats; // handled by main server, mask defining changes:
        /*  <<0 movement or look
            <<1 hp
            <<2 crouch/bedpos 
            <<3 animation
            <<4 sleeping update
            <<5 ridingcart
            <<6 holding change
        *///<<7 equip change
        uint8_t render_updates;

        void updateBlob(uint8_t newBlob);
        void updatePosLook();//TODO 

        uint32_t getEntityId() override;
        std::u16string getUsername();

        Player();
        ~Player();



        //TODO constructor, destructor and methods specify the arguments for each function.
};

#endif