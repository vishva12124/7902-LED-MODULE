#include "RainbowPattern.hpp"
#include "stdio.h"
#include <cmath> 

//WORK IN PROGRESS (NON-FUNCTIONAL)

RainbowPattern::RainbowPattern(LED& led)
    : led(led), wait(3) {
    }  
    
WaitCommand& RainbowPattern::getWaitCommand() {
    return wait;
}

RainbowPattern::RGB RainbowPattern::getWaveColor(float time, float phaseOffsetR, float phaseOffsetG, float phaseOffsetB) {
    RainbowPattern::RGB c;
    c.r = static_cast<unsigned char>((sin(time + phaseOffsetR) + 1.0) * 127.5);
    c.g = static_cast<unsigned char>((sin(time + phaseOffsetG) + 1.0) * 127.5);
    c.b = static_cast<unsigned char>((sin(time + phaseOffsetB) + 1.0) * 127.5);
    return c;
}

void RainbowPattern::init() {
    // led.setLED(r, g, b);
}

void RainbowPattern::periodic() {
    float currentTime = time_us_64() / 1e6f * 2.0f; 
    RGB currentColor = getWaveColor(currentTime, 0.0, 2.0 * M_PI / 3.0, 4.0 * M_PI / 3.0);
    led.setLED(currentColor.r, currentColor.g, currentColor.b);
}

bool RainbowPattern::isFinished() {
    return false;
}

void RainbowPattern::end() {}