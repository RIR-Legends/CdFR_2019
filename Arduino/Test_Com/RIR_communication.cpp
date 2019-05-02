#include "RIR_communication.h"

RIR_Com::RIR_Com()
{
    // Open Serial
    Serial.begin(9600);

    // In and Out
    Recu            = '1';
    Attente         = '0';
    
    // In
    Arret           = 'A';
    Initialisation  = 'I';
    Transport       = 'T';
    Palet_Floor_In  = 'f';
    Palet_Wall_In   = 'w';
    Palet_Floor_Out = 'F';
    Palet_Wall_Out  = 'W';
    
    // Out
    Action_Finished = 't';
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
        if(Serial.available()){
            Serial.write(__ard_msg);
            __rasp_msg = Serial.read();
        }
    }
    __ard_msg = Attente;
    for (int i = 0 ; i < 1000 ; i++){
        if(Serial.available()){
            Serial.write(__ard_msg);
        }
    }
}

void RIR_Com::RIR_read()
{
    while (Serial.available() && (__rasp_msg == Attente || __rasp_msg == Recu)){
        __rasp_msg = Serial.read();
    }
    // Interprete value, so change internal variables
    
    __ard_msg = Recu;
    while (Serial.available() && (Serial.read() != Attente || Serial.read() != Recu)){
        Serial.write(__ard_msg);
    }
}

bool RIR_Com::RIR_check()
{
    if (Serial.available()){
        Serial.write(Attente);
        return Serial.read() != Attente && Serial.read() != Recu;
    }
    return false;
}

bool RIR_Com::RIR_checkAndRead()
{
    if (this -> RIR_check()){
        this -> RIR_read();
        return true;
    }
    return false;
}
