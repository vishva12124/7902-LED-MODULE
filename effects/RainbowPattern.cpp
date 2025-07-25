#include "RainbowPattern.hpp"
#include "stdio.h"

//WORK IN PROGRESS (NON-FUNCTIONAL)

RainbowPattern::RainbowPattern(LED& led)
    : led(led), wait(3) {
    }  
    
void RainbowPattern::init() {
    wait.reset();
    led.setLED(r, g, b);
}

void RainbowPattern::periodic() {
    wait.periodic();

    bool timerDone = wait.isFinished();

    if (timerDone) {
        uint8_t scaledR = (r * brightness) / 255;
        uint8_t scaledG = (g * brightness) / 255;
        uint8_t scaledB = (b * brightness) / 255;
        brightness += fadeInterval;

        led.setLED(scaledR, scaledG, scaledB);

        if (brightness <= 0 || brightness >= 255) {
            fadeInterval = -fadeInterval;
        }
        wait.reset();
    }
}

bool RainbowPattern::isFinished() {
    return false;
}

void RainbowPattern::end() {}