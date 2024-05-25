#ifndef MC_ENTITY_H
#define MC_ENTITY_H

#include "../world/vector.hpp"

class Entity{
    protected:
        uint32_t ID;
        v3<double> xyz;
        v3<double> velocity;
        float pitch;
        float yaw;
        bool despawned;
        bool to_update;
    public:
        v3<double> getXYZ();
        virtual uint32_t getEntityId();
};

#endif