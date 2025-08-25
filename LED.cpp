
#include "pico/stdlib.h" 
#include "hardware/pio.h"
#include "drivers/ws2812.pio.h"
#include "LED.hpp" 


LED::LED(int pin, int NUM_PIXELS, float freq, bool isRGBW) :
    NUM_PIXELS(NUM_PIXELS),
    turnLEDOn(true) {
        init(pin, freq, isRGBW);
}

LED::LED(int pin, int NUM_PIXELS, float freq) :
    NUM_PIXELS(NUM_PIXELS),
    turnLEDOn(true) {
        init(pin, freq);
}

LED::LED(int pin, int NUM_PIXELS, bool isRGBW) :
    NUM_PIXELS(NUM_PIXELS),
    turnLEDOn(true) {
        init(pin, 800000, isRGBW);
}

LED::LED(int pin, int NUM_PIXELS) :
    NUM_PIXELS(NUM_PIXELS),
    turnLEDOn(true) {
        init(pin);
}

void LED::init(uint pin, float freq, bool isRGBW) {
    pio = pio0;
    sm = pio_claim_unused_sm(pio, false);

    if (sm < 0) {
        pio = pio1;
        sm = pio_claim_unused_sm(pio, false);
    }

    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, pin, freq, isRGBW);
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
}

int LED::getNumOfLEDS() {
    return NUM_PIXELS;
}

void LED::testLED() {
    gpio_put(25, turnLEDOn);
    turnLEDOn = !turnLEDOn;
}

void LED::setLED(uint8_t r, uint8_t g, uint8_t b) {
    sleep_ms(1);
    for (int i = 0; i != NUM_PIXELS; i++) {
        uint32_t colour_set = urgb_u32(r, g, b);
        put_pixel(colour_set);
    }
}

void LED::setLED(int index, uint8_t r, uint8_t g, uint8_t b) {
    sleep_ms(1);
    RGB rgb[NUM_PIXELS];

    for (int i = 0; i != NUM_PIXELS; i++) {
        if (i == index) {
            rgb[i].r = r;
            rgb[i].g = g;
            rgb[i].b = b;
        }
        
        else {
            rgb[i].r = 0;
            rgb[i].g = 0;
            rgb[i].b = 0;
        }
    }

    setLED(rgb);
}

void LED::setLED(RGB rgb[]) {
    sleep_ms(1);
    for (int i = 0; i != NUM_PIXELS; i++) {
        uint32_t colour_set = urgb_u32(rgb[i].r, rgb[i].g, rgb[i].b);
        put_pixel(colour_set);
    }
}

inline void LED::put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

inline uint32_t LED::urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)(r) << 8) |
        ((uint32_t)(g) << 16) |
        (uint32_t)(b);
}


