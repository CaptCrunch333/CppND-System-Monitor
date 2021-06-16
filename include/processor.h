#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include "Timer.hpp"

class Processor {
 public:
 Processor();
 float Utilization(); 

 private:
    int _prevTotal = 0, _prevIdle = 0;
    float _prevUtilization = 0;
    Timer _timer;
};

#endif