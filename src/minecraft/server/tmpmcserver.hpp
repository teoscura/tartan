#ifndef MC_TEMPMCSERVER_H
#define MC_TEMPMCSERVER_H

#include "../../network/server.hpp"
#include "../logic/eventhandler.hpp"
#include "../logic/packetprocessor.hpp"
#include "../world/chunk.hpp"
#include "../world/worldgen/flatgen.hpp"
#include "serverstate.hpp"

#include <memory>

class TempServer : public Server, public FlatlandGenerator{
    private:
        PacketQueue in;
        PacketDeserializer pdeserial; 
        PacketSerializer pserial;
        PlayerList global_plist;
        EntityList global_elist;
        ServerState state;
        PacketProcessor pp_processor;
        EventHandler e_handler;
        std::unique_ptr<Chunk> motherchunk;
    public:
        TempServer();

        PacketQueue* getIn();
        void tickevents();
        void tickloop();

};

#endif