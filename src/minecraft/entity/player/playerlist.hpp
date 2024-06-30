#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "player.hpp"

struct LoginPlayer{
    uint64_t login_tick;
    std::u16string username;
    PacketReturnInfo inf;
    uint64_t howLongAgo(uint64_t current_tick);
};

class PlayerList{
    private:
        std::vector<std::shared_ptr<Player>> list;
        std::vector<std::shared_ptr<LoginPlayer>> login_list; 
    public:
        void insert(std::shared_ptr<Player> playerin);
        void insertLogin(std::shared_ptr<LoginPlayer> logplayerin);
        void remove(std::u16string username);
        void cleanupLogin(uint64_t current_tick);
        const std::vector<std::shared_ptr<Player>>& getList();
        std::optional<uint32_t> findEID(PacketReturnInfo info);
        std::optional<std::shared_ptr<Player>> findPlayer(uint32_t eid);
        std::optional<std::shared_ptr<Player>> findPlayer(std::u16string username);
        std::optional<std::shared_ptr<LoginPlayer>> findLogin(PacketReturnInfo inf);
        bool isOnline(std::u16string username);
        bool isLogin(std::u16string username);
        bool ishandshake(std::u16string username);
};



#endif