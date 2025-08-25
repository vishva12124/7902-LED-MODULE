#ifndef RAINBOWPATTERN_HPP
#define RAINBOWPATTERN_HPP

#include "PatternBase.hpp"
#include "LED.hpp"
#include "WaitCommand.hpp"

class RainbowPattern : public PatternBase {
public:
    RainbowPattern(LED& led);
    void init() override;
    void periodic() override;
    bool isFinished() override;
    void end() override;
    WaitCommand& getWaitCommand() override;

private:
    struct RGB {
        unsigned char r, g, b;
    };
    LED& led;
    uint8_t r, g, b;
    WaitCommand wait;
    int brightness = 0;
    int fadeInterval = 1;
    bool finished = false;         
    static RGB getWaveColor(float time, float phaseOffsetR, float phaseOffsetG, float phaseOffsetB);
};

#endif