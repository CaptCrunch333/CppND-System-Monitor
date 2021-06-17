#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;

  // for (int i = 0; i < n; ++i) {
  //   mvwprintw(window, ++row, pid_column, to_string(processes[i].Pid()).c_str());
  //   mvwprintw(window, row, user_column, processes[i].User().c_str());
  //   float cpu = processes[i].CpuUtilization() * 100;
  //   mvwprintw(window, row, cpu_column, to_string(cpu).substr(0, 4).c_str());
  //   mvwprintw(window, row, ram_column, processes[i].Ram().c_str());
  //   mvwprintw(window, row, time_column,
  //             Format::ElapsedTime(processes[i].UpTime()).c_str());
  //   mvwprintw(window, row, command_column,
  //             processes[i].Command().substr(0, window->_maxx - 46).c_str());
  // }
  NCursesDisplay::Display(system);
}