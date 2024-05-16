#include "logger.hpp"

Logger::Logger(){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "./logs/L-%X-%d\\%m\\%Y.txt", &tstruct);
    std::string filename(buf);

    this->log = std::ofstream(filename);
}

Logger::~Logger(){
    this->log.close();
}