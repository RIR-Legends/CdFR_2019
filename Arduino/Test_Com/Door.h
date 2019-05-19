#ifndef DOOR_ACTION
#define DOOR_ACTION

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
  void OpenAll();
  void CloseAll();

};
#endif
