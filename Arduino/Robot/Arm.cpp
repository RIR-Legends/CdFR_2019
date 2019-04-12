#include "Arm.h"

Arm::Arm(){

}

void Arm::SetArm(){

  SetupRobot.SetElevator();
  SetupRobot.SetPomp();
  
}

void Arm::InitArm(){
  DoorAction.OpenAll();
  delay(500);
  SetArm();
  delay(500);
  ForeArmAction.DeploiementSaisie();
  ElevatorRobot.InitialPosition();
  Parking();
  DoorAction.CloseAll();
}

void Arm::Parking(){
  ElevatorRobot.Transport();
  ForeArmAction.InitDynamixel();
}

void Arm::Transport(){
    ForeArmAction.BrasTransport();
    DoorAction.CloseAll();
    ElevatorRobot.Transport();
}

void Arm::TakePalet(int floorNb, bool cote){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisie();
  ElevatorRobot.GetPalet();
  delay(500);
  PompeRobot.Open();
  delay(500);
  ElevatorRobot.GoToFloor(floorNb+1);
  if(cote == true){
    ForeArmAction.ParquetG();
  }else{
    ForeArmAction.ParquetD();
  }
  delay(1000);
  ElevatorRobot.GoToFloor(floorNb);
  PompeRobot.Close();
  delay(500);
  ElevatorRobot.GoOut(floorNb);
  delay(500);
  ForeArmAction.DeploiementSaisie();
  delay(500);
  DoorAction.CloseAll();
}
