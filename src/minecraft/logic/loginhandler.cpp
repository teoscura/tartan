#include "loginhandler.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "../../packet/packets/p_Kick.hpp"

std::unique_ptr<DsPacket> LoginHandler::handlepacket(std::unique_ptr<DsPacket> p, PlayerList* plist){
    std::cout<<"sheesh1\n";

    //FIX ME REMAKE THIS PROPERLY DAMN.

    DsPacket* res;
    DsPacket* tmp = p.release();
    switch(p->getID()){
        case 0x01: 
            res = handleLoginRequest((p_LoginRequest*)tmp);
            break;
        case 0x02:
            res = handleHandshake((p_HandShake*)tmp, plist);
            break;
        default: break;  
    }
    delete tmp;
    std::unique_ptr<DsPacket> pack(res);
    return pack;
    std::cout<<"sheesh2\n";
}

DsPacket* LoginHandler::handleHandshake(p_HandShake* pack, PlayerList* plist){
    std::u16string string;

    //TODO when server player list is implemented, change this
    //To use main player list for checkups.
    if(plist->containsname(pack->username)){
        string = u"Server is full!";
        p_Kick* result = new p_Kick(string, string.length());
        return result;
    }
    string = u"-";
    p_HandShake* result = new p_HandShake(string, string.length());
    result->setInfo(pack->getInfo());
    return result;
}


DsPacket* LoginHandler::handleLoginRequest(p_LoginRequest *pack){
    p_LoginRequest resp;
    resp.dimension = 0x00;
    resp.seed = 0;
    resp.protocol = 0x0e;
    resp.username_len=0;
    resp.setInfo(pack->getInfo());
    if(pack->protocol!=14){
        std::u16string string = u"Invalid version!";
        return new p_Kick(string, string.length());
    }
    return new p_LoginRequest(resp);
}

