#ifndef MC_ENTITYLIST_H
#define MC_ENTITYLIST_H

#include <optional>
#include <vector>

#include "entity.hpp"

class EntityList{
    private:
        std::vector<DeadEntity> list;
        uint32_t last_eid = 1;
    public:
        uint32_t allocateEID();
        void insert(Entity entityin);
        std::optional<Entity*> findEntity(uint32_t eid);
        void despawn(uint32_t eid);
        bool isDespawned(uint32_t eid);
};

#endif