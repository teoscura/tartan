#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include "server_settings.hpp"

class SettingsHandler{
    private:
        static inline ServerSettings *settings;
    public:
        SettingsHandler();
        static ServerSettings* getSettings();
        ~SettingsHandler();
};

#endif