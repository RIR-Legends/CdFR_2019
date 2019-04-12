#include "Arduino.h"
#include "Setup.h"
#include "Door.h"
#include "ForeArm.h"
#include "Elevator.h"
#include "Pompe.h"

class Arm{
  public:
  Arm();
 void Setup();


  private:
  Door DoorAction;
  ForeArm ForeArmAction;
  Setup SetupRobot;
  Elevator ElevatorRobot;
  Pompe PompeRobot;
 
};
