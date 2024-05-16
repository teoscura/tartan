#include "p_serialhandler.hpp"
#include "p_serial.hpp"

SerializerHandler::SerializerHandler(){
    this->p_serial = new PacketSerializer();
}

PacketSerializer* SerializerHandler::getSerializer(){
    return p_serial;
}

SerializerHandler::~SerializerHandler(){
    delete this->p_serial;
}