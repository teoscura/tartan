#ifndef MC_ENTITY_H
#define MC_ENTITY_H

#include "../world/vector.hpp"

class DeadEntity{
    private:
        uint32_t EID;
        bool despawned = false;
    public:
        DeadEntity(uint32_t eid);
        void despawn();
        bool isDespawned();
        uint32_t getEntityId();
        virtual ~DeadEntity() = default;
};

class Entity : public DeadEntity{
    protected:
        v3<double> xyz = v3<double>(0,10,0);
        v3<double> velocity = v3<double>(0,0,0);
        v2<float> yp = v2<float>(0,0);
        bool on_ground = true;
    public:
        Entity(uint32_t eid);
        void updateOnGround(bool new_on_ground);
        void updatePosLook(v3<double> new_xyz, v2<float> new_yp);
        v3<double> getXYZ();
        v2<float> getYP();
        virtual ~Entity() override = default;
};  

#endif