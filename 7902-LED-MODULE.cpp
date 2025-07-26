#include <stdio.h>
#include <vector>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "PatternBase.hpp"
#include "FlashingPattern.hpp"
#include "FadingPattern.hpp"
#include "StaticPattern.hpp"
#include "RainbowPattern.hpp"
#include "MovingPattern.hpp"
#include "WaitCommand.hpp"
#include "drivers/ws2812.pio.h"
using namespace std;

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 4800

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_RX_PIN 5

#define STRIP_ONE_PIN 2
#define STRIP_TWO_PIN 28

#define STRIP_ONE_LEDS 8
#define STRIP_TWO_LEDS 20

bool irq_triggered = false;

static int vectorSize = 0; //debugging purposes

vector<PatternBase*> patternsToRun;

void run(LED led) {
    for (PatternBase* pattern: patternsToRun) {
        pattern->init();
    }

    while (true) {
            int i = 0;
            for (PatternBase* pattern : patternsToRun) {
                pattern->periodic();
                vectorSize = patternsToRun.size(); //debugging purposes
                if (pattern->isFinished()) {
                    patternsToRun.erase(patternsToRun.begin() + (i - 1));
                    delete pattern;
                }
                i++;
            }
    } 
}

int main() {

    stdio_init_all();

    PIO pio = pio0;
    uint sm1 = 0;
    uint sm2 = 1;

    LED leftLED(pio, sm1, STRIP_ONE_PIN, 800000, false, STRIP_ONE_LEDS);
    LED rightLED(pio, sm2, STRIP_TWO_PIN, 800000, false, STRIP_TWO_LEDS);

    patternsToRun.push_back(new StaticPattern(leftLED, 0, 0, 255));
    // patternsToRun.push_back(new WaitCommand(100));
    patternsToRun.push_back(new MovingPattern(rightLED, 255, 255, 255));

    run(leftLED);
}



