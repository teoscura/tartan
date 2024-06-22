#ifndef E_PLAYERUPDATE_H
#define E_PLAYERUPDATE_H

#include "event.hpp"

//just using this as a way to keep track of what to implement.
enum PlayerUpdateType{
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
        uint32_t EID;
        bool on_ground;
    public:
        Event_PlayerUpdateBase(uint64_t destination_tick, uint32_t EID, bool on_ground);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_PlayerUpdateBase() override = default;
};

class Event_PlayerUpdate_Pos : public Event_PlayerUpdateBase{
    protected:
        v3<double> new_xyz;
        double stance;
    public:
        Event_PlayerUpdate_Pos(uint64_t destination_tick, uint32_t EID, bool on_ground, v3<double> xyz, double stance);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_PlayerUpdate_Pos() override = default;
};

class Event_PlayerUpdate_Look : public Event_PlayerUpdateBase{
    protected:
        v2<float> new_yp;
    public:
        Event_PlayerUpdate_Look(uint64_t destination_tick, uint32_t EID, bool on_ground, v2<float> new_yp);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_PlayerUpdate_Look() override = default;
};

class Event_PlayerUpdate_PosLook : public Event_PlayerUpdate_Look, public Event_PlayerUpdate_Pos{
    protected:
    public:
        Event_PlayerUpdate_PosLook(uint64_t destination_tick, uint32_t EID, bool on_ground, v3<double> new_xyz, double stance, v2<float> new_yp);
        void process(ServerState* state, PacketQueue* queue) override;
        ~Event_PlayerUpdate_PosLook() override = default;
};

#endif


