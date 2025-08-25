#include "StaticPattern.hpp"
#include "LED.hpp"

StaticPattern::StaticPattern(LED& led, uint8_t r, uint8_t g, uint8_t b):
    led(led),
    r(r),
    g(g),
    b(b),
    wait(0) {}

WaitCommand& StaticPattern::getWaitCommand() {
    return wait;
}

void StaticPattern::init() {}
void StaticPattern::periodic() {
    led.setLED(r, g, b);
    end();
}

bool StaticPattern::isFinished() {
    return finished;
}
void StaticPattern::end(){
    finished = true;         
}