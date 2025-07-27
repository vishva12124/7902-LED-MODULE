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
#include "hardware/pll.h"
#include "hardware/clocks.h"
#include "hardware/structs/pll.h"
#include "hardware/structs/clocks.h"

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

bool irq_triggered = false;

PIO pio = pio0;
uint sm1 = 0;
uint sm2 = 1;

uint8_t stripNumber = 0;
uint8_t brightness = 0;
uint8_t mode = 0;
uint8_t RGB[3];
uint8_t r, g, b;

static int vectorSize = 0; //debugging purposes

PatternBase* patternsToRun[2];

LED leftLED(pio, sm1, STRIP_ONE_PIN, 800000, false, STRIP_ONE_LEDS);
LED rightLED(pio, sm2, STRIP_TWO_PIN, 800000, false, STRIP_TWO_LEDS);
LED* selectedLED = nullptr;

void run() {
    for (PatternBase* pattern: patternsToRun) {
        pattern->init();
    }

    while (!irq_triggered) {
        int i = 0;
        for (PatternBase* pattern : patternsToRun) {
            if (pattern == nullptr) {
                continue;
            }
            pattern->periodic();
            // vectorSize = patternsToRun.size(); //debugging purposes
            if (pattern->isFinished()) {
                // patternsToRun.erase(patternsToRun.begin() + (i - 1));
                delete pattern;
                patternsToRun[i] = nullptr;
            }
            i++;
        }
    } 
}

void getUserInput() {
    RGB[0] = RGB[1] = 0;
    uart_read_blocking(UART_ID, &stripNumber, 1);
    uart_read_blocking(UART_ID, &brightness, 1);
    uart_read_blocking(UART_ID, &mode, 1);
    uart_read_blocking(UART_ID, RGB, 2);
    r = RGB[0] + RGB[1];
    uart_read_blocking(UART_ID, RGB, 2);
    g = RGB[0] + RGB[1];
    uart_read_blocking(UART_ID, RGB, 2);
    b = RGB[0] + RGB[1];

    // sleep_ms(1);

    printf("\nSTRIP: %d\n", stripNumber);
    printf("Mode: %d\n", mode);
    printf("R: %d\n", r);
    printf("G: %d\n", g);
    printf("B: %d\n", b);

    switch (stripNumber) {
        case 0:
            selectedLED = &rightLED;
            break;
        case 1:
            selectedLED = &leftLED;
            break;
        // default:
        //     selectedLED = &rightLED;
        //     break;
    }

    delete patternsToRun[stripNumber];

    switch (mode) {
        case 1:
            patternsToRun[stripNumber] = (new FadingPattern(*selectedLED, r, g, b));
            break;
        case 2:
            patternsToRun[stripNumber] = (new MovingPattern(*selectedLED, r, g, b));
            selectedLED->testLED();
            break;
    }
}

int main() {

    stdio_init_all();

    // pll_deinit(pll_usb);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    irq_set_exclusive_handler(UART1_IRQ, getUserInput);
    irq_set_enabled(UART1_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);  // RX IRQ only

    // patternsToRun.push_back(new FadingPattern(leftLED, 0, 0, 255));
    // // patternsToRun.push_back(new WaitCommand(100));
    // patternsToRun.push_back(new MovingPattern(rightLED, 255, 255, 255));

    patternsToRun[0] = (new MovingPattern(rightLED, 255, 255, 255));
    patternsToRun[1] = (new FadingPattern(leftLED, 0, 0, 255));
    // patternsToRun.push_back(new WaitCommand(100));

    run();
}



