#ifndef RIR_COM
#define RIR_COM

#include "Arduino.h"

class RIR_Com{
    public:
    RIR_Com();
    ~RIR_Com();
    void RIR_send(int);
    bool RIR_read();
    void RIR_waitEndMove(int);

    int Reponse;

    enum{
      // Message commun (public)
      Action_Finished   = 't',

      // Message entrants
      Arret             = 'A',
      Initialisation    = 'I',
      Transport         = 'T',
      Palet_Floor_In    = 'f',
      Palet_Wall_In     = 'w',
      Palet_Floor_Out   = 'F',
      Palet_Wall_Out    = 'W', 

      //Message sortants
      Tirette           = 'D',
      Violet            = 'v',
      Orange            = 'o',
                          
      Avance            = 'a',
      Recule            = 'r',
    };
        
    private:
    int __ard_msg;
    int __rasp_msg;

    enum {
      // Message commun (private)
      __Recu            = '1',
      __Attente         = '0',
    };
};

#endif
