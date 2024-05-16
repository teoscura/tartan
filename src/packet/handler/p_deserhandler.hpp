#ifndef P_DESERHANDLER_H
#define P_DESERHANDLER_H

#include "p_deserial.hpp"

class DeserializerHandler{
    private:
        static inline PacketDeserializer *p_deser;
    public:
        DeserializerHandler();
        static PacketDeserializer* getDeserializer();
        ~DeserializerHandler();
};

#endif