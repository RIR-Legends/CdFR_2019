#ifndef RIR_COM
#define RIR_COM

#include "Arduino.h"

class RIR_Com{
    public:
    RIR_Com();
    ~RIR_Com();
    void RIR_send(int);
    void RIR_read();
    bool RIR_check();
    bool RIR_checkAndRead();
    
    int Recu;
    int Attente;
    
    int Arret;
    int Initialisation;
    int Transport;
    int Plaet_Floor_In;
    int Palet_Wall_In;
    int Palet_Floor_Out;
    int Palet_Wall_Out;
    
    int Action_Finished;
    int Tirette;
    int Violet;
    int Orange;
    int Avance;
    int Recule;
    
    private:
    int __ard_msg;
    int __rasp_msg;
};

#endif RIR_COM