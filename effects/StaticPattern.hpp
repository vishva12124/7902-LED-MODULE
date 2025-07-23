#ifndef STATICPATTERN_HPP
#define STATICPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class StaticPattern : public PatternBase {
    public: 
        explicit StaticPattern(LED led);

        void init();
        void periodic();
        bool isFinished();
        void end();

    private:
        LED led;    


};

#endif