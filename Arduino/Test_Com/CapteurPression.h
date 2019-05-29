#ifndef CAPTEURPRESSION_ACTION
#define CAPTEURPRESSION_ACTION

#include "Arduino.h"
#include "Setup.h"

class CapteurPression{
  public:
    CapteurPression();
    int GetPression();
      
  private:
    static int PRESSION;
  
};
#endif
