#include "../src/helpers/loggerhandler.hpp"

int main(){
    LoggerHandler lh;
    auto lg = LoggerHandler::getLogger();
    int a = 10;
    lg->LogPrint(DATA, "this is a number: {}, and a string: {}", a, "cagasbusb");
    lg->LogPrint(DATA, "this is a number: {}, and a string: {}", a, "cagasbusb");
    lg->LogPrint(DATA, "this is a number: {}, and a string: {}", a, "cagasbusb");
    lg->LogPrint(DATA, "this is a number: {}, and a string: {}", a, "cagasbusb");
    return 0;
}