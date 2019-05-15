#include "RIR_communication.h"
#include "Arm.h"

Door DoorAction;
ForeArm ForeArmAction;
Setup SetupRobot;
Elevator ElevatorRobot;
Pompe PompeRobot;
Arm ArmRobot; 
RIR_Com com;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
    while(!com.RIR_read()){
      continue;
    }
    // Do the action
    ArmRobot.InitArm();
    
    com.RIR_send(com.Action_Finished);

    delay(100000);
}
