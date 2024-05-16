#include "settingshandler.hpp"
#include "server_settings.hpp"

SettingsHandler::SettingsHandler(){
    this->settings = new ServerSettings();
}

ServerSettings* SettingsHandler::getSettings(){
    return settings;
}

SettingsHandler::~SettingsHandler(){
    delete this->settings;
}