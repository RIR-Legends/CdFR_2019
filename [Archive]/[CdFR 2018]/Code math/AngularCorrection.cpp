#include "AngularCorrection.h"


Correction Trajectory(Point StepN_1, Point StepN, Point FinalStep)
{
  float ThetaRecovery;
  float LengthRecovery;
  Correction Instructions; 
  float DistanceStepBefore;
  float DistanceFinalStep;
  float Y_position;
  double SignAngle;

  // Calcul DistanceStepBefore
  DistanceStepBefore = StepN.X() - StepN_1.X();

  // Calcul DistanceFinalStep
  DistanceFinalStep = FinalStep.X() - StepN.X();

  // Calcul SignAngle donne le bon sign a l'angle
  if (StepN.Y() - StepN_1.Y() < 0)
  SignAngle = 1;
  else
  SignAngle = -1;
  
  
  // Calcul du theta a corriger pour retrouver la trajectoire
  ThetaRecovery = SignAngle*abs( atan(tan(StepN.Theta())*(DistanceStepBefore/DistanceFinalStep))) + abs(StepN.Theta());

  // Calcul de la différence de distance parcourrue
  LengthRecovery = DistanceFinalStep + (StepN.Y()/tan(StepN.Theta()))*cos(ThetaRecovery - StepN.Theta());
  
  // Assignation des variables
  Instructions.Theta = ThetaRecovery;
  Instructions.Length = LengthRecovery;
  return(Instructions);
}
