#include "Arduino.h"
#include "Setup.h"
#include <TimerOne.h>




class Elevator{
  public:
  Elevator();
  void Setup();
  static void UnTick();

  private:
  int ENA;
  int DIR;
  static int PUL;

  int SWT;

  static int NbTick;
  static bool State;
  static bool MoteurAvance;
};
