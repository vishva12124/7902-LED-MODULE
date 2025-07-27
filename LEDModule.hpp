#include "LED.hpp"
#include "PatternBase.hpp"
#include <vector>
using namespace std;


class LEDModule {
    public:
        void run(LED led);
        void getUserInput();
        int main();

    private:
        LED rightLED;
        LED leftLED;
        uint8_t stripNumber = 0;
        uint8_t brightness = 0;
        uint8_t mode = 0;
        uint8_t RGB[3];
        int vectorSize = 0; //debugging purposes
        bool irq_triggered = false;
        vector<PatternBase*> patternsToRun;
};


