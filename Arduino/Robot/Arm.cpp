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
  ForeArmAction.DeploiementSaisieFloor();
  delay(1000);
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

void Arm::TakePaletFloor(int floorNb, bool cote){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  ElevatorRobot.GetPaletFloor();
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
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  DoorAction.CloseAll();
}


void Arm::TakePaletWall(int floorNb, bool cote){
  DoorAction.OpenAll();
  ElevatorRobot.GoToFloor(6);
  delay(500);
  ForeArmAction.DeploiementSaisieWall();
  delay(500);
  ElevatorRobot.GetPaletWall();
  delay(500);
  PompeRobot.Open();
  delay(500);
  ElevatorRobot.GoToFloor(7);
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  if(cote == true){
    ForeArmAction.ParquetG();
  }else{
    ForeArmAction.ParquetD();
  }
  delay(1000);
  ElevatorRobot.GoToFloor(floorNb);
  PompeRobot.Close();
  delay(500);
  ElevatorRobot.GoOut(6);
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  DoorAction.CloseAll();
}


void Arm::OutPaletWall(int floorNb, bool cote){
  DoorAction.OpenAll();
  delay(500);
  ElevatorRobot.GoToFloor(7);
  if(cote == true){
    ForeArmAction.ParquetG();
  }else{
    ForeArmAction.ParquetD();
  }
  delay(1000);
  ElevatorRobot.GoToFloor(floorNb);
  delay(500);
  PompeRobot.Open();
  delay(500);
  ElevatorRobot.GoToFloor(7);
  delay(500);
  ForeArmAction.DeploiementSaisieWall();
  delay(500);
  ElevatorRobot.GetPaletWall();
  delay(500);
  PompeRobot.Close();

  
//  ElevatorRobot.GoToFloor(6);
//  delay(500);
//  ForeArmAction.DeploiementSaisieWall();
//  delay(500);
//  delay(500);
//  PompeRobot.Open();
//  delay(500);
//  ElevatorRobot.GoToFloor(7);
//  delay(500);
//  ForeArmAction.DeploiementSaisieFloor();
//  delay(500);
//  if(cote == true){
//    ForeArmAction.ParquetG();
//  }else{
//    ForeArmAction.ParquetD();
//  }
//  delay(1000);
//  ElevatorRobot.GoToFloor(floorNb);
//  delay(500);
//  ElevatorRobot.GoOut(6);
//  delay(500);
//  ForeArmAction.DeploiementSaisieFloor();
//  delay(500);
//  DoorAction.CloseAll();
}

void Arm::OutPaletFloor(int floorNb, bool cote){
  
}

void Arm::ChoixPileStock(){
  
}

void Arm::ChoixPileDeStock(){
  
}
