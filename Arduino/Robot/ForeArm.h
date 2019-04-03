#include "Arduino.h"
#include <DynamixelSerial2.h>
#include "Setup.h"

class ForeArm
{
public:
	ForeArm();
	void MoveTo(double, double);//MoveTo
  void InitDynamixel();
  void DeploiementSaisie();
  void DeploiementDrop();
  void ParquetG();
  void ParquetD();
  void BrasTransport();

};
