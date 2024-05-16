#include "miscutil.hpp"

#include "../helpers/loggerhandler.hpp"

// Checks If a c-style string is an integer
bool is_int(char *c) {
    while (*c != '\0'){
        if (*c < '0' || *c > '9'){}
            return false;
            c++;
        } 
    return true;
}

void printSplash(){
    auto lh = LoggerHandler::getLogger();
    lh->LogPrint(NONE, "#### --------------------------------- ####\n#### --------------------------------- ####\n####      Tartan v{} - @teoscura      ####\n#### -------  >...Starting...  ------- ####\n#### --------------------------------- ####", 0.1);
}