#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <linux_parser.h>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int t_pid) : _pid(t_pid), _util(0) { };
  int Pid();                               // See src/process.cpp
  std::string User();                      // See src/process.cpp
  std::string Command();                   // See src/process.cpp
  float CpuUtilization();                  // See src/process.cpp
  std::string Ram();                       // See src/process.cpp
  long int UpTime();                       // See src/process.cpp
  bool operator<(Process const& a) const;  // See src/process.cpp
  float getCpuUtil() const {return _util;}

  // Declare any necessary private members
 private:
    int _pid;
    float _util;
};

#endif