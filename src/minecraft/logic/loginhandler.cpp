#include "loginhandler.hpp"
#include <string>

DsPacket* LoginHandler::handlepacket(DsPacket* p){
    DsPacket* pack;
    switch(p->getID()){
        case 0x00:
            //TODO implement tick timer.
            break;
        case 0x01: 
            pack = handleLoginRequest((p_LoginRequest*)p);
            break;
        case 0x02:
            pack = handleHandshake((p_HandShake*)p);
            break;
        default: break;  
    }
    return pack;
}

DsPacket* LoginHandler::handleHandshake(p_HandShake* pack){
    std::u16string string;

    //TODO when server player list is implemented, change this
    //To use main player list for checkups.
    if(this->usernames.contains(pack->username)){
        string = u"Server is full!";
        p_Kick* result = new p_Kick(string, string.length());
        delete pack;
        return result;
    }
    string = u"-";
    p_HandShake* result = new p_HandShake(string, string.length());
    result->setInfo(pack->getInfo());
    delete pack;
    return result;
}


p_LoginRequest* LoginHandler::handleLoginRequest(p_LoginRequest *pack){
    p_LoginRequest resp;
    resp.dimension = 0x00;
    resp.seed = 0;
    resp.protocol = 0x0e;
    resp.username_len=0;
    resp.setInfo(pack->getInfo());
    if(pack->protocol!=14){
        //send 0xFF
        exit(-1);
    }
    return new p_LoginRequest(resp);
}

