#include "server_settings.hpp"

#include <fstream>

std::map<std::string,std::string> ServerSettings::getDefaultSettings(){
    return defaults;
}

std::map<std::string, std::string> ServerSettings::getSettings(){
    return this->settings;
}

ServerSettings::ServerSettings(){
    std::string key, value;
    std::fstream reader("./server_preferences.txt", std::fstream::in);

    while( reader >> key >> value ) {
        this->settings[key] = value; // input them into the map 
    }

    //check for missing settings and set them to defaults.
    for(auto k : this->defaults){
        if(!this->settings.contains(k.first)){
            this->settings[k.first] = k.second;
        }
    }
}

ServerSettings::~ServerSettings(){
    std::fstream reader("./server_preferences.txt", std::fstream::out);
    std::string tmp;
    for(auto t : this->settings){
        tmp.clear();
        tmp = t.first+" "+t.second+"\n";
        reader.write(tmp.c_str(), tmp.length());
    }
    reader.close();
}
    