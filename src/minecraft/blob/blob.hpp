#ifndef MC_BLOB_H
#define MC_BLOB_H

#include "../entity/player/playerlist.hpp"
#include "worldblob.hpp"

class Blob : public WorldBlob{
    protected:
        //PacketProcessor blob_packets;
        PlayerList *global_Players;
        PlayerList local_players;
    public:
        Blob(std::size_t radius);
        Blob(v2<int32_t> chunk_coords, std::size_t radius);


        void welcomePlayer(std::shared_ptr<Player> moved_p);
        void goodbyePlayer(std::shared_ptr<Player> player_tomove);
        void processPacket(std::unique_ptr<DsPacket> p);
        void sendPacketToGlobal(std::unique_ptr<DsPacket> p);
};

#endif