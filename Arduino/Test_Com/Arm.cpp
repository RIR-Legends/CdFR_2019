#include "Arm.h"

int Arm::stock[2] = {0,0};
int Arm::consigneStock[2]= {0,0};
int Arm::consigneDesStock[2]= {0,0};

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
  delay(1000);
  DoorAction.CloseAll();
  delay(1000);
}

void Arm::InitPosiArm(){
  ForeArmAction.DeploiementSaisieFloor();
  ElevatorRobot.InitialPosition();
}

void Arm::Parking(){
  ElevatorRobot.Transport();
  ForeArmAction.InitDynamixel();
}

void Arm::Transport(){
    DoorAction.OpenAll();
    delay(500);
    ForeArmAction.DeploiementSaisieFloor();
    delay(500);
    ElevatorRobot.Transport();
    delay(500);
    ForeArmAction.BrasTransport();
    delay(500);
    DoorAction.CloseAll();
    
}



//////////////////////////////////////////////////////////////////////Take a Palet to the floor//////////////////////////////////////////////////////////////////////////
void Arm::PreTakePaletFloor(){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
}

void Arm::TakePaletFloor(){
  ChoixStockPile();
  int floorNb = consigneStock[0];
  bool cote = consigneStock[1];
  
  //Rappel et verif qu'il ai fait le preTake
  DoorAction.OpenAll();
  ForeArmAction.DeploiementSaisieFloor();
  //Puis il continu normal
  ElevatorRobot.GetPaletFloor();
  delay(500);
  PompeRobot.Open();
  delay(500);
  if(CapteurPressionRobot.GetPression()){
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
    stock[consigneStock[1]] = stock[consigneStock[1]]+1;
  }else{
    PompeRobot.Close();
    delay(500);
    ForeArmAction.DeploiementSaisieFloor();
   delay(500);
    ElevatorRobot.Transport();
  }
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

void Arm::OutPaletFloor(){
  ChoixDesStockPile();
  int floorNb = consigneStock[0];
  bool cote = consigneStock[1];
  
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
  delay(1000);
  if(CapteurPressionRobot.GetPression()){
  
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

    stock[consigneStock[1]] = stock[consigneStock[1]]-1;
  }else{    
    PompeRobot.Close();
    delay(500);
    ElevatorRobot.InitialPosition();
    delay(500);
    ForeArmAction.DeploiementSaisieFloor();
  }
}

void Arm::PostOutPaletFloor(){
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  DoorAction.CloseAll();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////take Palet to the wall//////////////////////////////////////////////////////////////////////////


void Arm::PreTakePaletWall(){
  DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  ElevatorRobot.GoToFloor(3);
  delay(500);
  ForeArmAction.DeploiementSaisieWall();
  delay(500);
  ElevatorRobot.GetPaletWall();
  delay(500);
  DoorAction.CloseAll();
  delay(500);
}


void Arm::TakePaletWall(){
  PompeRobot.Open();
  delay(500);
  ElevatorRobot.GoToFloor(2);
  delay(500);
}


void Arm::PostTakePaletWall(){
  ChoixStockPile();
  int floorNb = consigneStock[0];
  bool cote = consigneStock[1];
  delay(500);
  if(CapteurPressionRobot.GetPression()){
    DoorAction.OpenAll();
  delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  ElevatorRobot.GoToFloor(floorNb+1);
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
  ElevatorRobot.GoToFloor(floorNb+1);
 delay(500);
  ForeArmAction.DeploiementSaisieFloor();
  delay(500);
  DoorAction.CloseAll();
  stock[consigneStock[1]] = stock[consigneStock[1]]+1;
  }
  PompeRobot.Close();
  delay(500);
  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////Out Palet to the wall//////////////////////////////////////////////////////////////////////////

void Arm::PreOutPaletWall(){
  ChoixDesStockPile();
  int floorNb = consigneStock[0];
  bool cote = consigneStock[1];
  
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
   if(CapteurPressionRobot.GetPression()){
    ElevatorRobot.GoToFloor(floorNb+1);
    delay(500);
    ForeArmAction.DeploiementSaisieFloor();
    delay(500);
    ForeArmAction.DeploiementOutWall();
    delay(500);
    DoorAction.CloseAll();
    
     stock[consigneStock[1]] = stock[consigneStock[1]]-1;
   }else{
      ElevatorRobot.GoToFloor(floorNb+1);
      delay(500);
      ForeArmAction.DeploiementSaisieFloor();
      delay(500);
      DoorAction.CloseAll();
   }
  
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


void Arm::ChoixStockPile(){
  //choix coté

  if (stock[0] == stock[1]){
    consigneStock[1] = 1;
  }else if(stock[0] < stock[1]){
    consigneStock[1] = 0;
  }else{
     consigneStock[1] = 1;
  }
  //Choix étage
  consigneStock[0] = stock[consigneStock[1]]+1;
    //stock[consigneStock[1]] = stock[consigneStock[1]]+1;
}

void Arm::ChoixDesStockPile(){
  //choix coté
  if (stock[0] == stock[1]){
    consigneStock[1] = 1;
  }else if(stock[0] > stock[1]){
    consigneStock[1] = 0;
  }else{
     consigneStock[1] = 1;
  }
  //Choix étage
  consigneStock[0] = stock[consigneStock[1]];
    //stock[consigneStock[1]] = stock[consigneStock[1]]-1;
}

void Arm::CoupBrasJaune(){
  ForeArmAction.MoveTo(820,180);
  delay(500);
  ForeArmAction.MoveTo(500,180);
  delay(500);
  ForeArmAction.MoveTo(500,860);
  
}

void Arm::CoupBrasViolet(){
   ForeArmAction.MoveTo(820,860);
   delay(500);
  ForeArmAction.MoveTo(500,860);
    delay(500);
   ForeArmAction.MoveTo(500,180);
}
