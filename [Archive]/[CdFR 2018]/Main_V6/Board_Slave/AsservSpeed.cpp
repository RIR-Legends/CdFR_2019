#include "AsservSpeed.h"

Asservissement::Asservissement()
{
  MaxSpeed = 23;
  Offset = 21; //15 mini

  TicksAccL = 50; //Nombre de ticks avant d'atteindre la vitesse max
  TicksDecL = 50; //Nombre de ticks pour passer de la vitesse max à la vitesse min

  TicksAccR = 50;
  TicksDecR = 50;

  SeuilDiff = 250;
}

short Asservissement::Trapeze(short ticks, short Ticks_Consigne, short DiffTicksLR, short Speed, bool RightSide, bool Rotation)
{
  short Ticks = fabs(ticks);
  short DiffTicks = Ticks_Consigne - Ticks;
  //Cas dépassement de la consigne
  if (DiffTicks < 20)
    return 0;

  short TicksAcc = RightSide ? TicksAccR : TicksAccL;
  short TicksDec = RightSide ? TicksDecR : TicksDecL;

  //Calcul de la vitesse à associée à la situation
  float ComputeSpeed = 0;
  float MinSpeed = float(MaxSpeed - Offset);
  if (Ticks > Ticks_Consigne - TicksDec)
  {
    ComputeSpeed = (MinSpeed / float(float(TicksDec)) * DiffTicks);
    if (ComputeSpeed < 0)
      ComputeSpeed = 0;
  }
  else if (Ticks < TicksAcc)
    ComputeSpeed = MinSpeed * (float(Ticks) / float(TicksAcc));
  else
    ComputeSpeed = MinSpeed;

  if (ComputeSpeed < 0) //Techniquement impossible
    ComputeSpeed = 0;

  //Si rotation on diminue la vitesse par 2
  if (Rotation)
    ComputeSpeed /= 2;

  //if (DiffTicksLR > SeuilDiff)
  //  ComputeSpeed *= 0,9 //SeuilDiff = 20
  ComputeSpeed *= (1 - float(DiffTicksLR) / SeuilDiff);

  //Offset dans le cas de l'accélération ou la décélération
  //if (Ticks < TicksAcc || Ticks > Ticks_Consigne - TicksDec)
  ComputeSpeed += Offset;

  //  if (ComputeSpeed < Offset)
  //    return 0;

  return short(ComputeSpeed);
}
