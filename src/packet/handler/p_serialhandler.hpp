#ifndef P_SERIALHANDLER_H
#define P_SERIALHANDLER_H

#include "p_serial.hpp"

class SerializerHandler{
    private:
        static inline PacketSerializer *p_serial;
    public:
        SerializerHandler();
        static PacketSerializer* getSerializer();
        ~SerializerHandler();
};

#endif