#include "loggerhandler.hpp"

LoggerHandler::LoggerHandler(){
    this->logger = new Logger();
}

Logger* LoggerHandler::getLogger(){
    return logger;
}

LoggerHandler::~LoggerHandler(){
    delete this->logger;
}