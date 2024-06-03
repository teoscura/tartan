#ifndef PACKETS_H
#define PACKETS_H

#include <cstdint>
#include <cstddef>
#include <memory>

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
    uint32_t thread_ID;
};

struct Packet{
    PacketReturnInfo info;
    uint8_t *bytes;
    std::size_t size;
    
    Packet();
    Packet(uint8_t *arr, std::size_t sz, PacketReturnInfo in);
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
        virtual std::unique_ptr<Packet> serialize();
        virtual ~DsPacket() = default;
};

bool isImplemented(uint8_t id);

#endif