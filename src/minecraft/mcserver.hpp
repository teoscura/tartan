#ifndef MC_MCSERVER_H
#define MC_MCSERVER_H

//LONGTERM structure mcserver

#include <memory>
#include <set>
#include <thread>

#include "player/playerlist.hpp"
//#include "blob.hpp"



class MCServer{
    private:
        GlobalPlayerList globalPlayerList;
        std::set<std::jthread> blobs;
        //TODO implement RegionPool.
    public:
        MCServer();
        void handleBlobs();
        void mergeBlobs();
        void diviteBlob();
        void recievePacket();
        void sendGlobalPacket(std::unique_ptr<DsPacket> pack);
        ~MCServer();
};

#endif