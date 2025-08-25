#ifndef LED_HPP
#define LED_HPP

#include "pico/stdlib.h" 
#include "hardware/pio.h" 

class LED {
    public: 
        LED(int pin, int NUM_PIXELS, float freq, bool isRGBW);
        LED(int pin, int NUM_PIXELS, float freq);
        LED(int pin, int NUM_PIXELS, bool isRGBW);
        LED(int pin, int NUM_PIXELS);

        struct RGB {
            uint8_t r;
            uint8_t g;
            uint8_t b;
        };
        
        void init(uint pin, float freq = 800000, bool isRGBW = false);
        void setLED(uint8_t r, uint8_t g, uint8_t b);
        void setLED(int index, uint8_t r, uint8_t g, uint8_t b);
        void setLED(RGB rgb[]);
        void testLED();
        int getNumOfLEDS();

    private:
        const int NUM_PIXELS;
        PIO pio;
        uint sm;
        inline void put_pixel(uint32_t pixel_grb);
        inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
        bool turnLEDOn;
};
#endif