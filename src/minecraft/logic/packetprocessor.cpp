#include "packetprocessor.hpp"

#include <memory>
#include <optional>

#include "../../packet/packets/p_Login.hpp"
#include "../../packet/packets/p_Misc.hpp"
#include "../../packet/packets/p_Player.hpp"
#include "../../helpers/loggerhandler.hpp"
#include "events/e_login.hpp"
#include "events/e_misc.hpp"
#include "events/e_player.hpp"
//#include "events/e_player.hpp"

PacketProcessor::PacketProcessor(PacketQueue* in) : 
    in(in){
}

void notImpl(uint8_t id){
    LoggerHandler::getLogger()->LogPrint(INFO, "Recieved an unimplemented packet! ID: {}", (int)id);
}

void PacketProcessor::processPackets(ServerState* state, EventHandler* handler){
    std::optional<std::shared_ptr<DsPacket>> tmp = std::nullopt;
    while((tmp=this->in->pop()).has_value()){
        switch(tmp.value()->getID()){
            case 0x00:
                notImpl(tmp.value()->getID());break;
            case 0x01:
                {auto t = dynamic_cast<p_LoginRequest*>(tmp.value().get());
                handler->insertEvent(std::shared_ptr<EventBase>(new Event_LoginLogRequest(0, t->getInfo(), t->protocol)), 1);
                break;}
            case 0x02:
                {auto t = dynamic_cast<p_HandShake*>(tmp.value().get());
                handler->insertEvent(std::shared_ptr<EventBase>(new Event_LoginHandshake(0, t->getInfo(), t->username)), 1);
                break;}
            case 0x03:
                {auto t = dynamic_cast<p_ChatMessage*>(tmp.value().get());
                handler->insertEvent(std::shared_ptr<Event_ChatMessage>(new Event_ChatMessage(0, t->getInfo(), t->getMessage())), 1);
                break;}
            case 0x07:
                notImpl(tmp.value()->getID());break;
            case 0x09:
                notImpl(tmp.value()->getID());break;
            case 0x0A:
                notImpl(tmp.value()->getID());break;
            case 0x0B:
                {auto t = dynamic_cast<p_Player_Pos*>(tmp.value().get());
                auto tmpplayer = state->global_plist->findPlayer(t->getInfo());
                if(!tmpplayer.has_value()){
                    break;
                }
                auto eid = tmpplayer.value()->getEntityId();
                handler->insertEvent(std::shared_ptr<EventBase>(new Event_PlayerUpdate_Pos(0, eid, t->getOnGround(), t->getXYZ(), t->getStance())), 1);
                break;}
            case 0x0C:
                notImpl(tmp.value()->getID());break;
            case 0x0D:
                notImpl(tmp.value()->getID());break;
            case 0x0E:
                notImpl(tmp.value()->getID());break;
            case 0x0F:
                notImpl(tmp.value()->getID());break;
            case 0x10:
                notImpl(tmp.value()->getID());break;
            case 0x12:
                notImpl(tmp.value()->getID());break;
            case 0x13:
                notImpl(tmp.value()->getID());break;
            case 0x65:
                notImpl(tmp.value()->getID());break;
            case 0x66:
                notImpl(tmp.value()->getID());break;
            case 0x6A:
                notImpl(tmp.value()->getID());break;
            case 0x82:
                notImpl(tmp.value()->getID());break;
            case 0xFF:
                {auto t = dynamic_cast<p_Kick*>(tmp.value().get());
                handler->insertEvent(std::shared_ptr<EventBase>(new Event_PlayerDisconnect(0, t->getInfo())), 1);
                break;}
            default:
                notImpl(tmp.value()->getID());break;
        }
    }
    //TODO
}
