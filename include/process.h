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
  Process() : _pid(-1), _util(0) { };
  Process(int t_pid) : _pid(t_pid), _util(0) { };
  void Pid(int i) { _pid = i;};
  int Pid();                               // See src/process.cpp
  int Pid() const;
  std::string User();                      // See src/process.cpp
  std::string Command();                   // See src/process.cpp
  float CpuUtilization();                  // See src/process.cpp
  std::string Ram();                       // See src/process.cpp
  long int UpTime();                       // See src/process.cpp
  bool operator<(Process const& a) const;  // See src/process.cpp
  bool operator==(Process const& a) const;  // See src/process.cpp
  float CpuUtilization() const {return _util;}
  void calcCpuUtil();

  // Declare any necessary private members
 private:
    int _pid;
    float _util;
};

#endif