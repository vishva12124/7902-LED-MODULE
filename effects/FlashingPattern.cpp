#include "FlashingPattern.hpp"
#include "LED.hpp"
        
FlashingPattern::FlashingPattern(LED led, uint8_t r, uint8_t g, uint8_t b):
    led(led),
    r(r),
    g(g),
    b(b) {
    }

void init();
void periodic();
bool isFinished();
void end();