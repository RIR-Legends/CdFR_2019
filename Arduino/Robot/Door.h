#include "Arduino.h"
#include "Setup.h"

class Door
{
public:
	Door();
	void SetupDoor();
	void MoveToR(double);
	void MoveToL(double);
	void InitDoor();
	void OpenR();
	void OpenL();
	void CloseR();
	void CloseL();

};