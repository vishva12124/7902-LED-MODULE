#include "StaticPattern.hpp"
#include "LED.hpp"

StaticPattern::StaticPattern(LED& led, uint8_t r, uint8_t g, uint8_t b):
    led(led),
    r(r),
    g(g),
    b(b) {}

void StaticPattern::init() {}
void StaticPattern::periodic() {
    led.setLED(r, g, b);
}

bool StaticPattern::isFinished() {
    return true;
}
void StaticPattern::end(){}