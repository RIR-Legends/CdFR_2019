#include "Arduino.h"
#include <TimerOne.h>

class Foo{
  public:
  Foo();
  static void Setup();
  static void Action();
  static int Return_Compteur();

  private:
  static int Compteur;

};
