#ifndef MC_TEMPMCSERVER_H
#define MC_TEMPMCSERVER_H

#include "../logic/events/eventschedule.hpp"
#include "../logic/packetprocessor.hpp"
#include "../world/chunk.hpp"
#include "../world/worldgen/flatgen.hpp"
#include "serverstate.hpp"
#include "servertimeutil.hpp"

#include <memory>

class TempServer{
    private:
        ServerState state;
        TimeUtil time_state;
        PacketProcessor pp_processor;
        FlatlandGenerator terrain_gen;
        EventSchedule schedule;
        std::unique_ptr<Chunk> motherchunk;
    public:
        TempServer(PacketDeserializer* pdeserial,PacketSerializer* pserial);

        void processEvents();
        void tickevents();
        void tickloop();

};

#endif