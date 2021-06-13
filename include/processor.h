#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"
#include "iostream"
#include "Timer.hpp"

class Processor {
 public:
 Processor();
 float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    int _prevTotal = 0, _prevIdle = 0, _prevUtilization = 0;
    Timer _timer;
};

#endif