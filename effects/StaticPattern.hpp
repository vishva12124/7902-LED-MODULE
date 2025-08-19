#ifndef STATICPATTERN_HPP
#define STATICPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class StaticPattern : public PatternBase {
    public: 
        explicit StaticPattern(LED& led, uint8_t r, uint8_t g, uint8_t b);

        LED& getLED();
        void init();
        void periodic();
        bool isFinished();
        void end();
        WaitCommand& getWaitCommand() override;

    private:
        LED& led;
        WaitCommand wait;
        const uint8_t r;
        const uint8_t g;
        const uint8_t b;    
};

#endif