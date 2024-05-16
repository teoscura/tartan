#include "ticker.hpp"
#include <chrono>
#include <ratio>
#include <thread>

Ticker::Ticker(){
    this->tick=0;
    while(this->running){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        this->tick++;
        //FIXME write tick to sql. 
    }
}