#include "Setup.h"

Setup::Setup(){
  
}

void Setup::SetElevator(){
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRECTION, OUTPUT);
  pinMode(IMPULL, OUTPUT);

  pinMode(SWITCHBUTE, INPUT);
}

void Setup::SetPomp(){
  pinMode(POMPPIN, OUTPUT);
  pinMode(VANPIN, OUTPUT);

}

void Setup::SetTirette(){
  pinMode(TIRETTEPIN, INPUT_PULLUP);
  pinMode(COTEPIN, INPUT);
}
