#ifndef MOVINGPATTERN_HPP
#define MOVINGPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"
#include "WaitCommand.hpp"

class MovingPattern : public PatternBase {
public:
    MovingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b);
    void init() override;
    void periodic() override;
    bool isFinished() override;
    void end() override;

private:
    LED& led;
    const int ledCount;
    LED::RGB rgb[0];
    const uint8_t r, g, b;
    WaitCommand wait;
    int brightness = 0;
    int fadeInterval = 1;
};

#endif