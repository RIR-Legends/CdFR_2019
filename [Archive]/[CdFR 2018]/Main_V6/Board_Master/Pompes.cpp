#include "Pompes.h"

Pompes::Pompes(){
  P1 = POMPE1;
  P2 = POMPE2;
  P3 = POMPE3;
  P4 = POMPE4;
  P5 = POMPE5;
}

Pompes::Pompes(int PinPompe1, int PinPompe2, int PinPompe3, int PinPompe4, int PinPompe5){
  P1 = PinPompe1;
  P2 = PinPompe2;
  P3 = PinPompe3;
  P4 = PinPompe4;
  P5 = PinPompe5;
}

void Pompes::AllOn(){
  digitalWrite(P1,HIGH);
  digitalWrite(P2,HIGH);
  digitalWrite(P3,HIGH);
  digitalWrite(P4,HIGH);
  digitalWrite(P5,HIGH);
}

void Pompes::AllOff(){
  digitalWrite(P1,LOW);
  digitalWrite(P2,LOW);
  digitalWrite(P3,LOW);
  digitalWrite(P4,LOW);
  digitalWrite(P5,LOW);
}

void Pompes::Pompe1(bool Actif){
  if (Actif)
    digitalWrite(P1, HIGH);
  else
    digitalWrite(P1, LOW);
}

void Pompes::Pompe2(bool Actif){
  if (Actif)
    digitalWrite(P2, HIGH);
  else
    digitalWrite(P2, LOW);
}

void Pompes::Pompe3(bool Actif){
  if (Actif)
    digitalWrite(P3, HIGH);
  else
    digitalWrite(P3, LOW);
}

void Pompes::Pompe4(bool Actif){
  if (Actif)
    digitalWrite(P4, HIGH);
  else
    digitalWrite(P4, LOW);
}

void Pompes::Pompe5(bool Actif){
  if (Actif)
    digitalWrite(P5, HIGH);
  else
    digitalWrite(P5, LOW);
}
