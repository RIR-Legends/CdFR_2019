#ifndef ARM_ACTION
#define ARM_ACTION

#include "Arduino.h"
#include "Setup.h"
#include "Door.h"
#include "ForeArm.h"
#include "Elevator.h"
#include "Pompe.h"

class Arm{
  public:
  Arm();
 void SetArm();
 void InitArm();
 void Parking();
 void TakePaletFloor(int, bool);
 void Transport();
 void TakePaletWall(int, bool);
 void OutPaletWall(int, bool);
 void OutPaletFloor(int, bool);
 void ChoixPileStock(); // determine la pile ou il doit ranger le palet
 void ChoixPileDeStock(); // determine la pile ou il doit prendre un palet


  private:
  Door DoorAction;
  ForeArm ForeArmAction;
  Setup SetupRobot;
  Elevator ElevatorRobot;
  Pompe PompeRobot;
 
};
#endif
