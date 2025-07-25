#ifndef WAITCOMMAND_HPP
#define WAITCOMMAND_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class WaitCommand : public PatternBase {
    public: 
        explicit WaitCommand(int64_t ms);

        void init();
        void periodic();
        bool isFinished();
        void end();
        void reset();

    private:
        int64_t waitTimeUs;
        absolute_time_t startTime;
        bool finished;     
};

#endif