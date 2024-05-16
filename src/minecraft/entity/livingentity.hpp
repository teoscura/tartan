#ifndef MC_LIVINGENTITY_H
#define MC_LIVINGENTITY_H

#include "../world/vector.hpp"
#include "entity.hpp"
#include <cstdint>

class LivingEntity : public Entity{
    protected:
        uint8_t health;
        v3<double> last_grounded;
    public:
        virtual uint32_t getEntityId();     
};

#endif

