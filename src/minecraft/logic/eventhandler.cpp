#include "eventhandler.hpp"

void EventHandler::processEvents(){
    for(auto t : this->e_schedule.getExpectedEvents(this->state->time.s_tick)){
        t.process(this->state, this->serializer);
    }
}