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

int stock[2] = {0,1};

int consigneStock[2]= {0,0};

int consigneDesStock[2]= {0,0};


void setup() {

//stock = {0,0};
//consigneStock = {0,0};
//consigneDesStock = {0,0};
  
  // put your setup code here, to run once:

  //SetupRobot.SetElevator();
  //SetupRobot.SetPomp();
      Serial.begin(9600);

  //ArmRobot.InitArm();
  delay(2000);


//TestDoor();
//TestForeArm();
//TestElevator();
//TestPomp();
//TestArm();
TestPile();

}

void loop() {

 
}

void TestPile(){

ChoixStockPile();

}

void ChoixStockPile(){
  //choix coté
  if (stock[0] == stock[1]){
    consigneStock[1] = 0;
  }else if(stock[0] < stock[1]){
    consigneStock[1] = 0;
  }else{
     consigneStock[1] = 1;
  }
  //Choix étage
  consigneStock[0] = stock[consigneStock[1]+1];
}

void ChoixDesStockPile(){
  //choix coté
  if (stock[0] == stock[1]){
    consigneStock[1] = 0;
  }else if(stock[0] < stock[1]){
    consigneStock[1] = 1;
  }else{
     consigneStock[1] = 0;
  }
  //Choix étage
  consigneStock[0] = stock[consigneStock[1]-1];
}


void TestArm(){
  ArmRobot.Transport();
  delay(1000);


//TEST TakePaletFloor
//  ArmRobot.PreTakePaletFloor();
//  ArmRobot.TakePaletFloor(1,0);
//  ArmRobot.PostTakePaletFloor();
//  delay(500);  

//TEST OutPaletFloor
//  ArmRobot.PreOutPaletFloor();
//  ArmRobot.OutPaletFloor(2,0);
//  delay(500);  
//  ArmRobot.OutPaletFloor(1,0);
//  ArmRobot.PostOutPaletFloor();
//  delay(500);  


//TEST TakePaletWall
//  ArmRobot.PreTakePaletWall();
//  delay(1000);
//  ArmRobot.TakePaletWall();
//  delay(1000);
//  ArmRobot.PostTakePaletWall(1,0);
//  delay(500);  

//TEST TakePaletFloor
  ArmRobot.PreOutPaletWall(1,0);
  delay(1000);
  ArmRobot.OutPaletWall();
  delay(1000);
  ArmRobot.PostOutPaletWall();
  delay(500); 

  //ArmRobot.Transport();
//  delay(1000);
//  ArmRobot.OutPaletWall(1,0);
//  delay(500);
//  ArmRobot.OutPaletWall(2,0);
//  delay(500);
//  ArmRobot.OutPaletWall(3,0);
//  delay(500);
//  ArmRobot.OutPaletWall(4,0);
//  delay(500);
//  ArmRobot.OutPaletWall(5,0);
//  delay(500);

  

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
  ForeArmAction.InitDynamixel();
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
