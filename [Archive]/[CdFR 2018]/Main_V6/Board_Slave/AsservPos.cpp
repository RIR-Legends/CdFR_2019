#include "AsservPos.h"

const float mmPerTick = (PI * 90) / 1024;
const short entreRoues = 272; // En mm
const float K_Angular = mmPerTick / entreRoues;

Trajectory::Trajectory()
{
  PositionActuelle = Point();
  rotation = 1;
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
  if (fabs(ticks_R) < 10)
    ticks_R = 0;
  if (fabs(ticks_L) < 10)
    ticks_L = 0;

  //Distance parcourue par les roues depuis le dernier releve
  float distMean = mmPerTick * (ticks_L + ticks_R) / 2;

  //Affectation de la nouvelle position
  float tempX = PositionActuelle.X();
  float tempY = PositionActuelle.Y();
  float tempT = PositionActuelle.Theta();

  tempT = Point::NormTheta(tempT + K_Angular * (ticks_R - ticks_L)); //Angle en Radian ! Si Positif alors orient� vers la gauche.

  tempX += cos(tempT) * distMean;
  tempY += sin(tempT) * distMean;

  PositionActuelle = Point(tempX, tempY, tempT);
  return PositionActuelle;
}

short Trajectory::ConvertStep(float Dist_Cons, bool Rotation)
{
  return Rotation ? short((Dist_Cons * entreRoues / 2) / mmPerTick) : short(Dist_Cons / mmPerTick);
}

bool Trajectory::CheckArrival(Point CurrentStep, Point FinalStep, bool Tol)
{
  float DiffTheta = Point::NormTheta(FinalStep.Theta() - CurrentStep.Theta());
  float tol = Tol ? ToleranceAngulaire : ToleranceAngulaireLarge;
  tol /= 2;

  return (((DiffTheta < tol) || (DiffTheta > 2 * PI - tol)) && CheckDistance(CurrentStep, FinalStep));
}

bool Trajectory::CheckDistance(Point CurrentStep, Point FinalStep)
{
  float DiffLength = sqrt(pow(FinalStep.X() - CurrentStep.X(), 2) + pow(FinalStep.Y() - CurrentStep.Y(), 2));
  return (DiffLength < ToleranceCartesienne);
}

short Trajectory::ComputeStep(float Angle_C, float Length_C, bool Tol)
{
  //Faire attention au sens de rotation, car l'une des deux codeuse ne peut compter que positivement.
  Angle_C = Point::NormTheta(Angle_C);
  float tol = Tol ? ToleranceAngulaire : ToleranceAngulaireLarge;
  tol /= 2;

  //D'abord asservir de en angle
  if (Angle_C > tol && Angle_C < 2 * PI - tol)
  {
    //Serial.print (" ");
    //Serial.print ("Rotation!");
    if (Angle_C > PI)
    {
      Angle_C -= PI;
      rotation = 4;
    }
    else
      rotation = 2;
    return ConvertStep(Angle_C, true);
  }
  else if (fabs(Length_C) > ToleranceCartesienne)
  {
    //Serial.print ("Translation!");
    if (Length_C < 0)
    {
      rotation = 3;
      Length_C = -Length_C;
    }
    else
      rotation = 1;
    return ConvertStep(Length_C, false);
  }
  return 0;
}

Correction Trajectory::ComputeCorrection(Point PtActuel, Point PtDestination)
{
  Correction consigne;

  float DiffX = PtDestination.X() - PtActuel.X();
  float DiffY = PtDestination.Y() - PtActuel.Y();
  float ThetaAbs = PI / 2;
  if (fabs(DiffX) > 0.1)
    ThetaAbs = (DiffX > 0) ? atan(DiffY / DiffX) : atan(DiffY / DiffX) + PI;

  consigne.Length = sqrt(pow(DiffX, 2) + pow(DiffY, 2));
  consigne.Theta = Point::NormTheta(ThetaAbs - PtActuel.Theta());
  if (consigne.Theta > PI / 2 && consigne.Theta < 3 * PI / 2) {
    consigne.Length = - consigne.Length;
    consigne.Theta = Point::NormTheta(consigne.Theta - PI);
  }
  //  if (DiffX == 0 && DiffY == 0)
  //  {
  //    consigne.Length = 0;
  //    consigne.Theta = 0;
  //  }
  //  else if (DiffX == 0)
  //  {
  //    consigne.Length = fabs(DiffY);
  //    consigne.Theta = PI/2 - PtActuel.Theta();
  //  }
  //  else if (DiffY == 0)
  //  {
  //    consigne.Length = fabs(DiffX);
  //    consigne.Theta = -PtActuel.Theta();
  //  }
  //  else
  //  {
  //    consigne.Length = sqrt(pow(DiffX,2)+pow(DiffY,2));
  //    consigne.Theta = ThetaAbs - PtActuel.Theta();
  //  }
  return consigne;
}

short Trajectory::Rotation()
{
  /*
     1 Tout droit
     2 Rotation trigo
     3 En arriere
     4 Rotation horaire
  */
  return rotation;
}

