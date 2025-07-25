#include "MovingPattern.hpp"
#include "stdio.h"

//WORK IN PROGRESS (NON-FUNCTIONAL)

uint8_t x = 0, i = 1;
bool direction = true;

MovingPattern::MovingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b)
    : led(led), r(r), g(g), b(b), wait(3000), ledCount(led.getNumOfLEDS()) {
        rgb[ledCount];
}  
    
void MovingPattern::init() {
    wait.reset();
    led.setLED(0, 0, 0);
}

void MovingPattern::periodic() {
    wait.periodic();

    bool timerDone = wait.isFinished();

    if (timerDone) {
        if (i == ledCount) {
            direction = false;
            x = ledCount + 1;
        }
        
        else if (i == 0 && direction == false) {
            direction = true;
            x = -1;
        }

        switch (direction) {
            case 0:
                i--;
                x--;
                break;
            case 1:
                i++;
                x++;
                break;
        }
        rgb[i].r = r;
        rgb[i].g = g;
        rgb[i].b = b;

        led.setLED(rgb);
        
        rgb[x].r = 0;
        rgb[x].g = 0;
        rgb[x].b = 0;
        
        led.setLED(rgb);
    }

    wait.reset();
}


bool MovingPattern::isFinished() {
    return false;
}

void MovingPattern::end() {}