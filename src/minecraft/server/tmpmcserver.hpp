#ifndef MC_TEMPMCSERVER_H
#define MC_TEMPMCSERVER_H

#include "../logic/eventhandler.hpp"
#include "../logic/packetprocessor.hpp"
#include "../world/chunk.hpp"
#include "../world/worldgen/flatgen.hpp"
#include "serverstate.hpp"

#include <memory>

class TempServer{
    private:
        ServerState state;
        PacketProcessor pp_processor;
        FlatlandGenerator terrain_gen;
        EventHandler e_handler;
        std::unique_ptr<Chunk> motherchunk;
    public:
        TempServer(PacketDeserializer* pdeserial,PacketSerializer* pserial, PlayerList* plist, EntityList* elist);

        void processEvents();
        void tickevents();
        void tickloop();

};

#endif