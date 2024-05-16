#ifndef MC_REGIONHANDLER_H
#define MC_REGIONHANDLER_H

#include <cstddef>
#include <map>
#include <memory>

#include "player/playerlist.hpp"
#include "world/worldgen/flatgen.hpp"
#include "world/chunk.hpp"

class Blob{
    private:
        std::map<v2<int32_t>, std::shared_ptr<Chunk>> chunks;
        FlatlandGenerator terrain_generator;
        PlayerMap local_players;
        std::size_t radius;
    public:
        //respectively accepts a player from outside, or takes out the player
        void eventLoop();

        void welcomePlayer(std::shared_ptr<Player> moved_p);
        void goodbyePlayer(std::shared_ptr<Player> player_tomove);

        void processPacket(std::unique_ptr<DsPacket> p);
        void sendPacketToGlobal(std::unique_ptr<DsPacket> p);


        void genChunk(v2<int32_t> chunk_coords);

        Blob();
        Blob(v2<int32_t> center_chunk_coords);
        ~Blob();
};

#endif