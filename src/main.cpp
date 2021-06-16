#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  while(1) {
    auto processes = system.Processes();
    for (auto proc : processes) {
      proc.Pid();
      proc.User();
      proc.CpuUtilization() * 100;
      proc.Ram();
      proc.UpTime();
      proc.Command();
    }
  }
  //NCursesDisplay::Display(system);
}