#include "FlashingPattern.hpp"
#include "stdio.h"

FlashingPattern::FlashingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(500) {
        FlashingPattern::init();
    }  
 
WaitCommand& FlashingPattern::getWaitCommand() {
    return wait;
}    

void FlashingPattern::init() {
    wait.reset();
    // led.setLED(r, g, b);
}

void FlashingPattern::periodic() {
    if (isBlank) {
        led.setLED(r, g, b);
    } else {
        led.setLED(0, 0, 0);
    }
    isBlank = !isBlank;
    wait.reset();
}

bool FlashingPattern::isFinished() {
    return false;
}

void FlashingPattern::end() {}