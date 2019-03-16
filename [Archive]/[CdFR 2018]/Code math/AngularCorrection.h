#include "Arduino.h"
#include "Point.h"

//int *AngleC; 
//double *TicRecovery;

struct Correction
{
  float Theta;
  float Length;
};

Correction Trajectory(Point StepN_1, Point StepN, Point FinalStep);
// ancienne def de fonction: double thetaNow, double DistanceStepBefore, double DistanceFinalStep, double Y_position



  

