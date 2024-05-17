#include "mcserver.hpp"

#include "../helpers/settingshandler.hpp"
#include "blob/blobpool.hpp"


MCServer::MCServer() : 

    settings(SettingsHandler::getSettings()->getSettings()),
    bp(atoi(settings.at("view_distance").c_str())){
}