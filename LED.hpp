#ifndef LED_HPP
#define LED_HPP

#include "pico/stdlib.h" 
#include "hardware/pio.h" 

class LED {
    public: 
        LED(PIO pio, uint sm, uint offset, int pin, float freq, bool isRGBW, int NUM_PIXELS);
        void setLED(uint8_t r, uint8_t g, uint8_t b);

    private:
        const PIO pio;
        const uint sm;
        const int NUM_PIXELS;
        int incrementor;
        inline void put_pixel(uint32_t pixel_grb);
        inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
};
#endif