#include "Setup.h"
#include "Door.h"
#include "ForeArm.h"

Door DoorAction;
ForeArm ForeArmAction;

void setup() {
  // put your setup code here, to run once:



//TestDoor();
TestForeArm();

}

void loop() {
  // put your main code here, to run repeatedly:

}


void TestForeArm(){
  ForeArmAction.MoveTo(520,515);

}

void TestDoor(){

DoorAction.InitDoor();
//DoorAction.OpenR();
//DoorAction.OpenL();
//DoorAction.CloseR();
//DoorAction.CloseL();

}
