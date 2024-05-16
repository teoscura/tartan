#ifndef MC_ENTITY_H
#define MC_ENTITY_H

#include "../world/vector.hpp"
#include <cstdint>

//FIXME only tell specific properties to be updated, such that
//useless packets may be avoided.

//SOLUTION->use bitmask.

class Entity{
    protected:
        int32_t ID;
        v3<double> xyz;
        v3<double> velocity;
        float pitch;
        float yaw;
        bool despawned;
        bool to_update;  
    public:
};

#endif