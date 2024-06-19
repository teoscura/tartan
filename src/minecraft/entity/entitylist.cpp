#include "entitylist.hpp"

#include <optional>

#include "../../helpers/loggerhandler.hpp"
#include "entity.hpp"

uint32_t EntityList::allocateEID(){
    this->last_eid++;
    return this->last_eid;
}

void EntityList::insert(Entity player){
    this->list.push_back(player);
}

std::optional<Entity*> EntityList::findEntity(uint32_t eid){
    for(DeadEntity& t : this->list){
        if(t.isDespawned()){
            return std::nullopt;
        } 
        Entity temp = static_cast<Entity&>(t);
        if(temp.getEntityId()==eid){
            return &temp;
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
        if(list.at(i).isDespawned()){
            continue;
        }
        if(list.at(i).getEntityId()==eid){
            list.at(i) = DeadEntity(eid);
            return;
        }
    }
    LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to despawn an already despawned entity! ({})", eid);
    return;
}

bool EntityList::isDespawned(uint32_t eid){
    return list.at(eid-1).isDespawned();
}