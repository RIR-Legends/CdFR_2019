#include "Arduino.h"

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


class Setup
{
  public:
  void Encoder();
};

