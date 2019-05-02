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



//////////////////////////////////////////////////////////////////////Take a Palet to the floor//////////////////////////////////////////////////////////////////////////
void Arm::PreTakePaletFloor(){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
}

void Arm::TakePaletFloor(int floorNb, bool cote){
  //Rappel et verif qu'il ai fait le preTake
  DoorAction.OpenAll();
  ForeArmAction.DeploiementSaisieFloor();
  //Puis il continu normal
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

}

void Arm::PostTakePaletFloor(){
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  DoorAction.CloseAll();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////Out Palet to the floor//////////////////////////////////////////////////////////////////////////

void Arm::PreOutPaletFloor(){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  ElevatorRobot.GoToFloor(7);
}

void Arm::OutPaletFloor(int floorNb, bool cote){
  //Rappel et verif qu'il ai fait le preOut
  DoorAction.OpenAll();
  ForeArmAction.DeploiementSaisieFloor();
  ElevatorRobot.GoToFloor(7);
  delay(500);
  //Et il continue
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
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  ElevatorRobot.GetPaletFloor();
  delay(500);
  PompeRobot.Close();
  delay(500);
  ElevatorRobot.GoToFloor(3);

}

void Arm::PostOutPaletFloor(){
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  DoorAction.CloseAll();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////take Palet to the wall//////////////////////////////////////////////////////////////////////////


void Arm::PreTakePaletWall(){
  ForeArmAction.DeploiementSaisieWall();
  delay(500);
  ElevatorRobot.GetPaletWall();
  delay(500);
}


void Arm::TakePaletWall(){
  PompeRobot.Open();
  delay(500);
  ElevatorRobot.GoToFloor(2);
  delay(500);
}


void Arm::PostTakePaletWall(int floorNb, bool cote){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  ElevatorRobot.GoToFloor(7);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////Out Palet to the wall//////////////////////////////////////////////////////////////////////////

void Arm::PreOutPaletWall(int floorNb, bool cote){
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
  ElevatorRobot.GoToFloor(4);
  delay(500);
  ForeArmAction.DeploiementOutWall();
  delay(500);
  DoorAction.CloseAll();
 }


void Arm::OutPaletWall(){
  ElevatorRobot.GetOutPaletWall();
  delay(500);
  PompeRobot.Close();
}


void Arm::PostOutPaletWall(){
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  ElevatorRobot.GoToFloor(6);
}


void Arm::ChoixPileStock(){
  
}

void Arm::ChoixPileDeStock(){
  
}
