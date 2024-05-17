#ifndef MC_ENTITY_H
#define MC_ENTITY_H

#include "../world/vector.hpp"

class Entity{
    protected:
        v3<double> xyz;
        v3<double> velocity;
        float pitch;
        float yaw;
        bool despawned;
        bool to_update;
    public:
};

#endif