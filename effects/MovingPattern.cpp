#include "MovingPattern.hpp"
#include "stdio.h"

int counter = 0;
int incrementor = 1;

MovingPattern::MovingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(50), ledCount(led.getNumOfLEDS()) {
    }  
    
void MovingPattern::init() {
    wait.reset();
    led.testLED();
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

    // led.setLED(5, r, g, b);
}

bool MovingPattern::isFinished() {
    return false;
}

void MovingPattern::end() {}