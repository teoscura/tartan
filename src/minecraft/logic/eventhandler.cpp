#include "eventhandler.hpp"

void EventHandler::processEvents(){
    for(auto t : this->e_schedule.getExpectedEvents(this->state->time.s_tick)){
        t.process(this->state, &this->out);
    }
}

void EventHandler::sendPackets(){
    auto tmpsz = out.size();
    for(int i=0;i<tmpsz;i++){
        this->serializer->serialize(out.pop());
    }
}