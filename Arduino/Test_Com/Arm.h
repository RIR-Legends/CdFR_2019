#ifndef ARM_ACTION
#define ARM_ACTION

#include "Arduino.h"
#include "Setup.h"
#include "Door.h"
#include "ForeArm.h"
#include "Elevator.h"
#include "Pompe.h"
#include "CapteurPression.h"

class Arm{
  public:
  Arm();
 void SetArm();
 void InitArm();
 void Parking();
 void Transport();
 void InitPosiArm();

 void PreTakePaletFloor();
 void TakePaletFloor();
 void PostTakePaletFloor();

 void PreOutPaletFloor();
 void OutPaletFloor();
 void PostOutPaletFloor();

 void PreTakePaletWall();
 void TakePaletWall();
 void PostTakePaletWall();

  void PreOutPaletWall();
 void OutPaletWall();
 void PostOutPaletWall();

 void ChoixStockPile();
 void ChoixDesStockPile();


  private:
  Door DoorAction;
  ForeArm ForeArmAction;
  Setup SetupRobot;
  Elevator ElevatorRobot;
  Pompe PompeRobot;
  CapteurPression CapteurPressionRobot;

  static int stock[2];
  static int consigneStock[2];
  static int consigneDesStock[2];
 
};
#endif
