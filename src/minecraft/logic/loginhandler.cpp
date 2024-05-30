#include "loginhandler.hpp"


#include <memory>
#include <string>

#include "../../packet/packets/p_LoginRequest.hpp"
#include "../../packet/packets/p_HandShake.hpp"
#include "../../packet/packets/p_Kick.hpp"

std::unique_ptr<DsPacket> LoginHandler::handlepacket(std::unique_ptr<DsPacket> p, PlayerList* plist){
    //FIX ME REMAKE THIS PROPERLY DAMN.
    std::unique_ptr<DsPacket> tmp;
    switch(p->getID()){
        case 0x01:
            tmp = handleLoginRequest(std::move(p));
            break;
        case 0x02:
            tmp = handleHandshake(std::move(p), plist);
            break;
        default:
            LoggerHandler::getLogger()->LogPrint(ERROR, "Recieved Invalid packet in loginhandler");
            break;
    }
    return std::move(tmp);
}

std::unique_ptr<DsPacket> LoginHandler::handleLoginRequest(std::unique_ptr<DsPacket> pack){
    auto tmp = dynamic_cast<p_LoginRequest&>(*pack);
    if(tmp.protocol!=14){
        std::u16string string = u"Invalid version!";
        return std::make_unique<p_Kick>(string, string.length());
    }
    auto result = std::make_unique<p_LoginRequest>(pack->getInfo());
    return std::move(result);
}


std::unique_ptr<DsPacket> LoginHandler::handleHandshake(std::unique_ptr<DsPacket> pack, PlayerList* plist){
    std::u16string string;
    auto tmp = dynamic_cast<p_HandShake&>(*pack);
    if(plist->containsname(tmp.username)){
        string = u"Server is full!";
        auto t = std::make_unique<p_Kick>(string, string.length());
        t->setInfo(tmp.getInfo());
        return std::move(t);
    }
    string = u"-";
    auto result = std::make_unique<p_HandShake>(string, string.length());
    result->setInfo(tmp.getInfo());
    return result;
}



