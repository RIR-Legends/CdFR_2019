//#include "Setup.h"
//#include "Door.h"
//#include "ForeArm.h"
//#include "Elevator.h"
//#include "Pompe.h"

#include "Arm.h"
#include "Tirette.h"
#include "CapteurPression.h"

Door DoorAction;
ForeArm ForeArmAction;
Setup SetupRobot;
Elevator ElevatorRobot;
Pompe PompeRobot;
Arm ArmRobot; 
Tirette TiretteRobot; 
CapteurPression CapteurPressionRobot;

void setup() {


  
  // put your setup code here, to run once:

  //SetupRobot.SetElevator();
  //SetupRobot.SetPomp();
  //SetupRobot.SetTirette();
  //SetupRobot.SetCapPression();
  SetupRobot.SetAll();

  
  
      Serial.begin(9600);

  ArmRobot.InitArm();
  delay(2000);
  


//TestDoor();
//TestForeArm();
//TestElevator();
//TestPomp();
//TestArm();
TestPile();
TestDePile();

}

void loop() {

   //TestTirette();
   //TestPression();
}
void TestPression(){
  Serial.println(CapteurPressionRobot.GetPression());   
  PompeRobot.Open();

}


void TestTirette(){
  //Serial.println(TiretteRobot.GetCote());
  Serial.println(TiretteRobot.GetTirette());
}


void TestPile(){
    ArmRobot.Transport();
  delay(1000);


//TEST TakePaletFloor
  ArmRobot.PreTakePaletFloor();
  ArmRobot.TakePaletFloor();
  ArmRobot.PostTakePaletFloor();
  delay(500); 

//TEST TakePaletFloor
  ArmRobot.PreTakePaletFloor();
  ArmRobot.TakePaletFloor();
  ArmRobot.PostTakePaletFloor();
  delay(500); 

  ArmRobot.InitPosiArm();
  delay(500);

//TEST TakePaletFloor
  ArmRobot.PreTakePaletFloor();
  ArmRobot.TakePaletFloor();
  ArmRobot.PostTakePaletFloor();
  delay(500); 

//TEST TakePaletFloor
  ArmRobot.PreTakePaletFloor();
  ArmRobot.TakePaletFloor();
  ArmRobot.PostTakePaletFloor();
  delay(500);
  
  ArmRobot.InitPosiArm();
  delay(500); 

//TEST TakePaletFloor
  ArmRobot.PreTakePaletFloor();
  ArmRobot.TakePaletFloor();
  ArmRobot.PostTakePaletFloor();
  delay(500); 

}

void TestDePile(){
   ArmRobot.InitPosiArm();
   delay(500);
   ArmRobot.Transport();
  delay(1000);


//TEST OutPaletFloor  
  ArmRobot.PreOutPaletFloor();
  ArmRobot.OutPaletFloor();
  ArmRobot.PostOutPaletFloor();
  delay(500); 

//TEST OutPaletFloor  
  ArmRobot.PreOutPaletFloor();
  ArmRobot.OutPaletFloor();
  ArmRobot.PostOutPaletFloor();
  delay(500); 
  //ArmRobot.InitArm();
  ArmRobot.InitPosiArm();
  delay(500);

//TEST OutPaletFloor  
  ArmRobot.PreOutPaletFloor();
  ArmRobot.OutPaletFloor();
  ArmRobot.PostOutPaletFloor();
  delay(500); 

//TEST OutPaletFloor  
  ArmRobot.PreOutPaletFloor();
  ArmRobot.OutPaletFloor();
  ArmRobot.PostOutPaletFloor();
  delay(500);
  ArmRobot.InitPosiArm();
  delay(500); 
 
//TEST OutPaletFloor  
  ArmRobot.PreOutPaletFloor();
  ArmRobot.OutPaletFloor();
  ArmRobot.PostOutPaletFloor();
  delay(500); 

}


void TestArm(){
  ArmRobot.Transport();
  delay(1000);
  //ArmRobot.InitPosiArm();

////TEST TakePaletFloor
//  ArmRobot.PreTakePaletFloor();
//  ArmRobot.TakePaletFloor();
//  ArmRobot.PostTakePaletFloor();
//  delay(500);  

//TEST OutPaletFloor
//  ArmRobot.PreOutPaletFloor();
//  ArmRobot.OutPaletFloor();
//  delay(500);  
//  ArmRobot.OutPaletFloor();
//  ArmRobot.PostOutPaletFloor();
//  delay(500);  


//TEST TakePaletWall
//  ArmRobot.PreTakePaletWall();
//  delay(1000);
//  ArmRobot.TakePaletWall();
//  delay(1000);
//  ArmRobot.PostTakePaletWall();
//  delay(500);  

//TEST TakePaletFloor
//  ArmRobot.PreOutPaletWall();
//  delay(1000);
//  ArmRobot.OutPaletWall();
//  delay(1000);
//  ArmRobot.PostOutPaletWall();
//  delay(500); 

  //ArmRobot.Transport();
//  delay(1000);
//  ArmRobot.OutPaletWall();
//  delay(500);
//  ArmRobot.OutPaletWall();
//  delay(500);
//  ArmRobot.OutPaletWall();
//  delay(500);
//  ArmRobot.OutPaletWall();
//  delay(500);
//  ArmRobot.OutPaletWall();
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
