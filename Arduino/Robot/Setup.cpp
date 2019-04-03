#include "Setup.h"

void Setup::SetElevator(){
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRECTION, OUTPUT);
  pinMode(IMPULL, OUTPUT);

  pinMode(SWITCHBUTE, INPUT);
}
