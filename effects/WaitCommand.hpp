#ifndef WAITCOMMAND_HPP
#define WAITCOMMAND_HPP

#include "PatternBase.hpp"
#include "LED.hpp"

class WaitCommand : public PatternBase {
    public: 
        explicit WaitCommand(LED led);

        void init();
        void periodic();
        bool isFinished();
        void end();

    private:
        LED led;     

};

#endif