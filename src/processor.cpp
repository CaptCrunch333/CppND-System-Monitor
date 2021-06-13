#include "processor.h"

Processor::Processor() {_timer.start();}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    if(_timer.time() > 0.5) {
        _timer.start();
        int newTotal(0), newIdle, total, idle;
        auto raw = LinuxParser::CpuUtilization();
        for(int i=0; i<8;i++)
            newTotal += std::stoi(raw.at(i));
        newIdle = std::stoi(raw.at(3)) + std::stoi(raw.at(4));
        total = newTotal - _prevTotal;
        idle = newIdle - _prevIdle;

        _prevTotal = newTotal;
        _prevIdle = newIdle;
        if(total != 0)
            _prevUtilization = (total-idle)/total * 100;
    }
    std::cout << "_prevUtilization: " << _prevUtilization << std::endl;
    return _prevUtilization;
}