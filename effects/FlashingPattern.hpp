#ifndef FLASHINGPATTERN_HPP
#define FLASHINGPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"
#include "WaitCommand.hpp"

class FlashingPattern : public PatternBase {
public:
    FlashingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b);
    void init() override;
    void periodic() override;
    bool isFinished() override;
    void end() override;

private:
    LED& led;
    uint8_t r, g, b;
    bool isBlank = false;
    WaitCommand wait;
};

#endif