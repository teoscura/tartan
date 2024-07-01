#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "player.hpp"

class PlayerList{
    private:
        std::vector<std::shared_ptr<Player>> list;
    public:
        void insert(std::shared_ptr<Player> playerin);
        void remove(std::u16string username);
        void cleanupList(uint64_t current_tick);
        const std::vector<std::shared_ptr<Player>>& getList();
        std::optional<std::shared_ptr<Player>> findPlayer(uint32_t eid);
        std::optional<std::shared_ptr<Player>> findPlayer(PacketReturnInfo inf);
        std::optional<std::shared_ptr<Player>> findPlayer(std::u16string username);
        bool isOnline(std::u16string username);
};

#endif