#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/uart.h"

class LED {
    public: 
        LED(PIO pio, uint sm, uint offset, int pin, float freq, bool isRGBW, int NUM_PIXELS);
};