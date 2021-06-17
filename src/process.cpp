#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return _pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() {
    auto tot_time = LinuxParser::ActiveJiffies(_pid);
    auto up_time = LinuxParser::UpTime();
    auto proc_up_time = LinuxParser::UpTime(_pid);
    auto hrtz = LinuxParser::Jiffies();
    float time_in_sec = float(up_time) - float(proc_up_time/hrtz);
    return  (float(tot_time/hrtz)/time_in_sec);
    }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(_pid); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(_pid); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(_pid); }

// Return the age of this process (in seconds)
long int Process::UpTime() { 
    return long(LinuxParser::UpTime() - (LinuxParser::UpTime(_pid)/LinuxParser::Jiffies())); 
}

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return (this->getCpuUtil() < a.getCpuUtil() ? true : false); }