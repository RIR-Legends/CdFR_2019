#include "Setup.h"
#include "Point.h"
#include "Trajectory.h"

#include <digitalWriteFast.h>

//Setups
Setup RobotSetup; //Pour les codeuses pour l'instant
Trajectory RobotMove = Trajectory(Point(3000 - 110,405,PI)); //Pour gérer le déplacement (planification) du robot

//Codeuses
short ticks_R = 0;
short ticks_L = 0; 

void setup()
{
  Serial.begin(9600);
  RobotSetup.Encoder();

  attachInterrupt(vectInterruptA_gauche, CodeuseGauche, RISING);
  attachInterrupt(vectInterruptA_droit, CodeuseDroite, RISING);
}


void loop()
{
  delay(1000);
  (RobotMove.ComputePosition(ticks_L, ticks_R)).AfficherPosition();
  //Serial.print(ticks_L);
  //Serial.print("\t");
  //Serial.println(ticks_R);
  ticks_L = 0;
  ticks_R = 0;
}

void CodeuseDroite()
{
  ticks_R = !digitalReadFast(VOIXB_DROITE) ? ticks_R - 1 : ticks_R + 1;
}

void CodeuseGauche()
{
  ticks_L = digitalReadFast(VOIXB_GAUCHE) ? ticks_L - 1 : ticks_L + 1;
}

