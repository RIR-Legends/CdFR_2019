#include "RIR_communication.h"

RIR_Com com;
void setup() {  
}

void loop() {
    // Sending side
    com.RIR_send(com.Orange);

    com.RIR_send(com.Tirette);

    while(!com.RIR_checkAndRead()){
      delay(10);
    }
    // Do the action
    delay(5000);

    com.RIR_send(com.Action_Finished);

    while(!com.RIR_checkAndRead()){
      delay(10);
    }
    // Suppose to turn off robot.
}
