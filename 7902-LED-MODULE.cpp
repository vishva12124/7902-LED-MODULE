#include <stdio.h>
#include <vector>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "PatternBase.hpp"
#include "FlashingPattern.hpp"
#include "StaticPattern.hpp"
#include "WaitCommand.hpp"
#include "drivers/ws2812.pio.h"



// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 4800

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_RX_PIN 5

#define STRIP_ONE_PIN 1
#define STRIP_TWO_PIN 2

#define STRIP_ONE_LEDS 8
#define STRIP_TWO_LEDS 20

bool irq_triggered;

std::vector<PatternBase*> patternsToRun;

void run(std::vector<PatternBase*> patternsToRun) {
    while (!irq_triggered) {
        for (PatternBase* pattern : patternsToRun) {
            pattern->periodic();
        }
    } 
}

int main() {
    stdio_init_all();

    PIO pio = pio0;
    int sm1 = 0;
    int sm2 = 1;
    uint offset = pio_add_program(pio, &ws2812_program);

    LED leftLED(pio, sm1, offset, STRIP_ONE_PIN, 800000, false, STRIP_ONE_LEDS);
    LED rightLED(pio, sm2, offset, STRIP_TWO_PIN, 800000, false, STRIP_TWO_LEDS);

    patternsToRun.push_back(new StaticPattern(leftLED, 255, 255, 255));

    run(patternsToRun);

}



