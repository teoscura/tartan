#ifndef MC_TICKER_H
#define MC_TICKER_H

#include <cstdint>

class Ticker{
    private:
        uint64_t tick;
        bool running;
        //TODO sqlite database pointer.
    public:
        Ticker();
};

#endif