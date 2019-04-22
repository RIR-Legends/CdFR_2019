//#include "Setup.h"
//#include "Door.h"
//#include "ForeArm.h"
//#include "Elevator.h"
//#include "Pompe.h"
#include "Arm.h"

Door DoorAction;
ForeArm ForeArmAction;
Setup SetupRobot;
Elevator ElevatorRobot;
Pompe PompeRobot;
Arm ArmRobot; 

void setup() {
  // put your setup code here, to run once:

  //SetupRobot.SetElevator();
  //SetupRobot.SetPomp();
  ArmRobot.InitArm();
  delay(2000);

    Serial.begin(9600);


//TestDoor();
//TestForeArm();
//TestElevator();
//TestPomp();
TestArm();


}

void loop() {

 
}

void TestArm(){
//  ArmRobot.Transport();
//  delay(1000);
//  ArmRobot.TakePaletFloor(1,0);
//  delay(500);
//  ArmRobot.TakePaletFloor(2,0);
//  delay(500);
//  ArmRobot.TakePaletFloor(3,0);
//  delay(500);
//  ArmRobot.TakePaletFloor(4,0);
//  delay(500);
//  ArmRobot.TakePaletFloor(5,0);
//  delay(500);

  //ArmRobot.Transport();
  delay(1000);
  ArmRobot.TakePaletWall(1,0);
  delay(500);
//  ArmRobot.TakePaletWall(2,0);
//  delay(500);
//  ArmRobot.TakePaletWall(3,0);
//  delay(500);
//  ArmRobot.TakePaletWall(4,0);
//  delay(500);
//  ArmRobot.TakePaletWall(5,0);
  delay(500);


  

}

void TestPomp(){
  PompeRobot.Open();
  delay(1000);
  PompeRobot.Close();
}


void TestElevator(){
  //ElevatorRobot.Move(200,LOW);
  //ElevatorRobot.InitialPosition();
  //delay(1000);
  //ElevatorRobot.MoveTo(800);
  //ElevatorRobot.GoToFloor(5);
  //ElevatorRobot.GetPaletFloor();
   //ElevatorRobot.GetPaletWall();
  //ElevatorRobot.GetOutPalet();
  //ElevatorRobot.Transport();
  Serial.println(ElevatorRobot.getPosition());
  delay(1000);
 

}

void TestForeArm(){
  //ForeArmAction.MoveTo(520,515);
  //ForeArmAction.InitDynamixel();
  //ForeArmAction.DeploiementSaisieFloor();
  //ForeArmAction.DeploiementDrop();
  ForeArmAction.DeploiementSaisieWall();
  //ForeArmAction.ParquetG();
  //ForeArmAction.ParquetD();
  //ForeArmAction.BrasTransport();
}

void TestDoor(){

DoorAction.InitDoor();
//DoorAction.OpenR();
//DoorAction.OpenL();
//DoorAction.CloseR();
//DoorAction.CloseL();
//DoorAction.OpenAll();
//DoorAction.CloseAll();

}
