#include "RIR_communication.h"

#include "Arm.h"
#include "Tirette.h"
#include "CapteurPression.h"

Door DoorAction;
ForeArm ForeArmAction;
Setup SetupRobot;
Elevator ElevatorRobot;
Pompe PompeRobot;
Arm ArmRobot; 
//Tirette TiretteRobot; 
CapteurPression CapteurPressionRobot;

RIR_Com com;

void setup() {
  Serial.begin(9600);

  SetupRobot.SetAll();
  //Test();
  delay(1000);
  com.RIR_send(com.Action_Finished); //Arduino doit entamer la communication en PREMIER!

  //com.RIR_send(com.Orange);
  //com.RIR_send(com.Tirette);
}

void loop() {
    while(!com.RIR_read()){
      continue;
    }
    
    switch(com.Reponse){
      case com.Arret:
        delay(100);
        return;
        //break;
        
      case com.Initialisation:
        delay(100);
        ArmRobot.InitArm();
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Transport:
        delay(100);
        ArmRobot.Transport();
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Palet_Floor_In:
        delay(100);
        ArmRobot.PreTakePaletFloor();
        //com.RIR_waitEndMove(com.Avance);
        //Serial.flush();
        delay(100);
        ArmRobot.TakePaletFloor();
        //com.RIR_waitEndMove(com.Recule);
        //Serial.flush();
        delay(100);
        ArmRobot.PostTakePaletFloor();
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Palet_Wall_In:
        delay(100);
        com.RIR_waitEndMove(com.Avance);
        delay(100);
        com.RIR_waitEndMove(com.Recule);
        delay(100);
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Palet_Floor_Out:
        delay(100);
        ArmRobot.PreOutPaletFloor();
        //com.RIR_waitEndMove(com.Avance);
        delay(100);
        ArmRobot.OutPaletFloor();
        //com.RIR_waitEndMove(com.Recule);
        delay(100);
        ArmRobot.PostOutPaletFloor();
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Palet_Wall_Out:
        delay(100);
        com.RIR_waitEndMove(com.Avance);
        delay(100);
        com.RIR_waitEndMove(com.Recule);
        delay(100);
        com.RIR_send(com.Action_Finished);
        break;
    }
}

void Test(){
  //Serial.println("test");
  ArmRobot.InitArm();
  delay(2000);
  ArmRobot.CoupBrasJaune();
  delay(1000);
//  ForeArmAction.DeploiementSaisieFloor();
//  //delay(1000);
//  //PompeRobot.Open();
//  delay(2000);
//  ElevatorRobot.GoToFloor(6);
//  //delay(500);
//  ForeArmAction.ParquetG();
//  //ForeArmAction.DeploiementSaisieWall();
//  delay(5000);
  //PompeRobot.Close();

  //ForeArmAction.DeploiementSaisieFloor();
  //ForeArmAction.DeploiementDrop();
  //ForeArmAction.DeploiementSaisieWall();
  //ForeArmAction.ParquetG();
  //ForeArmAction.ParquetD();
//
  //ArmRobot.Transport();
  for(int i = 0; i<5; i++){
        ArmRobot.PreTakePaletWall();
        //Serial.flush();
        delay(100);
        ArmRobot.TakePaletWall();
        //Serial.flush();
        delay(100);
        ArmRobot.PostTakePaletWall();
  }
  for(int i = 0; i<7; i++){
        ArmRobot.PreOutPaletWall();
        //Serial.flush();
        delay(100);
        ArmRobot.OutPaletWall();
        //Serial.flush();
        delay(100);
        ArmRobot.PostOutPaletWall();
  }
  

  delay(50000000);
}
