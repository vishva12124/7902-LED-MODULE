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
    WaitCommand& getWaitCommand() override;

private:
    LED& led;
    const int ledCount;
    const uint8_t r, g, b;
    WaitCommand wait;
    int brightness = 0;
    int counter = 0;
    int incrementor = 1;
};

#endif