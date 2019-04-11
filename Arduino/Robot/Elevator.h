#include "Arduino.h"
#include "Setup.h"


class Elevator{
  public:
  void Setup();
  void Move(int, bool);
  void InitialPosition();
  int getPosition();
  void MoveTo(int);
  void GoToFloor(int);
  void GetPalet();
  void GetOutPalet();
  void InitPosition();


  private:
  static int ENA;
  static int DIR;
  static int PUL;

  static int SWT;

  static int NbTick;
  static int Position;

};
