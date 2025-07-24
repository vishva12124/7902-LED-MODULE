#ifndef FLASHINGPATTERN_HPP
#define FLASHINGPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class FlashingPattern : public PatternBase {
    public: 
        explicit FlashingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b);

        void init();
        void periodic();
        bool isFinished();
        void end();
    
    private:
        LED led;
        const uint8_t r;
        const uint8_t g;
        const uint8_t b;    
};

#endif