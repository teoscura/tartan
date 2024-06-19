#ifndef MC_ENTITY_H
#define MC_ENTITY_H

#include "../world/vector.hpp"

class Entity{
    protected:
        uint32_t ID;
        v3<double> xyz;
        v3<double> velocity;
        v2<float> yp;
        bool on_ground;
        bool despawned;
    public:
        void updateOnGround(bool new_on_ground);
        v3<double> getXYZ();
        v2<float> getYP();
        virtual uint32_t getEntityId();
};

#endif