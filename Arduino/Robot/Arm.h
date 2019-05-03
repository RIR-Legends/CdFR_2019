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
 void Transport();

 void PreTakePaletFloor();
 void TakePaletFloor(int, bool);
 void PostTakePaletFloor();

 void PreOutPaletFloor();
 void OutPaletFloor(int, bool);
 void PostOutPaletFloor();

 void PreTakePaletWall();
 void TakePaletWall();
 void PostTakePaletWall(int floorNb, bool cote);

  void PreOutPaletWall(int, bool);
 void OutPaletWall();
 void PostOutPaletWall();


  private:
  Door DoorAction;
  ForeArm ForeArmAction;
  Setup SetupRobot;
  Elevator ElevatorRobot;
  Pompe PompeRobot;

 
};
#endif
