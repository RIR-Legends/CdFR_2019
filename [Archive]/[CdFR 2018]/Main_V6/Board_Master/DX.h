#include "Arduino.h"
#include <DynamixelSerial2.h>

class Dynamixels
{
  public:
  Dynamixels();

  void Parking();
  void PositionPrise();
  void DescenteMain();
  void Transport();
  void PositionDepose();
  void Rotation45();
};

