#ifndef SETUP_ACTION
#define SETUP_ACTION

#include "Arduino.h"
#include <TimerOne.h>


//Moteur pas à pas
#define ENABLE 52
#define DIRECTION 50
#define IMPULL 48

//Switch bute
#define SWITCHBUTE 22

//Pomp pin
#define POMPPIN 8
#define VANPIN 7

class Setup{
  public:
    void SetElevator();
    void SetPomp();
  
};
#endif
