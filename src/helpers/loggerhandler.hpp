#ifndef LOGGERHANDLER_H
#define LOGGERHANDLER_H

#include "logger.hpp"

class LoggerHandler{
    private:
        static inline Logger *logger;
    public:
        LoggerHandler();
        static Logger* getLogger();
        ~LoggerHandler();
};

#endif