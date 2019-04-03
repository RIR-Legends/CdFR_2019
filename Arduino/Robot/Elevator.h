#include "Arduino.h"
#include "Setup.h"
#include <TimerOne.h>


int NbTick;
bool State;
bool MoteurAvance;

class Elevator{
  public:
  Elevator();
  void Setup();
  void UnTick();

  private:
  int ENA;
  int DIR;
  int PUL;

  int SWT;
};
