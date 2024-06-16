#ifndef SERVERTIMEUTIL_H
#define SERVERTIMEUTIL_H

#include <chrono>

struct TimeUtil{
    static std::chrono::high_resolution_clock Clock;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
    std::chrono::milliseconds delay;
    uint64_t s_tick;
    uint64_t l_tick;
    //TODO implement starting tick when world is saved as to have continuity between sessions.
};

#endif