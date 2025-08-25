#ifndef FADINGPATTERN_HPP
#define FADINGPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"
#include "WaitCommand.hpp"

class FadingPattern : public PatternBase {
public:
    FadingPattern(LED& led, uint8_t r, uint8_t g, uint8_t b);
    void init() override;
    void periodic() override;
    bool isFinished() override;
    void end() override;
    WaitCommand& getWaitCommand() override;

private:
    LED& led;
    const uint8_t r, g, b;
    WaitCommand wait;
    int brightness = 0;
    int fadeInterval = 1;
    bool finished = false;         
};

#endif