#include <iostream>

#include "../src/helpers/server_settings.hpp"

int main(){
    ServerSettings settings;

    for(auto t: settings.getSettings()){
        std::cout << t.first +" "+ t.second + "\n";
    }
    return 0;
}