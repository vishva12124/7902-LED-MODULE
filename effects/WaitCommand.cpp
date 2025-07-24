#include "WaitCommand.hpp"
#include "LED.hpp"
#include <stdio.h>
#include <vector>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"

absolute_time_t  currentTime;
bool endCommand = false;

WaitCommand::WaitCommand(double ms)
    : waitTimeUs(ms * 1000), finished(false) {}
    
void WaitCommand::init() {
    currentTime = get_absolute_time();
}

void WaitCommand::periodic() {
    int64_t timeDiff = absolute_time_diff_us(currentTime, get_absolute_time());
     if (timeDiff >= waitTimeUs) {
        endCommand = true;
    }
}

void WaitCommand::reset() {
    currentTime = get_absolute_time();
    endCommand = false;
}

bool WaitCommand::isFinished() {
    return endCommand;
}
void WaitCommand::end() {}  

