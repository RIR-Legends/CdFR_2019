#include "Arduino.h"
#include "Setup.h"

class Pompes{
  public:
  Pompes();
  Pompes(int,int,int,int,int);

  void AllOn();
  void AllOff();
  void Pompe1(bool);
  void Pompe2(bool);
  void Pompe3(bool);
  void Pompe4(bool);
  void Pompe5(bool);

  private:
  int P1;
  int P2;
  int P3;
  int P4;
  int P5;
};

