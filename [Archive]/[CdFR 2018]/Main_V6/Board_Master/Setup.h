#ifndef SETUP_ACTION
#define SETUP_ACTION

#include "Arduino.h"
#include <Servo.h>

//Turbine
#define PINTURBINE 6

//Dynamixel Control
#define PINDX 10

//Tirette
#define TIRETTE 12 

//Capteurs IR
#define CAPT_AVD A4
#define CAPT_ARD A5
#define CAPT_AVG A6
#define CAPT_ARG A7

//Pompes
#define POMPE1 29
#define POMPE2 31
#define POMPE3 33
#define POMPE4 35
#define POMPE5 37
               

class Setup{
  public:
  void SetTurbine(Servo);
  void SetPompes();
};

#endif

