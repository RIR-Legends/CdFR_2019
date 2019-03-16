#include <digitalWriteFast.h>

//Codeuse Droite
#define VOIXA_DROITE 18 // Fil VERT du codeur
#define VOIXB_DROITE 19 // Fil GRIS du codeur 
#define vectInterruptA_droit 5 // Va avec VOIXA_DROIT, fictif
#define vectInterruptB_droit 4 // Va avec VOIXB_DROIT, fictif

//Codeuse Gauche
#define VOIXA_GAUCHE 2 // Fil VERT du codeur
#define VOIXB_GAUCHE 3 // Fil GRIS du codeur
#define vectInterruptA_gauche 0 // Va avec VOIXA_GAUCHE, fictif
#define vectInterruptB_gauche 1 // Va avec VOIXB_GAUCHE, fictif

long ticks_R = 0;
long ticks_L = 0; 


void setup() {
  Serial.begin(9600);

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
  attachInterrupt(vectInterruptA_droit, GestionInterruptionCodeurPinA_DR, RISING);
  attachInterrupt(vectInterruptA_gauche, GestionInterruptionCodeurPinA_GA, RISING);
}

void loop() {
  delay(100);

  Serial.print("Gauche : ");
  Serial.print(ticks_L);
  Serial.print("\t Droit: ");
  Serial.println(ticks_R);
  Serial.print(digitalRead(VOIXA_DROITE));
  Serial.println(digitalRead(VOIXB_DROITE));
}


void GestionInterruptionCodeurPinA_DR()
{
    ticks_R = digitalReadFast(VOIXB_DROITE) ? ticks_R + 1 : ticks_R - 1;
}

void GestionInterruptionCodeurPinA_GA()
{
  ticks_L = digitalReadFast(VOIXB_GAUCHE) ? ticks_L - 1 : ticks_L + 1;
}
