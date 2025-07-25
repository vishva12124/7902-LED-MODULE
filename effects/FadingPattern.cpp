#include "FadingPattern.hpp"
#include "stdio.h"

FadingPattern::FadingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(3) {
    }  
    
void FadingPattern::init() {
    wait.reset();
    led.setLED(r, g, b);
}

void FadingPattern::periodic() {
    wait.periodic();

    bool timerDone = wait.isFinished();

    if (timerDone) {
        r--;
        g--;
        b--;
        led.setLED(r, g, b);
        wait.reset();
    }
}

bool FadingPattern::isFinished() {
    return false;
}

void FadingPattern::end() {}