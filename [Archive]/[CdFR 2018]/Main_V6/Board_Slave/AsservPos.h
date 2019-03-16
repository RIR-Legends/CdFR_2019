#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include "Arduino.h"
#include "Point.h"
//#include "AngularCorrection.h"

extern const float mmPerTick;
extern const short entreRoues;

const float ToleranceAngulaire = 20* (PI / 180); //En degré, multiplié par PI / 180 pour les radians.
const float ToleranceAngulaireLarge = 30 * (PI / 180);
const float ToleranceCartesienne = 15; //En mm

struct Correction
{
  float Theta;
  float Length;
};

class Trajectory
{
  public:
  Trajectory();
  Trajectory(Point);

  Point ComputePosition(short, short);
  Correction ComputeCorrection(Point, Point);
  short ComputeStep(float,float,bool);
  short ConvertStep(float,bool);
  bool CheckArrival(Point, Point, bool);
  bool CheckDistance(Point,Point);
  //float ComputeTrajectory(Point); //Verifie régulièrement comment attendre un point donné en rectifiant l'angle de trajectoire.
  short Rotation();

  
  private:
  Point PositionActuelle;
  short rotation;
};
#endif
