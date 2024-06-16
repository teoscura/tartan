#include "tmpmcserver.hpp"

#include <chrono>
#include <thread>

#include "../logic/packetprocessor.hpp"
#include "servertimeutil.hpp"


TempServer::TempServer(PacketDeserializer* pdeserial, PacketSerializer* pserial):
    pp_processor(pdeserial),
    e_handler(pserial, &state),
    motherchunk(this->terrain_gen.generateChunk(v2(0,0))){
    state.time = TimeUtil(state.time.Clock.now(),std::chrono::milliseconds(50), 0, 0);
};

void TempServer::tickloop(){
    while(1){
        uint64_t current_tick = (state.time.Clock.now()-state.time.start_timepoint)/state.time.delay;
        //if im rushing - aka if i still didnt get to a new tick to handle;
        if(current_tick<=this->state.time.s_tick){ 
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        //if im dragging - i need to handle a tick or im late handling them.
        this->state.time.s_tick = current_tick;
        tickevents();
    }
}


void TempServer::tickevents(){
    this->pp_processor.retrieveQueue();
    this->pp_processor.processPackets();
    this->e_handler.processEvents();
}

