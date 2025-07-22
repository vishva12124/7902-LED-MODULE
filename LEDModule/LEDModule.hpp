#ifndef LEDMODULE_HPP
#define LEDMODULE_HPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "generated/ws2812.pio.h"


class LEDModule {

    public: 
        enum LEDState {
            OFF,
            STATIC,
            BLINKING,
            RGBWAVE,
            PATTERN
        };

        LEDModule(PIO pio, int sm, uint offset, int pin, float freq, bool isRGBW, int NUM_PIXELS);

        void run(LEDState mode);

        void run(LEDState mode, uint r, uint g, uint b);

    private:
        const PIO pio;
        const int sm;
        const int NUM_PIXELS;

        struct LEDValues {
            uint r;
            uint g;
            uint b;
        };

        LEDValues RGB[];

        void setStaticColour(uint r, uint g, uint b);
        
        void setColour(LEDValues rgb[]);

        void setColour(uint r, uint g, uint b);

        inline void put_pixel(uint32_t pixel_grb);

        inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
};

#endif
