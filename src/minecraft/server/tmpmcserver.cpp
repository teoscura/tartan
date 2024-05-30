#include "tmpmcserver.hpp"

#include <chrono>
#include <thread>

#include "../logic/events/eventschedule.hpp"
#include "../logic/packetprocessor.hpp"


TempServer::TempServer(PacketDeserializer* pdeserial, PacketSerializer* pserial):
    pp_processor(pdeserial, pserial, &this->state),
    motherchunk(this->terrain_gen.generateChunk(v2(0,0))){

    this->time_state.start_timepoint = this->time_state.Clock.now();
};

void TempServer::tickloop(){
    while(1){
        uint64_t current_tick = (time_state.Clock.now()-time_state.start_timepoint)/time_state.delay;
        //if im rushing - aka if i still didnt get to a new tick to handle;
        if(current_tick<=this->time_state.s_tick){ 
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        //if im dragging - i need to handle a tick or im late handling them.
        this->time_state.s_tick = current_tick;
        tickevents();
    }
}

void TempServer::processEvents(){
    for(auto t : this->schedule.getExpectedEvents(this->time_state.s_tick)){
        t->process(&this->state);
    }
}

void TempServer::tickevents(){
    this->pp_processor.retrieveQueue();
    this->pp_processor.processPackets();
    this->processEvents();
    this->pp_processor.sendPackets();
}

