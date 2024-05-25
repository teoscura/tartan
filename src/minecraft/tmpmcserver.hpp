#ifndef MC_TEMPMCSERVER_H
#define MC_TEMPMCSERVER_H

#include "entity/player/playerlist.hpp"
#include "logic/packetprocessor.hpp"
#include "world/chunk.hpp"
#include "world/worldgen/flatgen.hpp"

class TempServer{
    private:
        PlayerList global_plist;
        PacketProcessor pp_processor;
        FlatlandGenerator terrain_gen;
        Chunk motherchunk;
    public:
        TempServer(PacketDeserializer* pdeserial,PacketSerializer* pserial);
        void loop();

};

#endif