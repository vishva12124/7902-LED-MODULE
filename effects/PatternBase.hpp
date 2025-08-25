#ifndef PATTERNBASE_HPP
#define PATTERNBASE_HPP

#include "effects/WaitCommand.hpp"

class PatternBase {
  
    public:
        PatternBase();            
        virtual ~PatternBase();
        virtual void init() = 0;
        virtual void periodic() = 0;
        virtual bool isFinished() = 0;
        virtual void end() = 0;
        virtual WaitCommand& getWaitCommand() = 0;
};
#endif