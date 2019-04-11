#include "Arduino.h"
#include <DynamixelSerial2.h>
#include "Setup.h"

class Door{
public:
	Door();
	void MoveToR(double);
	void MoveToL(double);
	void InitDoor();
	void OpenR();
	void OpenL();
	void CloseR();
	void CloseL();

};
