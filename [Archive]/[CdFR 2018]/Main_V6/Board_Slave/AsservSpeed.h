#ifndef ASSERV_H
#define ASSERV_H

#include "Arduino.h"
#include "AsservPos.h" //Inclure mmPerTick



class Asservissement
{
  public:
  Asservissement();
  short Trapeze(short, short, short, short, bool, bool);

  private:
  short MaxSpeed;
  short SeuilDiff;
  short Offset;
  
  short TicksAccL;
  short TicksDecL;

  short TicksAccR;
  short TicksDecR;
};

#endif
