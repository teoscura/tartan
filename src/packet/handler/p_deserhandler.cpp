#include "p_deserhandler.hpp"
#include "p_deserial.hpp"

DeserializerHandler::DeserializerHandler(){
    this->p_deser = new PacketDeserializer();
}

PacketDeserializer* DeserializerHandler::getDeserializer(){
    return p_deser;
}

DeserializerHandler::~DeserializerHandler(){
    delete this->p_deser;
}