
#include "pico/stdlib.h" 
#include "hardware/pio.h"
#include "drivers/ws2812.pio.h"
#include "LED.hpp" 

LED::LED(PIO pio, uint sm, uint offset, int pin, float freq, bool isRGBW, int NUM_PIXELS) :
    NUM_PIXELS(NUM_PIXELS),
    pio(pio),
    sm(sm) {
    ws2812_program_init(pio, sm, offset, pin, freq, isRGBW);
    incrementor = 0;
}

void LED::setLED(uint8_t r, uint8_t g, uint8_t b) {
    sleep_ms(1);
    for (; incrementor != NUM_PIXELS; incrementor++) {
        uint32_t colour_set = urgb_u32(r, g, b);
        put_pixel(colour_set);
    }
    incrementor = 0;
}

inline void LED::put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

inline uint32_t LED::urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) |
        ((uint32_t)(g) << 16) |
        (uint32_t)(b);
}


