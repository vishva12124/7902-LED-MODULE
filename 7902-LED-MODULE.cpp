#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "generated/ws2812.pio.h"
#include "LEDModule/LEDModule.hpp"


// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 4800

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_RX_PIN 5

#define STRIP_ONE_PIN 1


int main()
{
    stdio_init_all();

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the RX pin by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    // uart_puts(UART_ID, " Hello, UART!\n");
    // uart_set_irq_enables(UART_ID, true, false);
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    LEDModule leftLED = LEDModule(pio, sm, offset, STRIP_ONE_PIN, 800000, false, 8);

    LEDModule::LEDState staticMode = LEDModule::STATIC;
    LEDModule::LEDState blinkMode = LEDModule::BLINKING;

    while (true) {
        leftLED.run(staticMode, 255, 255, 255);
        sleep_ms(1000);
        leftLED.run(staticMode, 0, 255, 255);
        sleep_ms(1000);
    }
}

void getUserInput() {
    
}
