#include "Setup.h"
#include "Door.h"
#include "ForeArm.h"
#include "Elevator.h"

Door DoorAction;
ForeArm ForeArmAction;

void setup() {
  // put your setup code here, to run once:
  Elevator elev = Elevator(); // Crée un objet de la classe Elevator
  elev.Setup(); // Setup l'objet


//TestDoor();
TestForeArm();

}

void loop() {
  // put your main code here, to run repeatedly:

}


void TestForeArm(){
  //ForeArmAction.MoveTo(520,515);
  //ForeArmAction.InitDynamixel();
  //ForeArmAction.DeploiementSaisie();
  //ForeArmAction.DeploiementDrop();
  //ForeArmAction.ParquetG();
  //ForeArmAction.ParquetD();
  ForeArmAction.BrasTransport();
}

void TestDoor(){

DoorAction.InitDoor();
//DoorAction.OpenR();
//DoorAction.OpenL();
//DoorAction.CloseR();
//DoorAction.CloseL();

}
