#include "Arduino.h"
#include "Setup.h"
#include <TimerOne.h>

bool State;
int NbTick;

class Elevator{
  public:
  Elevator();
  void Setup();
  void Untick();

  private:
  int ENA;
  int DIR;
  int PUL;

  int SWT;
};
