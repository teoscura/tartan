#include <chrono>
#include <iostream>
#include <thread>

#include "helpers/loggerhandler.hpp"
#include "helpers/settingshandler.hpp"
#include "packet/handler/p_deserhandler.hpp"
#include "packet/handler/p_serialhandler.hpp"
#include "util/miscutil.hpp" 
#include "network/server.hpp"

int main(){
    LoggerHandler lh = LoggerHandler();
    printSplash();
    DeserializerHandler des_handler;
    SerializerHandler ser_handler;
    SettingsHandler set_handler;
    Server networkserv;
    std::thread NetworkThread(&Server::listen_loop, networkserv);
    while(1){
        //ctrlC to destroy is strange but works.
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        std::cout<<"[INFO] Still Running... [CTRL+C to STOP!]\n";
    }
    close(networkserv.getListener().sockfd);
    return 0;
}
