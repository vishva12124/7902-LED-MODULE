#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "LEDModule.hpp"
#include "generated/ws2812.pio.h"


LEDModule::LEDModule(PIO pio, uint sm, uint offset, int pin, float freq, bool isRGBW, int NUM_PIXELS):
    pio(pio),
    sm(sm),
    NUM_PIXELS(NUM_PIXELS) {
        //  bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&ws2812_program, &pio, &sm, &offset, pin, 1, true);
        // hard_assert(success);
        ws2812_program_init(pio, sm, offset, pin, freq, isRGBW);
        // RGB[NUM_PIXELS];
}

void LEDModule::run(LEDState mode) {
    
    switch (mode) {
        case RGBWAVE:
            break;
        default: 
            break;
    }
}

void LEDModule::run(LEDState mode, uint r, uint g, uint b) {
    
    switch (mode) {
        case OFF:
            break;
        case STATIC:
            setStaticColour((uint8_t)r, (uint8_t)g, (uint8_t)b);
    }
}


void LEDModule::setStaticColour(uint r, uint g, uint b) {
    setColour(r, g, b);
}

// void LEDModule::setColour(LEDValues rgb[]) {
//     sleep_ms(1);
//     for (int i = 0; i < NUM_PIXELS; i++) {
//         uint32_t colour_set = urgb_u32((rgb[i].r), (rgb[i].g), (rgb[i].b));
//         put_pixel(colour_set);
//     }
// }

void LEDModule::setColour(uint8_t r, uint8_t g, uint8_t b) {

    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t colour_set = urgb_u32(r, g, b);
        put_pixel(colour_set);
    }
}

inline void LEDModule::put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

inline uint32_t LEDModule::urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) |
        ((uint32_t)(g) << 16) |
        (uint32_t)(b);
}