#ifndef MC_LIVINGENTITY_H
#define MC_LIVINGENTITY_H

#include "../world/vector.hpp"
#include "entity.hpp"
#include <cstdint>

//FIXME only tell specific properties to be updated, such that
//useless packets may be avoided.
//SOLUTION->use bitmask.

class LivingEntity : public Entity{
    protected:
        uint32_t ID;
        uint8_t health;
        v3<double> last_grounded;
        v3<double> xyz;
        v3<double> velocity;
        float pitch;
        float yaw;
        bool to_update;
    public:
        virtual uint32_t getEntityId();     
};

#endif

