#include "tmpmcserver.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "../logic/packetprocessor.hpp"
#include "servertimeutil.hpp"


TempServer::TempServer():
    pdeserial(&this->in),
    pp_processor(&this->in),
    Server(&pdeserial, &pserial),
    e_handler(&pserial, &state),
    motherchunk(this->generateChunk(v2(0,0))),
    state(TimeUtil(state.time.Clock.now(),std::chrono::milliseconds(50), 0, 0), &global_plist, &global_elist, PlayerList(), EntityList(), 0){
};

PacketQueue* TempServer::getIn(){
    return &this->in;
};

void TempServer::tickloop(){
    while(1){
        uint64_t current_tick = (state.time.Clock.now()-state.time.start_timepoint)/state.time.delay;
        uint64_t a = current_tick - this->state.time.s_tick;
        //if im rushing - aka if i still didnt get to a new tick to handle;
        if(current_tick<=this->state.time.s_tick){ 
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        if(a > 10){
            std::cout<<"Server lagging by "<<a<<" ticks!\n";
        }
        this->state.time.s_tick = current_tick;
        tickevents();
    }
}

void TempServer::tickevents(){
    this->state.global_plist->cleanupList(this->state.time.s_tick);
    //this->state.global_elist->cleanupList();
    this->pp_processor.processPackets(&this->state, &this->e_handler);
    this->e_handler.processEvents();
}