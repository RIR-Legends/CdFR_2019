#ifndef ELEVATOR_ACTION
#define ELEVATOR_ACTION

#include "Arduino.h"
#include "Setup.h"


class Elevator{
  public:
  Elevator();
  void Setup();
  void Move(int, bool);
  void InitialPosition();
  int getPosition();
  void MoveTo(int);
  void GoToFloor(int);
  void GoOut(int);
  void GetPaletFloor();
  void GetPaletWall();
  void GetOutPalet();
  void Transport();


  private:
  static int ENA;
  static int DIR;
  static int PUL;

  static int SWT;

  static int NbTick;
  static int Position;

};
#endif
