#include "processor.h"

Processor::Processor() {_timer.start();}

// Return the aggregate CPU utilization
float Processor::Utilization() { 
    if(_timer.time() > 0.5) {
        _timer.start();
        int newTotal(0), newIdle, total, idle;
        auto raw = LinuxParser::CpuUtilization();
        for(int i=0; i<=LinuxParser::CPUStates::kSteal_;i++)
            newTotal += std::stoi(raw.at(i));
        newIdle = std::stoi(raw.at(LinuxParser::CPUStates::kIdle_)) + std::stoi(raw.at(LinuxParser::CPUStates::kIOwait_));
        total = newTotal - _prevTotal;
        idle = newIdle - _prevIdle;

        _prevTotal = newTotal;
        _prevIdle = newIdle;
        if(total != 0)
            _prevUtilization = float((total-idle))/float(total);
    }
    return _prevUtilization;
}