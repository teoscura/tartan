#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <condition_variable>
#include <format>
#include <fstream>
#include <mutex>
#include <string_view>

enum LogLevel{
    NONE,
    DATA,
    INFO,
    ERROR,
    FATAL,
};

class Logger{
    private:
        std::ofstream log;
        std::mutex logger_m;
        std::condition_variable var;
    public:
        Logger();
        ~Logger();
        template<typename ...Args> void LogPrint(const LogLevel _lvl,const char* _msg,const Args&... args);
};

template<typename ...Args>
void Logger::LogPrint(const LogLevel _lvl, const char* _msg, const Args&... args){
    std::unique_lock<std::mutex> lck(this->logger_m);
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%X|%Y-%m-%d", &tstruct);
    const char* log_levels[] = {"","DATA", "INFO", "ERROR", "FATAL"};
    auto time = std::chrono::system_clock::now();
    if(_lvl==0){
        this->log<<std::vformat(std::string_view(_msg),std::make_format_args(args...))<<std::endl;
        this->log.flush();
        lck.unlock();
        var.notify_one();
        return;    
    }
    this->log<< buf <<" [" << log_levels[_lvl] <<"] "<<std::vformat(std::string_view(_msg),std::make_format_args(args...))<<std::endl;
    this->log.flush();
    lck.unlock();
    var.notify_one();
}

#endif