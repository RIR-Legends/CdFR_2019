#include "Setup.h"
#include "Door.h"
#include "ForeArm.h"
#include "Elevator.h"

Door DoorAction;
ForeArm ForeArmAction;
Setup SetupRobot;
Elevator ElevatorRobot;
//Elevator elev = Elevator(); // Crée un objet de la classe Elevator


void setup() {
  // put your setup code here, to run once:

  SetupRobot.SetElevator();
  //Elevator.Setup(); // Setup l'objet
    Serial.begin(9600);


//TestDoor();
//TestForeArm();

TestElevator();

}

void loop() {

 
}

void TestElevator(){
  //ElevatorRobot.Move(200,LOW);
  ElevatorRobot.InitialPosition();
  delay(1000);
  //ElevatorRobot.MoveTo(800);
  //ElevatorRobot.GoToFloor(5);
  //ElevatorRobot.GetPalet();
  //ElevatorRobot.GetOutPalet();
  ElevatorRobot.InitPosition();
  Serial.println(ElevatorRobot.getPosition());
  delay(1000);
 

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
