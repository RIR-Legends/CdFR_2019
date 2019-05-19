#include "RIR_communication.h"

RIR_Com com;

void setup() {
  Serial.begin(9600);

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
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Transport:
        delay(100);
        com.RIR_send(com.Action_Finished);
        break;
        
      case com.Palet_Floor_In:
        delay(100);
        com.RIR_waitEndMove(com.Avance);
        //Serial.flush();
        delay(100);
        com.RIR_waitEndMove(com.Recule);
        //Serial.flush();
        delay(100);
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
        com.RIR_waitEndMove(com.Avance);
        delay(100);
        com.RIR_waitEndMove(com.Recule);
        delay(100);
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

