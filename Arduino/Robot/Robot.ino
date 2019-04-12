//#include "Setup.h"
//#include "Door.h"
//#include "ForeArm.h"
//#include "Elevator.h"
//#include "Pompe.h"
#include "Arm.h"

//Door DoorAction;
//ForeArm ForeArmAction;
//Setup SetupRobot;
//Elevator ElevatorRobot;
//Pompe PompeRobot;
Arm ArmRobot; 

void setup() {
  // put your setup code here, to run once:

  //SetupRobot.SetElevator();
  //SetupRobot.SetPomp();
  ArmRobot.Setup();

    Serial.begin(9600);


//TestDoor();
//TestForeArm();
//TestElevator();
TestPomp();


}

void loop() {

 
}

void TestPomp(){
  PompeRobot.Open();
  delay(1000);
  PompeRobot.Close();
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
