#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System {
 public:
  Processor& Cpu();                   // See src/system.cpp
  std::vector<Process>& Processes();  // See src/system.cpp
  float MemoryUtilization();          // See src/system.cpp
  long UpTime();                      // See src/system.cpp
  int TotalProcesses();               // See src/system.cpp
  int RunningProcesses();             // See src/system.cpp
  std::string Kernel();               // See src/system.cpp
  std::string OperatingSystem();      // See src/system.cpp
  static bool customSort(Process p1, Process p2) { return p1 > p2; }

  // Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif