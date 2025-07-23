#ifndef FLASHINGPATTERN_HPP
#define FLASHINGPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class FlashingPattern : public PatternBase {
    public: 
        explicit FlashingPattern(LED led);

        void init();
        void periodic();
        bool isFinished();
        void end();
    
    private:
        LED led;

};

#endif