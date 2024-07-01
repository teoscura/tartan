#include "e_misc.hpp"

#include <codecvt>
#include <memory>

#include "../../../packet/packets/p_Misc.hpp"
#include "../../../helpers/loggerhandler.hpp"
#include "event.hpp"


Event_ChatMessage::Event_ChatMessage(uint64_t delivery_tick, PacketReturnInfo inf, std::u16string message) : 
    EventBase(delivery_tick),
    inf(inf),
    message(message){
}

void Event_ChatMessage::process(ServerState* state, PacketSerializer* serial){
    auto tmpplayer = state->global_plist->findPlayer(this->inf);
    if(!tmpplayer.has_value()){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Someone sent a chat message in an unallowed way!");
        return;
    }
    auto eid = tmpplayer.value()->getEntityId();
    if(this->inf.epoll_fd!=0&&eid==0){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Someone sent a chat message in an unallowed way!");
        return;
    }
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> converter;
    if(message.length()>118){
        LoggerHandler::getLogger()->LogPrint(ERROR, "{} sent a message thats too long!", converter.to_bytes(tmpplayer.value()->getUsername()));
        return;
    }
    if(message[0] == u'/'){
        serial->serialize(std::shared_ptr<p_ChatMessage>(new p_ChatMessage(this->inf, u"§l§cCommands are not implemented yet!§r§f")));
        //TODO Command.
        return;
    }
    std::u16string chat_message;
    chat_message = u"<"+tmpplayer.value()->getUsername()+u"> "+this->message;
    this->queuePacket_Global(std::shared_ptr<p_ChatMessage>(new p_ChatMessage(PacketReturnInfo(), chat_message)), state, serial);
}