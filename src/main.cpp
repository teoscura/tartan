#include <chrono>
#include <iostream>
#include <thread>

#include "helpers/loggerhandler.hpp"
#include "helpers/settingshandler.hpp"

#include "minecraft/entity/player/playerlist.hpp"
#include "minecraft/entity/entitylist.hpp"
#include "minecraft/server/tmpmcserver.hpp"
#include "packet/handler/p_deserial.hpp"
#include "util/miscutil.hpp" 
#include "network/server.hpp"

int main(){
    LoggerHandler lh = LoggerHandler();
    printSplash();
    PacketDeserializer deserial;
    PacketSerializer serial;
    SettingsHandler set_handler;
    PlayerList global_plist;
    EntityList global_elist;
    TempServer tserver(&deserial, &serial, &global_plist, &global_elist);
    Server server(&deserial, &serial);
    std::jthread NetworkThread(&Server::listen_loop, server);
    std::jthread GameThread(&TempServer::tickloop, std::ref(tserver));
    while(1){
        //ctrlC to destroy is strange but works.
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout<<"[INFO] Still Running... [CTRL+C to STOP!]\n";
    }
    close(server.getListener().sockfd);
    return 0;
}
