#include "FadingPattern.hpp"
#include "stdio.h"

FadingPattern::FadingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(3) {
    }  
 
WaitCommand& FadingPattern::getWaitCommand() {
    return wait;
}


void FadingPattern::init() {
    // led.testLED();d
    wait.reset();    
    // led.setLED(r, g, b);
}

void FadingPattern::periodic() {
    uint8_t scaledR = (r * brightness) / 255;
    uint8_t scaledG = (g * brightness) / 255;
    uint8_t scaledB = (b * brightness) / 255;
    brightness += fadeInterval;

    led.setLED(scaledR, scaledG, scaledB);

    if (brightness <= 0 || brightness >= 255) {
        fadeInterval = -fadeInterval;
    }
}

bool FadingPattern::isFinished() {
    return finished;
}

void FadingPattern::end() {
    finished = true;
}