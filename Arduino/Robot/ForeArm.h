#include "Arduino.h"
#include <DynamixelSerial2.h>
#include "Setup.h"

class ForeArm
{
public:
	ForeArm();
	void MoveTo(double, double, double, double);

};
