#include <stdio.h>
#include <vector>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "LEDModule.hpp"
#include "PatternBase.hpp"
#include "FlashingPattern.hpp"
#include "FadingPattern.hpp"
#include "StaticPattern.hpp"
#include "RainbowPattern.hpp"
#include "MovingPattern.hpp"
#include "WaitCommand.hpp"
#include "drivers/ws2812.pio.h"
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"
#include <pico/multicore.h>

using namespace std;

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 4800

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_RX_PIN 9

#define STRIP_ONE_PIN 2
#define STRIP_TWO_PIN 28

#define STRIP_ONE_LEDS 8
#define STRIP_TWO_LEDS 20

PIO pio = pio0;
uint sm1 = 0;
uint sm2 = 1;

LED leftLED(pio, sm1, STRIP_ONE_PIN, 800000, false, STRIP_ONE_LEDS);
LED rightLED(pio, sm2, STRIP_TWO_PIN, 800000, false, STRIP_TWO_LEDS);

PatternBase* patterns[2];
PatternBase* patternsToSchedule;
bool newPatternIsScheduled = false;

void run() {
    for (PatternBase* pattern: patterns) {
        if (pattern != nullptr) {
            pattern->init();
            WaitCommand wait = pattern->getWaitCommand();
            wait.reset();
        }
    }

    while (true) {
        int i = 0;
        for (PatternBase* pattern : patterns) {
            // if (pattern == nullptr) {
            //     leftLED.testLED();
            //     continue;
            // }

            if (newPatternIsScheduled) {
                int x = 0;
                for (PatternBase* pattern : patterns) {
                    if (pattern->isFinished()) {
                        delete patterns[x];
                        patterns[x] = patternsToSchedule;
                        // delete patternsToSchedule;
                        newPatternIsScheduled = false;
                        break;
                    }
                    x++;
                }
            }

            WaitCommand& wait = pattern->getWaitCommand();
            wait.periodic();

            if (wait.isFinished()) {
                pattern->periodic();
                wait.reset();
            }

            // if (pattern->isFinished()) {
            //     delete pattern;
            //     patternsToRun[i] = nullptr;
            // }
            i++;
        }
        tight_loop_contents();
    } 
}

inline uint8_t toUnsigned(int8_t value) {
    return static_cast<uint8_t>(value);
}


void updateLights(uint8_t stripNumber, uint8_t brightness, uint8_t mode, uint8_t r, uint8_t g, uint8_t b) {

    LED* selectedLED = nullptr;
    PatternBase* newPattern = nullptr;

    switch (stripNumber) {
        case 0:
            selectedLED = &rightLED;
            break;
        case 1:
            selectedLED = &leftLED;
            break;
        default:
            selectedLED = &rightLED;
            break;
    }

    switch (mode) {
        case 1:
            patternsToSchedule = new StaticPattern(*selectedLED, r, g, b);
            break;
        case 2:
            patternsToSchedule = new FlashingPattern(*selectedLED, r, g, b);
            break;
        case 3:
            patternsToSchedule = new FadingPattern(*selectedLED, r, g, b);
            break;
        case 4:
            patternsToSchedule = new MovingPattern(*selectedLED, r, g, b);
            break;
        case 5:
            patternsToSchedule = new RainbowPattern(*selectedLED);
            break;
        default:
            patternsToSchedule = new StaticPattern(*selectedLED, r, g, b);
            break;
    }
    newPatternIsScheduled = true;
    patterns[stripNumber]->end();
}

void getUserInput() {
    while (true) {
        sleep_ms(1);
        uint8_t r,
                g,
                b,
                stripNumber,
                brightness,
                mode,
                buffer[6];

        uart_read_blocking(UART_ID, reinterpret_cast<uint8_t*>(&buffer), 6);

        stripNumber = toUnsigned(buffer[0]);
        brightness = toUnsigned(buffer[1]);
        mode = toUnsigned(buffer[2]);
        r = toUnsigned(buffer[3]);
        g = toUnsigned(buffer[4]);
        b = toUnsigned(buffer[5]);

        updateLights(stripNumber, brightness, mode, r, g, b);
    }
}

int main() {
    stdio_init_all();

    // pll_deinit(pll_usb);

    // sleep_ms(1);

    multicore_launch_core1(getUserInput);
    // irq_set_exclusive_handler(SIO_FIFO_IRQ_NUM(0), updateLights);
    // irq_set_enabled(SIO_FIFO_IRQ_NUM(0), true);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    patterns[0] = (new MovingPattern(rightLED, 255, 255, 255));
    patterns[1] = (new FadingPattern(leftLED, 0, 0, 255));

    run();
}



