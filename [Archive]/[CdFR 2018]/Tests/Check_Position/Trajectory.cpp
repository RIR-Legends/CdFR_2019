#include "Trajectory.h"

const float mmPerTick = (PI * 90) / 1024;
const short entreRoues = 272; // En mm
const float K_Angular = mmPerTick / entreRoues;

const float ToleranceCartesienne = 100; //En mm
const float ToleranceAngulaire = 60 * (PI / 180); //En degré, multiplié par PI / 180 pour les radians

Trajectory::Trajectory()
{
  PositionActuelle = Point();
  rotation = false;
}

Trajectory::Trajectory(Point StartPoint)
{
  float tempX = StartPoint.X();
  float tempY = StartPoint.Y();
  float tempT = StartPoint.Theta();
  //Pour éviter un passage par adresse
  
  PositionActuelle = Point(tempX, tempY, tempT);
}

Point Trajectory::ComputePosition(short ticks_L, short ticks_R)
{
  //Distance parcourue par les roues depuis le dernier releve

    if (fabs(ticks_R) < 10)
    ticks_R = 0;
  if (fabs(ticks_L) < 10)
    ticks_L = 0;
  float distMean = mmPerTick * (ticks_L + ticks_R) / 2;
  
  //Affectation de la nouvelle position 
  float tempX = PositionActuelle.X();
  float tempY = PositionActuelle.Y();
  float tempT = PositionActuelle.Theta();

  tempT += K_Angular * (ticks_R - ticks_L); //Angle en Radian ! Si Positif alors orient� vers la gauche.
  while (tempT > 2*PI)
    tempT -= 2*PI;
  while (tempT < 0)
    tempT += 2*PI;    
  tempX += cos(tempT)* distMean;
  tempY += sin(tempT)* distMean;

  PositionActuelle = Point(tempX, tempY, tempT);
  return PositionActuelle;
}

short Trajectory::ComputeStep(Point DestinationPoint)
{
  //Faire attention au sens de rotation, car l'une des deux codeuse ne peut compter que positivement.
  float DiffTheta = DestinationPoint.Theta() - PositionActuelle.Theta();
  while (DiffTheta > 2*PI)
    DiffTheta -= 2*PI;
  while (DiffTheta < 0)
    DiffTheta += 2*PI;

  float DiffCart = sqrt(pow(DestinationPoint.X() - PositionActuelle.X(),2) + pow(DestinationPoint.Y() - PositionActuelle.Y(),2));
  float dist = 0;

  //D'abord asservir de en angle
  if (DiffTheta > ToleranceAngulaire && DiffTheta < 2*PI - ToleranceAngulaire)
  {
    dist = DiffTheta * entreRoues / 2;
    rotation = true;
  }
  else if (DiffCart > ToleranceCartesienne)
  {
    dist = DiffCart;
    rotation = false;
  }
      
  return short(dist/mmPerTick);
}

bool Trajectory::Rotation()
{
  return rotation;
}

