#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

using Clock = std::chrono::high_resolution_clock;
auto delay = std::chrono::milliseconds(666);

int main(){
    auto start_timepoint = Clock::now();
    uint64_t s_tick =0;
    while(1){
        uint64_t current_tick = (Clock::now()-start_timepoint)/delay;
        //if im rushing - aka if i still didnt get to a new tick to handle;
        if(current_tick<=s_tick){ 
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }
        //if im dragging - i need to handle a tick or im late handling them.
        s_tick = current_tick;
        std::cout<<"Tick!\n";
    }
}