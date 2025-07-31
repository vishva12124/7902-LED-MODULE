#include "FadingPattern.hpp"
#include "stdio.h"

FadingPattern::FadingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(3) {
        led.testLED();
        wait.reset();
        // led.setLED(r, g, b);
        // init();
    }  
    
void FadingPattern::init() {
    // led.testLED();
    wait.reset();    
    led.setLED(r, g, b);
}

void FadingPattern::periodic() {
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

bool FadingPattern::isFinished() {
    return false;
}

void FadingPattern::end() {}