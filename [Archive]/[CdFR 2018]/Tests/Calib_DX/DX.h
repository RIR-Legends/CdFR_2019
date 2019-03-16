#include "Arduino.h"
#include "Setup.h"
#include <DynamixelSerial2.h>

class Dynamixels
{
  public:
  Dynamixels();

  void Parking();
  void SortieBras();
  void DescenteMain();
  void RemonteMain();
  void Turn90();
};

