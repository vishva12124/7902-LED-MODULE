#include "MovingPattern.hpp"
#include "stdio.h"

MovingPattern::MovingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(50), ledCount(led.getNumOfLEDS()) {
    }  
    
void MovingPattern::init() {
    wait.reset();
    led.setLED(0, 0, 0);
    counter = 0;
    incrementor = 1;
}

void MovingPattern::periodic() {
    wait.periodic();

    bool timerDone = wait.isFinished();

    if (timerDone) {
        led.setLED(counter, r, g, b);
        counter += incrementor;

        if (counter >= ledCount - 1 || counter <= 0) {
            incrementor = -incrementor;
        }
        wait.reset();
    }
}

bool MovingPattern::isFinished() {
    return false;
}

void MovingPattern::end() {}