#include "MovingPattern.hpp"
#include "stdio.h"

MovingPattern::MovingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(40), ledCount(led.getNumOfLEDS()) {
        init();
    }  
    
WaitCommand& MovingPattern::getWaitCommand() {
    return wait;
}

void MovingPattern::init() {
    // led.setLED(0, 0, 0);
    counter = 0;
    incrementor = 1;
}

void MovingPattern::periodic() {
    led.setLED(counter, r, g, b);
    counter += incrementor;

    if (counter >= ledCount - 1 || counter <= 0) {
        incrementor = -incrementor;
    }
}

bool MovingPattern::isFinished() {
    return finished;
}

void MovingPattern::end() {
    finished = true;
}