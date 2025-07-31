#ifndef PATTERNBASE_HPP
#define PATTERNBASE_HPP

class PatternBase {
  
    public:
        PatternBase();            
        virtual ~PatternBase();
        virtual void init() = 0;
        virtual void periodic() = 0;
        virtual bool isFinished() = 0;
        virtual void end() = 0;

};
#endif