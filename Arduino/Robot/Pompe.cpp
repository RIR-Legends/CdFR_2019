#include "Pompe.h"


int Pompe::POMP = POMPPIN;
int Pompe::VAN = VANPIN;


void Pompe::Open(){

  digitalWrite(POMP, HIGH);
  digitalWrite(VAN, HIGH);
  
}

void Pompe::Close(){

  digitalWrite(POMP, LOW);
  digitalWrite(VAN, LOW);
  
}
