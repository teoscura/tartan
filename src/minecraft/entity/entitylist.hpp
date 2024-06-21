#ifndef MC_ENTITYLIST_H
#define MC_ENTITYLIST_H

#include <memory>
#include <optional>
#include <vector>

#include "entity.hpp"

class EntityList{
    private:
        std::vector<std::shared_ptr<DeadEntity>> list;
        uint32_t last_eid = 1;
        
    public:
        uint32_t allocateEID();
        void insert(std::shared_ptr<DeadEntity> entityin);
        std::optional<std::shared_ptr<Entity>> findEntity(uint32_t eid);
        void despawn(uint32_t eid);
        bool isDespawned(uint32_t eid);
};

#endif