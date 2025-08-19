#include "WaitCommand.hpp"

WaitCommand::WaitCommand(int64_t ms)
    : waitTimeUs(ms), finished(false) {}

void WaitCommand::init() {
    startTime = time_us_64() / 1000;
    finished = false;
}

void WaitCommand::periodic() {
    int64_t elapsed = (time_us_64() / 1000) - startTime;
    finished = elapsed >= waitTimeUs;
}

void WaitCommand::reset() {
    startTime = time_us_64() / 1000;
    finished = false;
}

bool WaitCommand::isFinished() {
    return finished;
}

void WaitCommand::end() {
    finished = true;
}