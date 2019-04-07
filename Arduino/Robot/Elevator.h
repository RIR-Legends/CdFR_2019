#include "Arduino.h"
#include "Setup.h"
#include <TimerOne.h>




class Elevator{
  public:
  Elevator();
  static void Setup();
  static void UnTick();
  static int RetournTimer();

  private:
  static int ENA;
  static int DIR;
  static int PUL;

  static int SWT;

  static int NbTick;
  static bool State;
  static bool MoteurAvance;
};
