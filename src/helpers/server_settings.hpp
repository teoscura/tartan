#ifndef SERVER_SETTINGS_H
#define SERVER_SETTINGS_H

#include <map>
#include <string>

class ServerSettings{

    //FIXME works acceptably for now, should convert this to use Boost's Program Options library

    private:
        std::map<std::string, std::string> settings;
        static inline std::map<std::string, std::string> defaults = {
            {"max_players"   ,"10"},
            {"thr_foreach_player","5"},
            {"server_ip"     ,"127.0.0.1"},
            {"server_port"   ,"25565"},
            {"view_distance" ,"3"},
            {"world_type"    ,"flatland"},
        };
    public:
        //FIXME change methods such taht only one setting get method is there, if request isnt present in custom settings
        //then send default value, not anything else.
        static std::map<std::string, std::string> getDefaultSettings();
        std::map<std::string, std::string> getSettings();

        ServerSettings();
        ~ServerSettings();
};

#endif