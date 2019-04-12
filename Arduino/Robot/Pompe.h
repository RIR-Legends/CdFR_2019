#ifndef POMPE_ACTION
#define POMPE_ACTION

#include "Arduino.h"
#include "Setup.h"


class Pompe{
  public:
  Pompe();
  void Open();
  void Close();


  private:
  static int POMP;
  static int VAN;

 
};
#endif
