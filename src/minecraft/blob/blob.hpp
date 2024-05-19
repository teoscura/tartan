#ifndef MC_BLOB_H
#define MC_BLOB_H

#include <thread>

#include "../entity/player/playerlist.hpp"
#include "../logic/packetprocessor.hpp"
#include "worldblob.hpp"

class Blob : public WorldBlob{
    protected:
        PacketProcessor blob_packprocessor;
        PlayerList *global_Players;
        PlayerList local_players;
        std::jthread blob_thread;
    public:
        Blob(std::size_t radius);
        Blob(v2<int32_t> center_chunk_coords, std::size_t radius);
        Blob(WorldBlob blob, PlayerList& new_local);

        PlayerList& getLocalPlayers();

        void eventLoop();
        void welcomePlayer(std::shared_ptr<Player> moved_p);
        void goodbyePlayer(std::shared_ptr<Player> player_tomove);
        void processPacket(std::unique_ptr<DsPacket> p);
        void sendPacketToGlobal(std::unique_ptr<DsPacket> p);
};

#endif