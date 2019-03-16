#include "Setup.h"
#include "Pompes.h"
#include "DX.h"
#include "TimerOne.h"

Servo Turbine;
Setup RobotSetup;
Pompes RobotPompes;
Dynamixels DX;
int CLOCK = 0;

void OneSecond() {
  CLOCK++;
}

void setup() {
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(OneSecond);

  Serial.begin(9600);
  RobotSetup.SetTurbine(Turbine);
  RobotSetup.SetPompes();

  RobotPompes = Pompes();
  RobotPompes.AllOff();

  DDRL = B11110000; //0 input et 1 output
  PORTL |= B00000000; //Données dans les 4 premiers bits //Par défaut tirette
  /*
    Master
    B10000000 Repos
    B00000000 Tirette
    B01010000 Action terminee
    B10100000 Timer
    B11110000 Obstacle
    B00010000 Recu

    Slave
    B00001000 Repos
    B00001111 Deplacement termine
    B00000001 Recu
  */
  //Serial.println((PINL & B00001111) == B00001000);

  DX.Parking(); //Ranger le bras
}

void loop() {
  CheckStop();

  /* CUBES 1*/
  ActionCubes();

  /*RECUPERATEUR EAU*/
  ActionEau();

  /* CUBES 2*/
  ActionCubes();
}

void NextMove() {
  PORTL = B01010000;
  delay(1000); //Pour éviter un éventuel chevauchement
  while ((PINL & B00001111) != B00001111) {
    PORTL = B01010000;
    CheckStop();
  }
  PORTL = B10000000;
}

bool DetectionObstacle() {
  short Threshold = 210; //Ancien 120
  return ((analogRead(CAPT_AVD) > Threshold) || (analogRead(CAPT_ARG) > Threshold) || (analogRead(CAPT_AVG) > Threshold) || (analogRead(CAPT_ARD) > Threshold));
  //return false;
}

void CheckStop() {
  while (digitalRead(TIRETTE) == 1)
  {
    PORTL = B00000000;
    delay(100);
    CLOCK = 0;
    delay(200);
  }

  if (CLOCK > 95)
  {
    while (true)
    {
      PORTL = B10100000; //Communication à la board slave
      delay(100);
      RobotPompes.AllOff();
      delay(100);
      Turbine.write(0);
      delay(100);
      //DX.Parking();
      //delay(100);
    }
  }
  else if (DetectionObstacle())
    while (DetectionObstacle())
    {
      PORTL = B11110000;
      delay(100);
    }
  delay(200);
}

void ActionCubes() {
  //Loin devant les cubes
  NextMove();
  CheckStop();
  DX.PositionPrise();
  CheckStop();
  RobotPompes.AllOn();
  CheckStop();

  //Avance devant les cubes
  NextMove();
  CheckStop();
  DX.DescenteMain();
  CheckStop();
  delay(400);
  CheckStop();
  DX.PositionDepose();
  CheckStop();


  //Deplacement à la zone
  NextMove();
  //Eventuellement tourner pour les etages etc...
  CheckStop();
  RobotPompes.AllOff();
  CheckStop();
  delay(500);
  DX.Rotation45();
  delay(300);
  CheckStop();
}

void ActionEau() {

  //Deplacement recupérateur d'eau
  NextMove();
  Turbine.write(170);
  delay(1000);
  Turbine.write(90);
  delay(1000);
}

