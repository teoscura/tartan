#ifndef PACKETS_H
#define PACKETS_H

#include <cstdint>
#include <vector>

enum PacketCategories{
    NOT_IMPLEMENTED,
    LOGIN,
    PLAYER,
    ENTITY,
    CHUNK_BLOCK,
    MISC,
};

struct PacketReturnInfo{
    uint32_t epoll_fd;
};

struct Packet{
    PacketReturnInfo info;
    std::vector<uint8_t> bytes;
    
    Packet();
    Packet(PacketReturnInfo in);
    Packet(std::vector<uint8_t> arr, PacketReturnInfo in);
    ~Packet();
};

class DsPacket{
    protected:
        PacketReturnInfo info;
    public:
        DsPacket();
        DsPacket(PacketReturnInfo inf);

        PacketReturnInfo getInfo();
        void setInfo(PacketReturnInfo inf);
        
        virtual uint8_t getID();
        virtual PacketCategories getType();
        virtual Packet serialize();
        virtual ~DsPacket() = default;
};

bool isImplemented(uint8_t id);

#endif