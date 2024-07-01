#include "p_serial.hpp"

#include "../../helpers/loggerhandler.hpp"
#include <memory>
#include <mutex>

void PacketSerializer::serialize(std::shared_ptr<DsPacket> p){
    Packet result = p->serialize();
    if(result.bytes.size()==0){
        LoggerHandler::getLogger()->LogPrint(ERROR, "Tried to serialize unimplemented {} packet!", (int)p->getID());
        return;
    }
    std::unique_lock<std::mutex> lock(mut);
    this->out.push_back(result);
}

std::vector<Packet> PacketSerializer::getPacketVector(){
    std::unique_lock<std::mutex> lock(this->mut);
    std::vector<Packet> res(this->out);
    this->out.clear();
    return res;
}