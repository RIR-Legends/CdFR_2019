#ifndef FOREARM_ACTION
#define FOREARM_ACTION

#include "Arduino.h"
#include <DynamixelSerial2.h>
#include "Setup.h"

class ForeArm
{
public:
	ForeArm();
	void MoveTo(double, double);//MoveTo
  void InitDynamixel();
  void DeploiementSaisieFloor();
  void DeploiementDrop();
  void ParquetG();
  void ParquetD();
  void BrasTransport();
  void DeploiementSaisieWall();

};
#endif
