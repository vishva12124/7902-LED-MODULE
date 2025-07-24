#include "FlashingPattern.hpp"
#include "WaitCommand.hpp"
#include "LED.hpp"

WaitCommand wait = WaitCommand(1000);
bool isBlank = false;

FlashingPattern::FlashingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b):
    led(led),
    r(r),
    g(g),
    b(b) {}

void FlashingPattern::init() {
    wait.reset(); 
    led.setLED(r, g, b);
}

void FlashingPattern::periodic() {
    wait.periodic();

    if (wait.isFinished() && isBlank) {
        led.setLED(0, 0, 0);
        isBlank = false;
        wait.reset();
    }

    else if (wait.isFinished() && !isBlank) {
        led.setLED(r, g, b);
        isBlank = true;
        wait.reset();
    }

}

bool FlashingPattern::isFinished() {
    return false;
}
void FlashingPattern::end() {}