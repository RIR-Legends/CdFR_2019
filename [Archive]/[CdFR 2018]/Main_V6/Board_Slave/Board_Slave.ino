#include "Setup.h"
#include "Point.h"
#include "AsservPos.h"
#include "Stage.h"
#include "AsservSpeed.h"

#include <digitalWriteFast.h>
#include <SoftwareSerial.h>
#include <PololuQik.h>

//Setups
Setup RobotSetup; //Pour les codeuses pour l'instant
Stage RobotStages; //Pour les différentes étapes sur la table
Trajectory RobotMove = Trajectory(Point(110, 465, 0)); //Pour gérer le déplacement (planification) du robot
Asservissement RobotAsserv; //Pour gérer la vitesse du robot
int WatchDog = 0;

int i = 0;

PololuQik2s12v10 qik(7, 8, 9);

//Codeuses
short ticks_C = 0;
short ticks_R = 0;
short speedR = 0;
short ticks_L = 0;
short speedL = 0;

//Correction
Point CurrentStep;
Point FinalStep;
Correction Instructions;
bool lock = false;

short Seuil = 140;

void ComputeSeuil(short ticks_C)
{
  Seuil = (ticks_C < 150) ? 20 : 150;
}

void setup()
{
  Serial.begin(9600);
  pinMode(11, INPUT);
  RobotSetup.Encoder();
  if (digitalRead(GreenPin) == 1)
    RobotMove = Trajectory(Point(3000 - 110, 465, PI)); //Pour gérer le déplacement (planification) du robot
  else
    RobotMove = Trajectory(Point(110, 465, 0));

  RobotStages.SetupAll(digitalRead(GreenPin) == 1); //Cote vert
  qik.init();

  if (digitalRead(GreenPin) == 1)
    RobotMove = Trajectory(Point(3000 - 110, 465, PI)); //Pour gérer le déplacement (planification) du robot
  else
    RobotMove = Trajectory(Point(110, 465, 0));

  attachInterrupt(vectInterruptA_gauche, CodeuseGauche, RISING);
  attachInterrupt(vectInterruptA_droit, CodeuseDroite, RISING);

  FinalStep = RobotStages.FirstPoint();
  CurrentStep = RobotMove.ComputePosition(0, 0);
  Instructions = RobotMove.ComputeCorrection(CurrentStep, FinalStep);
  ticks_C = RobotMove.ComputeStep(Instructions.Theta, Instructions.Length, !lock);
  ticks_L = 0;
  ticks_R = 0;

  DDRL = B00001111; //0 input et 1 output
  PORTL |= B00001000; //Données dans les 4 derniers bits
  /*
    Master
    B10000000 Repos
    B00000000 Tirette
    B01010000 Action terminee
    B10100000 Timer
    B11110000 Obstacle

    Slave
    B00001000 Repos
    B00001111 Deplacement termine
  */
  //byte Val = PINL & B11110000;
  //Serial.println(Val == B10000000);
  delay(500);
}

void loop()
{
  delay(100);

  CheckCom();
  speedL = RobotAsserv.Trapeze(ticks_L, ticks_C, fabs(ticks_L) - ticks_R , speedL, false, (RobotMove.Rotation() == 2 || RobotMove.Rotation() == 4));
  speedR = RobotAsserv.Trapeze(ticks_R, ticks_C, ticks_R - fabs(ticks_L) , speedR, true, (RobotMove.Rotation() == 2 || RobotMove.Rotation() == 4));
  CheckCom();

  if (RobotMove.CheckDistance(CurrentStep, FinalStep) ||  WatchDog > 20)
  {
    if (RobotMove.CheckArrival(CurrentStep, FinalStep, !lock) || WatchDog > 20)
    {
      CheckCom();
      qik.setBrakes(127, 127);
      delay(400);
      FinalStep = RobotStages.NextStage();
      if (RobotStages.ActionHere())
        NextAction();
      lock = false;
      WatchDog = 0;
    }
    if (RobotMove.CheckDistance(CurrentStep, FinalStep)) //Dans le cas d'une nouvelle consigne, mais seulement en angle... Sinon c'est un else
    {
      lock = true;
      if (RobotMove.Rotation() == 3 || RobotMove.Rotation() == 4)
        CurrentStep = RobotMove.ComputePosition(ticks_L, -ticks_R);
      else
        CurrentStep = RobotMove.ComputePosition(ticks_L, ticks_R);
      CheckCom();
      Instructions.Length = 0;
      Instructions.Theta = FinalStep.Theta() - CurrentStep.Theta();
      ticks_C = RobotMove.ComputeStep(Instructions.Theta, Instructions.Length, !lock);
      CheckCom();
      ticks_L = 0;
      ticks_R = 0;
    }

    CheckCom();
  }
  else
    lock = false;
  if ((ticks_R < 25) || (ticks_R < 25))
    WatchDog++;

  ComputeSeuil(ticks_C);
  if ((fabs(ticks_L) > Seuil || fabs(ticks_R) > Seuil) && !lock)
  {
    if (RobotMove.Rotation() == 3 || RobotMove.Rotation() == 4)
      CurrentStep = RobotMove.ComputePosition(ticks_L, -ticks_R);
    else
      CurrentStep = RobotMove.ComputePosition(ticks_L, ticks_R);
    CheckCom();
    Instructions = RobotMove.ComputeCorrection(CurrentStep, FinalStep);
    CheckCom();
    ticks_C = RobotMove.ComputeStep(Instructions.Theta, Instructions.Length, !lock);
    CheckCom();
    ticks_L = 0;
    ticks_R = 0;
  }

  CheckCom();
  if (RobotMove.Rotation() == 1)
    qik.setSpeeds(-speedR, +speedL); //Pas de retour arrière
  else if (RobotMove.Rotation() == 2)
    qik.setSpeeds(-speedR, -speedL);
  else if (RobotMove.Rotation() == 3)
    qik.setSpeeds(+speedR, -speedL);
  else if (RobotMove.Rotation() == 4)
    qik.setSpeeds(+speedR, +speedL);
  CheckCom();
}

void CheckCom()
{
  while ((((PINL & B11110000) == B11110000) || (PINL & B11110000) == B00000000) || ((PINL & B11110000) == B10100000))
  {
    qik.setBrakes(127, 127);
    //Serial.println("STOP");
  }
  PORTL = B00001000;
}

void NextAction() {
  PORTL = B00001111;
  delay(1000);
  while ((PINL & B11110000) != B01010000) {
    PORTL = B00001111;
    delay(200);
  }
  PORTL = B10000000;
}


void CodeuseDroite()
{
  //ticks_R = digitalReadFast(VOIXB_DROITE) ? ticks_R + 1 : ticks_R - 1; //Elle pue le canal B de la codeuse Droite
  ticks_R++;
}

void CodeuseGauche()
{
  ticks_L = digitalReadFast(VOIXB_GAUCHE) ? ticks_L - 1 : ticks_L + 1;
}

