#include "RIR_communication.h"

RIR_Com com;

void setup() {
  Serial.begin(9600);
}

void loop() {
    // Sending side
    com.RIR_send(com.Orange);

    com.RIR_send(com.Tirette);

    while(!com.RIR_read()){
      continue;
    }
    // Do the action

    com.RIR_send(com.Action_Finished);

    while(!com.RIR_read()){
      continue;
    }
    // Suppose to turn off robot.
    delay(100000);
}
