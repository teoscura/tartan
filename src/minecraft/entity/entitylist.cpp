#include "entitylist.hpp"

#include <memory>
#include <optional>

#include "../../helpers/loggerhandler.hpp"
#include "entity.hpp"

uint32_t EntityList::allocateEID(){
    auto t = this->last_eid;
    this->last_eid++;
    return t;
}

void EntityList::insert(std::shared_ptr<DeadEntity> entity){
    this->list.push_back(entity);
}

std::optional<std::shared_ptr<Entity>> EntityList::findEntity(uint32_t eid){
    for(auto t : this->list){
        if(t->isDespawned()){
            return std::nullopt;
        } 
        Entity* temp = static_cast<Entity*>(t.get());
        if(temp->getEntityId()==eid){
            return std::shared_ptr<Entity>(temp);
        }
    }
    return std::nullopt;
}

void EntityList::despawn(uint32_t eid){
    if(eid>this->last_eid){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to despawn a non existant entity! ({})", eid);
        return;
    }
    for(int i = 0; i<list.size();i++){
        if(list.at(i)->isDespawned()){
            continue;
        }
        if(list.at(i)->getEntityId()==eid){
            list.at(i) = std::shared_ptr<DeadEntity>(new DeadEntity(eid));
            return;
        }
    }
    LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to despawn an already despawned entity! ({})", eid);
    return;
}

bool EntityList::isDespawned(uint32_t eid){
    return list.at(eid-1)->isDespawned();
}