#ifndef MC_PLAYERLIST_H
#define MC_PLAYERLIST_H

#include "player.hpp"
#include <optional>
#include <string>
#include <vector>

struct LoginPlayer{
    std::u16string username;
    PacketReturnInfo inf;
};

class PlayerList{
    public:
        std::vector<Player> list;
        std::vector<LoginPlayer> login_list;
        void insert(Player playerin);
        void insertLogin(LoginPlayer logplayerin);
        void remove(std::u16string username);
        void cleanupLogin();
        std::optional<Player*> findPlayer(uint32_t eid);
        std::optional<Player*> findPlayer(std::u16string username);
        std::optional<LoginPlayer*> findLogin(PacketReturnInfo inf);
        bool isonline(std::u16string username);
        bool isLogin(std::u16string username);
        bool ishandshake(std::u16string username);
};



#endif