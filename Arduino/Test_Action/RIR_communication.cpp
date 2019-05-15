#include "RIR_communication.h"

RIR_Com::RIR_Com()
{
    // In and Out
    Recu            = '1';
    Attente         = '0';
    Action_Finished = 't';
    
    // In
    Arret           = 'A';
    Initialisation  = 'I';
    Transport       = 'T';
    Palet_Floor_In  = 'f';
    Palet_Wall_In   = 'w';
    Palet_Floor_Out = 'F';
    Palet_Wall_Out  = 'W';
    
    // Out
    Tirette         = 'D';
    Violet          = 'v';
    Orange          = 'o';
    
    Avance          = 'a';
    Recule          = 'r';
    
    // Devices messages
    __ard_msg = Attente;
    __rasp_msg = Attente;
}

RIR_Com::~RIR_Com()
{
}

void RIR_Com::RIR_send(int msg)
{
    __ard_msg = msg;
    while (__rasp_msg != Recu){
        Serial.write(__ard_msg);
        Serial.flush();  
        if (Serial.available() > 0) {
          __rasp_msg = Serial.read();
        }
        delay(100);
    }
    
    Serial.write(__ard_msg);
    delay(100);
}

bool RIR_Com::RIR_read()
{
    Serial.flush();  
    if (Serial.available() > 0) {
      __rasp_msg = Serial.read();
    }
    if (__rasp_msg == Attente || __rasp_msg == Recu){
      delay(100);
      return false;
    }
    // Interprete value
    
    __ard_msg = Recu;
    Serial.write(__ard_msg);
    delay(100);
    return true;
}
