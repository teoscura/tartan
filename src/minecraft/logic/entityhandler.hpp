#ifndef MC_PP_ENTITYHANDLER_H
#define MC_PP_ENTITYHANDLER_H 

#include <memory>

#include "../../packet/packets/packet.hpp"

class EntityHandler{
    protected:
    
    public:
        std::unique_ptr<DsPacket> processPacket(std::unique_ptr<DsPacket> p);
        //TODO update entities function
        //TODO send entity updates function
};

#endif