#include <chrono>
#include <iostream>
#include <thread>

#include "helpers/loggerhandler.hpp"
#include "helpers/settingshandler.hpp"

#include "minecraft/server/tmpmcserver.hpp"
#include "util/miscutil.hpp" 
#include "network/server.hpp"

int main(){
    LoggerHandler lh = LoggerHandler();
    printSplash();
    SettingsHandler set_handler;
    TempServer tserver;
    std::jthread NetworkThread(&TempServer::Server::listen_loop, &tserver);
    std::jthread GameThread(&TempServer::tickloop, &tserver);
    while(1){
        //ctrlC to destroy is strange but works.
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout<<"[INFO] Still Running... [CTRL+C to STOP!]\n";
    }
    return 0;
}
