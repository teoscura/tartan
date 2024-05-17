#ifndef MC_MCSERVER_H
#define MC_MCSERVER_H

//LONGTERM structure mcserver

#include <memory>

#include "../network/server.hpp"
#include "blob/blobpool.hpp"
#include "entity/player/playerlist.hpp"
#include "logic/loginhandler.hpp"
//#include "blob.hpp"

class MCServer : public Server{
    private:
        std::map<std::string, std::string> settings;
        GlobalPlayerList globalPlayerList;
        BlobPool bp;
        LoginHandler loginhandler;
    public:
        MCServer();
        void sendGlobalPacket(std::unique_ptr<DsPacket> pack);
        ~MCServer();
};

#endif