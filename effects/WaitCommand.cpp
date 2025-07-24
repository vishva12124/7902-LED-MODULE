#include "WaitCommand.hpp"
#include "LED.hpp"

WaitCommand::WaitCommand(LED led, double ms):
    led(led),
    ms(ms) {}

void init();
void periodic();
bool isFinished();
void end();  

