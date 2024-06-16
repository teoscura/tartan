#include "loginhandler.hpp"

#include <memory>
#include <string>

#include "../../packet/packets/p_Login.hpp"

void LoginHandler::handlepacket(std::unique_ptr<DsPacket> p, PlayerList* plist){
    switch(p->getID()){
        
    }
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
    auto tmp = dynamic_cast<p_HandShake*>(&*pack);
    if(plist->isonline(tmp->username)){
        string = u"Player is already online!";
        auto t = std::make_unique<p_Kick>(string, string.length());
        t->setInfo(tmp->getInfo());
        return std::move(t);
    }
    string = u"-";
    auto result = std::make_unique<p_HandShake>(string, string.length());
    result->setInfo(tmp->getInfo());
    return result;
}



