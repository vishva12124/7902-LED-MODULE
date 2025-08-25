#include "LED.hpp"
#include "PatternBase.hpp"
#include <vector>
using namespace std;


class LEDModule {
    public:
        void run();
        void getUserInput();
        int main();
        void updateLights();
        inline uint8_t toUnsigned(int8_t value);

    private:
        LED rightLED;
        LED leftLED;
};


