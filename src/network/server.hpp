#ifndef SERVER_H
#define SERVER_H

#include "../helpers/logger.hpp"
#include "../helpers/server_settings.hpp"
#include "threadpool.hpp"
#include "connections.hpp"

class Server{
    private:
        Logger* lg;
        ServerSettings* settings;
        ThreadPool tp;
        Connection listener;
        bool running;
    public:
        Server();
        ~Server();
        void listen_loop();
        void shutdown();
        Connection getListener();
};

#endif
