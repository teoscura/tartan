#ifndef E_PLAYERUPDATE_H
#define E_PLAYERUPDATE_H

#include "event.hpp"

//just using this as a way to keep track of what to implement.
enum PlayerUpdateType{
    LOGINPROCEDURE,
    POS,
    LOOK,
    POS_LOOK,
    VELOCITY,
    STANCE,
    HELD_SLOT,
    SLEEPING,
    ANIMATION,
};

class Event_PlayerUpdateBase : public EventBase{
    protected:
        uint64_t EID;
        bool on_ground;
    public:
        Event_PlayerUpdateBase(uint64_t destination_tick, bool on_ground);
        void process(ServerState* state) override;
        ~Event_PlayerUpdateBase() override;
};

class Event_PlayerUpdate_PosLook : public Event_PlayerUpdateBase{
    protected:
        v3<double> new_xyz;
        v2<float> new_yp;
    public:
        Event_PlayerUpdate_PosLook(/*TODO fields*/uint64_t destination_tick);
        void process(ServerState* state) override;
        ~Event_PlayerUpdate_PosLook() override;
};


#endif


