#ifndef WAITCOMMAND_HPP
#define WAITCOMMAND_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class WaitCommand : public PatternBase {
    public: 
        explicit WaitCommand(double ms);

        void init();
        void periodic();
        bool isFinished();
        void end();
        void reset();

    private:
        double waitTimeUs;
        absolute_time_t startTime;
        bool finished;     
};

#endif