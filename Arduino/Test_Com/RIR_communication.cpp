#include "RIR_communication.h"

RIR_Com::RIR_Com()
{        
    // Devices messages
    __ard_msg = __Attente;
    __rasp_msg = __Attente;

    Reponse = -1;
}

RIR_Com::~RIR_Com()
{
  Serial.flush();
}

void RIR_Com::RIR_send(int msg)
{
    __ard_msg = msg;
    Serial.flush(); 
    do {
        Serial.write(__ard_msg);
        //Serial.flush();  
        if (Serial.available() > 0) {
          __rasp_msg = Serial.read();
        }
        delay(500);
    }while(__rasp_msg != __Recu);

    __ard_msg = __Attente;
    Serial.write(__ard_msg);
    delay(100);
}

bool RIR_Com::RIR_read()
{
    if (Serial.available() > 0) {
      __rasp_msg = Serial.read();
    }
    if (__rasp_msg == __Attente || __rasp_msg == __Recu){
      delay(100);
      return false;
    }
    Reponse = __rasp_msg;
    
    __ard_msg = __Recu;
    Serial.write(__ard_msg);
    delay(100);
    return true;
}

void RIR_Com::RIR_waitEndMove(int msg)
{
  RIR_send(msg);
  while(Reponse != Action_Finished){
    RIR_read();
  }
  Reponse = -1;
}
