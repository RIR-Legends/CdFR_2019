#include "Setup.h"

void Setup::Encoder()
{
  // CODEUR DROIT
  pinMode(VOIXA_DROITE, INPUT);
  pinMode(VOIXB_DROITE, INPUT);
  digitalWrite(VOIXA_DROITE, HIGH);
  digitalWrite(VOIXB_DROITE, HIGH);
  // CODEUR GAUCHE
  pinMode(VOIXA_GAUCHE, INPUT);
  pinMode(VOIXB_GAUCHE, INPUT);
  digitalWrite(VOIXA_GAUCHE, HIGH);
  digitalWrite(VOIXB_GAUCHE, HIGH);
}
