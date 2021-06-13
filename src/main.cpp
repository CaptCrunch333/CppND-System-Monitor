#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  while(1)
    system.Cpu().Utilization();
  //NCursesDisplay::Display(system);
}