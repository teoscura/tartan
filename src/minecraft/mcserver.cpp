#include "mcserver.hpp"

#include "../helpers/settingshandler.hpp"


MCServer::MCServer() : 

    settings(SettingsHandler::getSettings()->getSettings()){

}